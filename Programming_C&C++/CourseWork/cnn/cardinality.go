package cnn

import (
	"errors"
	"fmt"
	"math"
	"sort"
)

const (
	epressionLength = 3 // Expression length
)

// CardinalityMatrix - abstracts relations beetwean things.
// forexample: a better then b, b better then c, therfor a beter then c
type CardinalityMatrix struct {
	// Matrix      map[byte]map[byte]float64 // Matrix Representation of relations
	// Keys        []byte                    // Matrix Keys for easier Itteration
	Allocations map[Position]int // Free cells allocations
	*Matrix
}

// Position in CardinalityMatrix
type Position struct {
	row, col byte
}

// Pos as Position alais
type Pos = Position

// result used to compare values
type result struct {
	a, b float64
}

var (
	inComparable = []result{{-1, -1}, {1, 1}}         // incomparable values
	greaterThat  = []result{{1, 0}, {1, -1}, {0, -1}} // greater that
	smallerThat  = []result{{0, 1}, {-1, 1}, {-1, 0}} // smaller that
	equvalentTo  = []result{{0, 0}}                   // equivalent
)

// ------------------------------------------------

// NewCardinalityMatrix - creates and return cardinality relations matrix
func NewCardinalityMatrix(relations []string) (*CardinalityMatrix, error) {

	if len(relations) == 0 {
		return &CardinalityMatrix{}, fmt.Errorf("Inital Error: Empty Input")
	}

	// Full Fill Matrix Initial Data.
	keys, errCreateKeys := createKeys(relations)
	if errCreateKeys != nil {
		return &CardinalityMatrix{
			Allocations: make(map[Position]int),
		}, fmt.Errorf("CreateKeys: %s", errCreateKeys)
	}

	cm := &CardinalityMatrix{
		Matrix:      NewMatrix(keys),
		Allocations: make(map[Position]int),
	}

	errCreateMaps := cm.createMap()
	if errCreateMaps != nil {
		return cm, fmt.Errorf("CreateMap: %s", errCreateMaps)
	}

	errLookups := cm.createLookups()
	if errLookups != nil {
		return cm, fmt.Errorf("CreateLookups: %s", errLookups)
	}

	// matrix map creation
	for _, expr := range relations {
		errAdd := cm.Add(expr)
		if errAdd != nil {
			return cm, fmt.Errorf("Can't process expression: %s", errAdd)
		}
	}

	errorDone := cm.done()
	if errorDone != nil {
		return cm, fmt.Errorf("Cardinality Finalization: %s", errorDone)
	}

	return cm, nil
}

// CreateKeys - form a sorted slice of keys
func createKeys(existingRelations []string) ([]byte, error) {
	keys := make(map[byte]bool)
	for _, expr := range existingRelations {
		for _, index := range []int{0, 2} {
			// Only a-z allowed to test.
			if expr[index] < 97 || expr[index] > 122 {
				continue
			}

			keys[expr[index]] = true
		}
	}

	if len(keys) <= 1 {
		return []byte{}, errors.New("Matrix requires at least 2 values to create keys")
	}

	// sorting keys
	var Keys []byte
	for i := range keys {
		Keys = append(Keys, i)
	}

	sort.Slice(Keys, func(i, j int) bool { return Keys[i] < Keys[j] })

	return Keys, nil
}

// CreateMap creates a map of cross values for comparing proposes
func (cm *CardinalityMatrix) createMap() error {

	if len(cm.Matrix.Keys()) <= 1 {
		return errors.New("Matrix requires at least 2 values to create keys")
	}

	cm.Matrix.Fill(func(a, b byte) float64 {
		if a == b {
			return 0
		}
		return math.NaN()
	})
	return nil
}

func (cm *CardinalityMatrix) createLookups() error {
	var keys = cm.Matrix.Keys()
	for i, row := range keys {
		for _, col := range keys[i+1:] {
			cm.Allocations[Position{row: row, col: col}] = 0
		}
	}

	return nil
}

// At position value return.
// this function intentionaly not implements error.
func (cm CardinalityMatrix) value(p Position) (float64, error) {
	return cm.Matrix.Val(p.row, p.col)
}

// set value at position
func (cm CardinalityMatrix) set(p Position, v float64) error {
	err := cm.Matrix.Set(p.row, p.col, v)
	if err != nil {
		return err
	}
	return nil
}

// done - finalize matrix creation
func (cm *CardinalityMatrix) done() error {

	for len(cm.Allocations) > 0 {

		var changed bool

		for key := range cm.Allocations {

			// We Creating interaction positions/coordinates.
			var rows, cols []Position

			// ...First rows
			for _, row := range cm.Matrix.Keys() {
				if row == key.row {
					continue
				}

				tmp := Position{row: key.row, col: row}
				if _, ok := cm.Allocations[tmp]; !ok {
					rows = append(rows, tmp)
				}

			}

			// ...Second Cols
			for _, col := range cm.Matrix.Keys() {
				if col == key.col {
					continue
				}
				tmp := Position{row: key.col, col: col}
				if _, ok := cm.Allocations[Position{row: tmp.col, col: tmp.row}]; !ok {
					cols = append(cols, tmp)
				}
			}

			// This is Pairs of position we can check
			var pairs [][]Position
			for _, row := range rows {
				for _, col := range cols {
					if row.col == col.col {
						pairs = append(pairs, []Position{row, col})
					}
				}
			}

			// Impossible to find relation now.
			if len(pairs) == 0 {
				cm.Allocations[key]++
				continue
			}

			for _, pair := range pairs {

				// checking comapre result
				p0, _ := cm.value(pair[0])
				p1, _ := cm.value(pair[1])

				r := result{p0, p1}
				// fmt.Println(key, pair, r)
				if in(inComparable, r) {
					continue
				}

				// default case.
				// we can add something like
				// in(smallerThat, r), but really we don't need.
				var do = '<'

				if in(equvalentTo, r) {
					do = '='
				}

				if in(greaterThat, r) {
					do = '>'
				}

				// fmt.Printf("%c%c%c\n", key.row, do, key.col)
				cm.Add(fmt.Sprintf("%c%c%c", key.row, do, key.col))
				changed = true
				break
			}

		}

		if !changed {
			break
		}
	}

	// after checks we can additonaly cehck if there is empty cells
	// and if yes... throw error.
	for _, row := range cm.Matrix.Keys() {
		for _, col := range cm.Matrix.Keys() {
			value, err := cm.value(Position{row: row, col: col})

			if err != nil {
				return err
			}

			if math.IsNaN(value) {
				return errors.New("Cardinality Failure: NaN found.")
			}
		}
	}

	// at this point we reseting values to 0.0 and 1.0
	//  0.0 => 1.0
	// -1.0 => 0.0

	// fmt.Println(cm.Matrix)

	cm.Matrix.Fill(func(row, col byte) float64 {
		position := Position{row: row, col: col}
		value, _ := cm.value(position)

		if value == 0.0 {
			return 1.
		}
		if value == -1.0 {
			return 0.
		}

		return value
	})

	return nil
}

// Add a value to cardinality matrix.
func (cm *CardinalityMatrix) Add(stmt string) error {
	if len(stmt) != epressionLength {
		return fmt.Errorf("Letngth Required %d for expression %s", epressionLength, stmt)
	}

	a, expr, b := stmt[0], stmt[1], stmt[2]

	// comparisons
	var ab, ba float64 // 0,0 by default zero value

	switch expr {
	case '>':
		ab, ba = 1., -1.
	case '<':
		ab, ba = -1., 1.
	case '=':
		ab, ba = 0., 0.
	default:
		return fmt.Errorf("Only =, <, > are implemented. Expression [%c] received", expr)
	}

	// check previous value

	var (
		abPos          = Pos{row: a, col: b}
		baPos          = Pos{row: b, col: a}
		abValue, abErr = cm.value(abPos)
		baValue, baErr = cm.value(baPos)
	)

	if abErr != nil || baErr != nil {
		return fmt.Errorf("Cardinality error: position not found set %s", stmt)
	}

	if (!math.IsNaN(abValue) && abValue != ab) || (!math.IsNaN(baValue) && baValue != ba) {
		return fmt.Errorf("Cardinality error: value set %s", stmt)
	}

	cm.set(abPos, ab)
	delete(cm.Allocations, abPos)

	cm.set(baPos, ba)
	delete(cm.Allocations, baPos)

	return nil
}

// String-er implementation - prints nice table that
// represent matrix
func (p Position) String() string {
	return fmt.Sprintf("(%c,%c)", p.row, p.col)
}

func in(results []result, r result) bool {
	for _, result := range results {
		if result == r {
			return true
		}
	}
	return false
}
