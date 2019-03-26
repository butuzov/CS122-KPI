package cnn

import (
	"bytes"
	"encoding/json"
	"errors"
	"fmt"
	"io/ioutil"
	"math"
	"os"
	"sort"
	"strings"
)

/******************************************************************************


******************************************************************************/

// Do nothing
func Do() {}

// Reader fo Raw Data ---------------------------------------------------------

type rawConvolution struct {
	Weight      float64  `json:"weight"`
	Priorities  []string `json:"priorities"`
	Description string   `json:"description"`
}

type rawModelData struct {
	Goal         string                    `json:"goal"`
	Posibilities map[string]string         `json:"posibilities"`
	Convolutions map[string]rawConvolution `json:"convolutions"`
}

// rawModelJsonReader - reading json data.
func rawModelJsonReader(f string) rawModelData {

	// Checking file existance and additional errors.
	if _, err := os.Stat(f); os.IsNotExist(err) {
		panic("Can't Read Input File")
	}

	raw := rawModelData{}

	if file, err := ioutil.ReadFile(f); err != nil {
		panic(fmt.Sprintf("File error: %v\n", err))
	} else {
		json.Unmarshal(file, &raw)
	}

	return raw
}

// Convolution ----------------------------------------------------------------

// Convolution represents Weight, Description a and Cardinality matrix
type Convolution struct {
	Weight      float64
	Description string
	Priorities  CardinalityMatrix
	priorities  []string
}

// String implementation of Stringer interface
func (c Convolution) String() string {
	template := "        Description:%s\n        Relations%#v\n\n"
	return fmt.Sprintf(template, c.Description, c.priorities)
}

// Model ----------------------------------------------------------------------

// Actual solution
type Model struct {
	debug        bool
	Goal         string
	Options      map[string]string
	Keys         []byte
	Convolutions map[string]Convolution

	// Solution
	// Q1, Q2 map[byte]float64
	Option byte
}

func Create(f string, debug bool) (Model, error) {

	raw := rawModelJsonReader(f)

	convolutions := make(map[string]Convolution)

	if len(raw.Convolutions) == 0 {
		return Model{}, errors.New("Cant find any convolutions")
	}

	for key, conv := range raw.Convolutions {

		m, err := NewCardinalityMatrix(conv.Priorities)
		if err != nil {
			if debug {
				fmt.Fprintf(os.Stdout, "> Debug: \tCardinalityStrings (%s)\n", conv.Priorities)
				fmt.Fprintf(os.Stdout, "> Debug: \tCardinality\n\n%s\n", convolutions[key].Priorities)
			}
			return Model{}, fmt.Errorf("CardinalityErro1r: %s", err)
		}

		convolutions[key] = Convolution{
			Weight:      conv.Weight,
			Description: conv.Description,
			Priorities:  *m,
			priorities:  conv.Priorities,
		}

		if debug {
			fmt.Fprintf(os.Stdout, "> Debug:\tKritetiy [%s] - %s\n", key, convolutions[key].Description)
			fmt.Fprintf(os.Stdout, "> Debug:\tWeight (%.2f) \n", convolutions[key].Weight)
			fmt.Fprintf(os.Stdout, "> Debug:\tCardinality\n%s\n", convolutions[key].Priorities)
		}
	}

	m := Model{
		debug:        debug,
		Goal:         raw.Goal,
		Options:      raw.Posibilities,
		Convolutions: convolutions,
	}

	// using m.Options as source of keys
	for k := range m.Options {
		m.Keys = append(m.Keys, k[0])
	}
	sort.Slice(m.Keys, func(i, j int) bool { return m.Keys[i] < m.Keys[j] })

	var matrixQ1 = m.Q1()
	var matrixQ1Strong = matrixQ1.Q1Strong()
	var matrixQ2 = m.Q2()
	var matrixQ2Strong = matrixQ2.Q2Strong()

	var MaxQ1 = matrixQ1Strong.MaxDim()
	var MaxQ2 = matrixQ2Strong.MaxDim()

	var MaxQ1Compl = complement(MaxQ1)
	var MaxQ2Compl = complement(MaxQ2)

	var Minimum = make(map[byte]float64)
	for _, i := range m.Keys {
		Minimum[i] = math.Min(MaxQ1Compl[i], MaxQ2Compl[i])
	}

	var maximum float64
	for i, k := range Minimum {
		// fmt.Print(i, k)
		if maximum < k {
			maximum = k
			m.Option = i
		}
	}

	if debug {

		template := "[%s]\n%s\n"

		fmt.Printf(template, "Q1", matrixQ1)
		fmt.Printf(template, "Q1/Strong", matrixQ1Strong)

		fmt.Printf(template, "Q2", matrixQ2)
		fmt.Printf(template, "Q2/Strong", matrixQ2Strong)

		var names []string
		// shows max dimesion
		names = []string{"Max(Q1_i)", "Max(Q2_i)"}
		maxDim, _ := mapsPrinter(m.Keys, names, MaxQ1, MaxQ2)
		fmt.Printf(template, "Maximum", maxDim)

		names = []string{"Complement(Max(Q1_i))", "Complement(Max(Q2_i))"}
		maxDimCompl, _ := mapsPrinter(m.Keys, names, MaxQ1Compl, MaxQ2Compl)
		fmt.Printf(template, "Complement(Maximum)", maxDimCompl)

		names = []string{"MinumPerMatrix"}
		minimumSelection, _ := mapsPrinter(m.Keys, names, Minimum)
		fmt.Printf(template, "MinumPerMatrix", minimumSelection)

		fmt.Println(strings.Repeat("-", 50))
	}

	return m, nil
}

// Printers -------------------------------------------

// PrintSolution - print solution of our desicion.
func (m Model) PrintSolution() {
	fmt.Println(m.GetSolution())
}

// GetSolution - return solution as string
func (m Model) GetSolution() string {
	return fmt.Sprintf("Solution is \"%c\" - %s\n", m.Option, m.Options[string(m.Option)])
}

// PrintConvolutions of our convolutional network raw data
func (m Model) PrintConvolutions() {
	fmt.Print(m.GetConvolutions())
}

// GetConvolutions return convolutions as string
func (m Model) GetConvolutions() string {
	var b bytes.Buffer
	fmt.Fprintln(&b, "\nConditions:")
	for k, c := range m.Convolutions {
		fmt.Fprintf(&b, "    CNN %s:\n%s", k, c)
		if m.debug {
			// fmt.Fprintln(&b, "Cardinality\n", c.Priorities)
		}
	}
	return b.String()
}

// GetOptions of the current convolutional network
func (m Model) GetOptions() string {
	var b bytes.Buffer
	b.WriteString("Available Options:\n")
	for k, v := range m.Options {
		fmt.Fprintf(&b, "    %s: %s\n", k, v)
	}
	b.WriteByte('\n')
	return b.String()
}

// PrintOptions of our convolutional network raw data
func (m Model) PrintOptions() {
	fmt.Print(m.GetOptions())
}

// GetOptions of the current convolutional network
func (m Model) GetGoal() string {
	var b bytes.Buffer
	fmt.Fprintf(&b, "Goal: %s\n", m.Goal)
	b.WriteByte('\n')
	return b.String()
}

// PrintGoal of our convolutional network
func (m Model) PrintGoal() {
	fmt.Print(m.GetGoal())
}
