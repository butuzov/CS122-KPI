package cnn

// Q1 convolution of advantages
func (m Model) Q1() *Matrix {

	// var keys []byte
	// // using m.Options as source of keys
	// for k := range m.Options {
	// 	keys = append(keys, k[0])
	// }
	// sort.Slice(keys, func(i, j int) bool { return keys[i] < keys[j] })

	matrix := NewMatrix(m.Keys)

	var Filler = func(convs map[string]Convolution) func(byte, byte) float64 {
		return func(row, col byte) float64 {
			var (
				valueInCell = 1.
				position    = Position{row: row, col: col}
			)

			for _, c := range convs {
				val, _ := c.Priorities.value(position)
				valueInCell *= val
			}

			return valueInCell
		}
	}

	matrix.Fill(Filler(m.Convolutions))

	return matrix
}

func (m *Matrix) Q1Strong() *Matrix {
	matrix := NewMatrix(m.Keys())

	matrix.Fill(func(m *Matrix) func(byte, byte) float64 {
		return func(a, b byte) float64 {
			aVal, _ := m.Val(a, b)
			bVal, _ := m.Val(b, a)
			if aVal > bVal {
				return 1.
			}
			return 0.
		}
	}(m))

	return matrix
}

func (m Model) Q2() *Matrix {

	// var keys []byte
	// // using m.Options as source of keys
	// for k := range m.Options {
	// 	keys = append(keys, k[0])
	// }
	// sort.Slice(keys, func(i, j int) bool { return keys[i] < keys[j] })

	matrix := NewMatrix(m.Keys)
	var Filler = func(convs map[string]Convolution) func(byte, byte) float64 {
		return func(row, col byte) float64 {
			var (
				valueInCell = 0.
				position    = Position{row: row, col: col}
			)
			for _, c := range convs {
				val, _ := c.Priorities.value(position)
				valueInCell += val * c.Weight
			}
			return valueInCell
		}
	}
	matrix.Fill(Filler(m.Convolutions))

	return matrix
}

func (m *Matrix) Q2Strong() *Matrix {

	matrix := NewMatrix(m.Keys())

	matrix.Fill(func(m *Matrix) func(byte, byte) float64 {
		return func(row, col byte) float64 {
			abVal, _ := m.Val(row, col)
			baVal, _ := m.Val(col, row)
			if abVal > baVal {
				return abVal - baVal
			}
			return 0.0
		}
	}(m))

	return matrix
}

func (m *Matrix) MaxDim() map[byte]float64 {

	var max = make(map[byte]float64)
	var val float64

	for _, col := range m.Keys() {
		for _, row := range m.Keys() {

			val, _ = m.Val(row, col)

			if v, ok := max[col]; !ok || v < val {
				max[col] = val
			}
		}
	}
	return max
}

func complement(maps map[byte]float64) map[byte]float64 {
	var complements = make(map[byte]float64)
	for i := range maps {
		complements[i] = 1 - maps[i]
	}
	return complements
}
