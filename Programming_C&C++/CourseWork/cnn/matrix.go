package cnn

import (
	"bytes"
	"fmt"
	"math"
	"strings"
)

// Matrix as matrix representation
type Matrix struct {
	keys   []byte
	matrix map[byte]map[byte]float64 //
}

// ----------------------------------------------------------------------------

// NewMatrix Creates and return pointer to new Matrix
func NewMatrix(Keys []byte) *Matrix {
	m := &Matrix{
		keys:   Keys,                            // keys we will use
		matrix: make(map[byte]map[byte]float64), // matrix initial rows
	}

	for _, row := range m.keys {
		m.matrix[row] = make(map[byte]float64)
	}

	m.Fill(func(a, b byte) float64 { return math.NaN() })

	return m
}

// Keys Return
func (m Matrix) Keys() []byte {
	return m.keys
}

// Fill matrix with arbitraty closure value
func (m *Matrix) Fill(fnc func(byte, byte) float64) {
	for _, row := range m.keys {
		for _, col := range m.keys {
			m.matrix[row][col] = fnc(row, col)
		}
	}
}

// Val returns value at row and col
func (m Matrix) Val(row, col byte) (float64, error) {
	return m.matrix[row][col], nil
}

// Set value
func (m Matrix) Set(row, col byte, v float64) error {

	if _, ok := m.matrix[row]; !ok {
		return fmt.Errorf("Row %c not available in matrix", row)
	}

	if _, ok := m.matrix[row][col]; !ok {
		return fmt.Errorf("Nothing available in matrix at row [%c] and col [%c]", row, col)
	}

	m.matrix[row][col] = v

	return nil
}

func (m Matrix) String() string {
	var b bytes.Buffer

	var lineLength = (len(m.keys) + 1) * (lengthCell + 1)
	// header
	b.WriteString(cellHeader(' ', lengthCell) + "|")
	for i, key := range m.keys {
		b.WriteString(cellHeader(key, lengthCell))
		if len(m.matrix) != i+1 {
			b.WriteByte('|')
		}
	}
	b.WriteByte('\n')
	fmt.Fprintln(&b, strings.Repeat("-", lineLength))

	for i, row := range m.keys {
		b.WriteString(cellHeader(row, lengthCell))
		if len(m.keys) != i-1 {
			b.WriteByte('|')
		}
		for i, col := range m.keys {
			b.WriteString(cellValue(m.matrix[row][col], lengthCell))
			if len(m.keys) != i+1 {
				b.WriteByte('|')
			}
		}
		b.WriteByte('\n')

		fmt.Fprintln(&b, strings.Repeat("-", lineLength))
	}

	return b.String()
}
