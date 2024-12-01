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
		return -1, errors.New("lists must be of equal length")
	}
	sum := 0
	for i := 0; i < len(list1); i++ {
		sum += abs(list1[i] - list2[i])
	}
	return sum, nil
}

func sim_score(l1, l2 []int) int {
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

func main() {
	f, err := os.Open("./day1_list1.dat")
	check(err)
	defer f.Close()

	f2, err := os.Open("./day1_list2.dat")
	check(err)
	defer f2.Close()

	scanner1 := bufio.NewScanner(f)
	list1 := read(*scanner1)
	scanner2 := bufio.NewScanner(f2)
	list2 := read(*scanner2)
	sort.Ints(list1)
	sort.Ints(list2)

	d, _ := distance(list1, list2)
	println("distance:", d)

	println("score:", sim_score(list1, list2))
}
