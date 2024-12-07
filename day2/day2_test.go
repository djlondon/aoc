package main

import "testing"

func TestSafe(t *testing.T) {
	safe := [][]int{
		{7, 6, 4, 2, 1},
		{1, 3, 6, 7, 9},
	}
	unsafe := [][]int{
		{1, 2, 7, 8, 9},
		{9, 7, 6, 2, 1},
		{1, 3, 2, 4, 5},
		{8, 6, 4, 4, 1},
	}

	for _, e := range safe {
		assertEq(t, isSafe(e), true)
	}

	for _, e := range unsafe {
		assertEq(t, isSafe(e), false)
	}
}

func assertEq[T comparable](t testing.TB, got, want T) {
	t.Helper()
	if got != want {
		t.Errorf("got %v want %v", got, want)
	}
}
