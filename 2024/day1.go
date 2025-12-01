package main

import (
	"aoc/util"
	"bufio"
	"errors"
	"os"
	"sort"
)

func distance(list1, list2 []int) (int, error) {
	if len(list1) != len(list2) {
		return -1, errors.New("slices must be of equal length")
	}
	sort.Ints(list1)
	sort.Ints(list2)

	var sum int
	for i := 0; i < len(list1); i++ {
		sum += util.Abs(list1[i] - list2[i])
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

func readFile(name string) []int {
	f, err := os.Open(name)
	util.Check(err)
	defer f.Close()
	scanner := bufio.NewScanner(f)
	return util.Read(*scanner)
}

func main() {
	list1 := readFile("./day1_list1.dat")
	list2 := readFile("./day1_list2.dat")

	d, err := distance(list1, list2)
	util.Check(err)
	println("distance:", d)
	println("score:", score(list1, list2))
}
