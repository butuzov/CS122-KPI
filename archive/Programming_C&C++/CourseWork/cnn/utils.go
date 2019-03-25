package cnn

import (
	"bytes"
	"errors"
	"fmt"
	"math"
	"strconv"
	"strings"
	"unicode/utf8"
)

const (
	lengthCell = 6
)

// center "s" word on predefined "l" length
func center(s string, length int) string {

	var strLength = utf8.RuneCountInString(s)

	if strLength > length {
		length = strLength
	}

	padding := (length - strLength) / 2

	format := fmt.Sprintf("%%%d[1]s%%-%d[2]s", padding, length-padding)
	return fmt.Sprintf(format, "", s)
}

//
func cellHeader(h byte, length int) string {
	return center(string(h), length)
}

func cellValue(digit float64, length int) string {
	if math.IsNaN(digit) {
		return center("", length)
	}

	tmp := int(float64(100) * digit)
	if tmp == 100 || tmp == 0 {
		return center(strconv.Itoa(tmp/100), length)
	}

	return center(fmt.Sprintf("%1.2f", digit), length)
}

func mapsPrinter(rows []byte, cols []string, maps ...map[byte]float64) (string, error) {
	var b bytes.Buffer

	if len(maps) < 1 {
		return "", errors.New("Map Printer error: Empty input")
	}

	if len(cols) != len(maps) {
		return "", errors.New("Map Printer error: Columns != Matrixies")
	}

	var firstColLen int
	for i := range cols {
		if firstColLen < len(cols[i]) {
			firstColLen = len(cols[i])
		}
	}
	firstColLen += 2
	separateLineLength := firstColLen + (len(rows))*(lengthCell+1)

	// header
	b.WriteString(cellHeader(' ', firstColLen) + "|")
	for i := range rows {
		b.WriteString(cellHeader(rows[i], lengthCell))
		if len(rows) != i+1 {
			b.WriteByte('|')
		}
	}
	b.WriteByte('\n')
	fmt.Fprintln(&b, strings.Repeat("-", separateLineLength))

	// body

	for i, mapa := range maps {
		b.WriteString(center(cols[i], firstColLen) + "|")

		for i, key := range rows {

			b.WriteString(cellValue(mapa[key], lengthCell))
			if len(rows) != i+1 {
				b.WriteByte('|')
			}
		}
		b.WriteByte('\n')
		fmt.Fprintln(&b, strings.Repeat("-", separateLineLength))
	}

	return b.String(), nil

}
