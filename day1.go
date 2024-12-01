package main

import (
	"bufio"
	"errors"
	"os"
	"sort"
	"strconv"
)

func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func read(scanner bufio.Scanner) []int {
	scanner.Split(bufio.ScanLines)
	var lines []int

	for scanner.Scan() {
		i, err := strconv.Atoi(scanner.Text())
		check(err)
		lines = append(lines, i)
	}
	return lines
}

func distance(list1, list2 []int) (int, error) {
	if len(list1) != len(list2) {
		return -1, errors.New("slices must be of equal length")
	}
	sort.Ints(list1)
	sort.Ints(list2)

	var sum int
	for i := 0; i < len(list1); i++ {
		sum += abs(list1[i] - list2[i])
	}
	return sum, nil
}

func score(l1, l2 []int) int {
	counts := make(map[int]int)

	for i := 0; i < len(l2); i++ {
		counts[l2[i]] += 1
	}

	var score int
	for i := 0; i < len(l1); i++ {
		score += l1[i] * counts[l1[i]]
	}
	return score
}

func read_file(name string) []int {
	f, err := os.Open(name)
	check(err)
	defer f.Close()
	scanner := bufio.NewScanner(f)
	return read(*scanner)
}

func main() {
	list1 := read_file("./day1_list1.dat")
	list2 := read_file("./day1_list2.dat")

	d, err := distance(list1, list2)
	check(err)
	println("distance:", d)
	println("score:", score(list1, list2))
}
