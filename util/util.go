package util

import (
	"bufio"
	"strconv"
)

func Abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}

func Check(e error) {
	if e != nil {
		panic(e)
	}
}

func Read(scanner bufio.Scanner) []int {
	scanner.Split(bufio.ScanLines)
	var lines []int

	for scanner.Scan() {
		i, err := strconv.Atoi(scanner.Text())
		Check(err)
		lines = append(lines, i)
	}
	return lines
}
