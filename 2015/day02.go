package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	// dat, _ := os.ReadFile("../input.txt")
	f, _ := os.Open("../input.txt")
	fileScanner := bufio.NewScanner(f)
	sum := 0
	sum2 := 0
	for fileScanner.Scan() {
		s := fileScanner.Text()
		//fmt.Println(s)
		vals := strings.Split(s, "x")
		// fmt.Println(vals)
		a, _ := strconv.Atoi(vals[0])
		b, _ := strconv.Atoi(vals[1])
		c, _ := strconv.Atoi(vals[2])
		if a > b {
			a, b = b, a
		}
		if a > c {
			a, c = c, a
		}
		if b > c {
			b, c = c, b
		}
		// fmt.Println(vals, s, a, b, c)
		sum += (a*b)*3 + (b*c)*2 + (a*c)*2
		sum2 += (a+b)*2 + a*b*c
	}
	fmt.Println(sum)
	fmt.Println(sum2)
}

// 659
// 1305
