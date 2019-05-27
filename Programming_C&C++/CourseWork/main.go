package main

import (
	"flag"
	"fmt"
	"log"
	"os"
	"strings"

	cnn "./cnn"
)

// data-3

var (
	file  = flag.String("file", "", "File with input data")
	debug = flag.Bool("debug", false, "Should we seee a debug matrixes?")
)

func init() {
	flag.Parse()
}

func main() {

	fmt.Printf("Debug [%t]\n", *debug)
	fmt.Printf("File  [%s]\n", *file)
	fmt.Println(strings.Repeat("-", 60))
	*file = strings.Trim(*file, " \n\r\t")

	if *file == "" {
		fmt.Fprintln(os.Stderr, "You need to provide a input file")
		os.Exit(1)
	}

	if f, err := os.Stat(*file); os.IsNotExist(err) || os.IsPermission(err) {
		fmt.Fprintf(os.Stderr, "Can't locate or access %s ", *file)
		os.Exit(1)
	} else if f.IsDir() {
		fmt.Fprintf(os.Stderr, "%s is Directory, not a file.", *file)
		os.Exit(1)
	}

	solver(*file, *debug)
}

func solver(file string, debug bool) {

	cnn, err := cnn.Create(file, debug)
	if err != nil {
		log.Fatal(err)
	}

	cnn.PrintGoal()
	cnn.PrintOptions()
	cnn.PrintConvolutions()
	cnn.PrintSolution()
}
