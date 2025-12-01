package main

import (
	"aoc/util"
	"bufio"
	"os"
	"strconv"
	"strings"
)

func read(scanner bufio.Scanner) [][]int {
	scanner.Split(bufio.ScanLines)
	var lines [][]int

	for scanner.Scan() {
		s := strings.Split(scanner.Text(), " ")
		result := make([]int, len(s))
		for i, t := range s {
			result[i], _ = strconv.Atoi(t)
		}
		// i, err := strconv.Atoi(scanner.Text())
		// util.Check(err)
		lines = append(lines, result)
	}
	return lines
}

func readFile(name string) [][]int {
	f, err := os.Open(name)
	util.Check(err)
	defer f.Close()
	scanner := bufio.NewScanner(f)
	return read(*scanner)
}

func isSafe(l []int) bool {
	direction := 0
	d := 0
	for i, e := range l {
		if i == len(l)-1 {
			return true
		}
		dif := l[i+1] - e
		if util.Abs(dif) < 1 || util.Abs(dif) > 3 {
			return false
		}
		if dif < 0 {
			d = -1
		} else if dif >= 1 {
			d = 1
		}
		if d != direction && i != 0 {
			return false
		}
		direction = d
	}
	return false
}

func main() {
	list1 := readFile("../day2.dat")
	count := 0
	for _, e := range list1 {
		if isSafe(e) {
			count += 1
		}
	}
	println(count)
}
