package main

import "testing"

func TestDistance(t *testing.T) {
	list1 := read_file("./day1_list1.dat")
	list2 := read_file("./day1_list2.dat")

	got, _ := distance(list1, list2)
	want := 1197984

	if got != want {
		t.Errorf("got %q want %q", got, want)
	}
}

func TestScore(t *testing.T) {
	list1 := read_file("./day1_list1.dat")
	list2 := read_file("./day1_list2.dat")

	got := score(list1, list2)
	want := 23387399

	if got != want {
		t.Errorf("got %q want %q", got, want)
	}
}
