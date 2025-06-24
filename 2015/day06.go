package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	f, _ := os.Open("../input.txt")
	fileScanner := bufio.NewScanner(f)

	res := 0
	val := make([][]int, 1000)
	for i := 0; i < 1000; i++ {
		val[i] = make([]int, 1000)
	}
	// apply := func(src string, dst string, option int) {
	// 	p1 := strings.Split(src, ",")
	// 	p2 := strings.Split(dst, ",")
	// 	x1, _ := strconv.Atoi(p1[0])
	// 	y1, _ := strconv.Atoi(p1[1])
	// 	x2, _ := strconv.Atoi(p2[0])
	// 	y2, _ := strconv.Atoi(p2[1])
	// 	for i := x1; i <= x2; i++ {
	// 		for j := y1; j <= y2; j++ {
	// 			switch option {
	// 			case 0:
	// 				val[i][j] ^= 1
	// 			case 1:
	// 				val[i][j] = 1
	// 			case 2:
	// 				val[i][j] = 0
	// 			}

	// 		}
	// 	}
	// }

	apply2 := func(src string, dst string, option int) {
		p1 := strings.Split(src, ",")
		p2 := strings.Split(dst, ",")
		x1, _ := strconv.Atoi(p1[0])
		y1, _ := strconv.Atoi(p1[1])
		x2, _ := strconv.Atoi(p2[0])
		y2, _ := strconv.Atoi(p2[1])
		for i := x1; i <= x2; i++ {
			for j := y1; j <= y2; j++ {
				switch option {
				case 0:
					val[i][j] += 2
				case 1:
					val[i][j]++
				case 2:
					val[i][j]--
					if val[i][j] < 0 {
						val[i][j] = 0
					}
				}

			}
		}
	}

	for fileScanner.Scan() {
		s := fileScanner.Text()

		arr := strings.Split(s, " ")

		// if arr[0] == "toggle" {
		// 	apply(arr[1], arr[3], 0)
		// } else {
		// 	if arr[1] == "on" {
		// 		apply(arr[2], arr[4], 1)
		// 	} else {
		// 		apply(arr[2], arr[4], 2)
		// 	}
		// }

		// part 2
		if arr[0] == "toggle" {
			apply2(arr[1], arr[3], 0)
		} else {
			if arr[1] == "on" {
				apply2(arr[2], arr[4], 1)
			} else {
				apply2(arr[2], arr[4], 2)
			}
		}
	}
	for i := 0; i < 1000; i++ {
		for j := 0; j < 1000; j++ {
			res += val[i][j]
		}
	}
	fmt.Print(res)
}
