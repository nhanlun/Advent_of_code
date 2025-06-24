package main

import (
	"bufio"
	"crypto/md5"
	"encoding/hex"
	"fmt"
	"os"
	"strings"
)

func main() {
	f, _ := os.Open("../input.txt")
	fileScanner := bufio.NewScanner(f)

	for fileScanner.Scan() {
		s := fileScanner.Text()
		for i := 0; i < 10000000; i++ {
			concatenated := fmt.Sprintf("%s%d", s, i)
			hashed := md5.Sum([]byte(concatenated))
			h := hex.EncodeToString(hashed[:])
			if strings.HasPrefix(h, "000000") {
				fmt.Println(i, h)
				break
			}
		}
		fmt.Printf("%x\n", md5.Sum([]byte(s)))
	}
}
