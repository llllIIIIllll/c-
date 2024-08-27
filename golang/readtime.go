package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strings"
	"time"
)

func findGaps(times []time.Time) []time.Time {
	sort.Slice(times, func(i, j int) bool {
		return times[i].Before(times[j])
	})

	var gaps []time.Time
	prev := times[0]
	for i := 1; i < len(times); i++ {
		curr := times[i]
		if curr.Sub(prev) > 2*time.Second {
			gaps = append(gaps, prev.Add(2*time.Second))
		}
		prev = curr
	}

	return gaps
}

func main() {
	file, err := os.Open("/tmp/sga.txt")
	if err != nil {
		fmt.Println("Error opening file:", err)
		return
	}
	defer file.Close()

	var times []time.Time
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		t, err := time.Parse("2006-01-02 15:04:05", strings.TrimSpace("2024-04-"+line))
		if err != nil {
			fmt.Println("Error parsing time:", err)
			continue
		}
		times = append(times, t)
	}

	if err := scanner.Err(); err != nil {
		fmt.Println("Error reading file:", err)
		return
	}

	gaps := findGaps(times)
	for _, gap := range gaps {
		fmt.Println(gap)
	}
}
