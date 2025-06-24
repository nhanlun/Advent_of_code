package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	f, _ := os.Open("../input.txt")
	fileScanner := bufio.NewScanner(f)

	// vowels := "aeiou"
	// blackList := []string{"ab", "cd", "pq", "xy"}
	res := 0
	for fileScanner.Scan() {
		s := fileScanner.Text()
		// cnt := 0
		// check := true
		// for i := 0; i < len(s); i++ {
		// 	for j := 0; j < len(vowels); j++ {
		// 		if s[i] == vowels[j] {
		// 			cnt++
		// 		}
		// 	}
		// }
		// for i := 0; i < len(blackList); i++ {
		// 	if strings.Contains(s, blackList[i]) {
		// 		check = false
		// 		break
		// 	}
		// }
		// checkConsecutive := false
		// for i := 0; i+1 < len(s); i++ {
		// 	if s[i] == s[i+1] {
		// 		checkConsecutive = true
		// 		break
		// 	}
		// }
		// check = check && checkConsecutive && (cnt >= 3)
		// if check {
		// 	res++
		// }

		check := false
		for i := 0; i+1 < len(s); i++ {
			for j := i + 2; j+1 < len(s); j++ {
				if s[i:i+2] == s[j:j+2] {
					check = true
					break
				}
			}
		}
		check2 := false
		for i := 0; i+2 < len(s); i++ {
			if s[i] == s[i+2] {
				check2 = true
				break
			}
		}
		if check && check2 {
			res++
		}
	}
	fmt.Print(res)
}
