package main

import (
	"bufio"
	"fmt"
	"os"
)

type Vertex struct {
	x, y int
}

func main() {
	f, _ := os.Open("../input.txt")
	fileScanner := bufio.NewScanner(f)
	x1, y1, x2, y2 := 0, 0, 0, 0
	m := make(map[Vertex]struct{})
	m[Vertex{x1, y1}] = struct{}{}
	for fileScanner.Scan() {
		s := fileScanner.Text()
		for id, c := range s {
			if id%2 == 0 {
				switch c {
				case '^':
					y1++
				case 'v':
					y1--
				case '<':
					x1--
				case '>':
					x1++
				default:
					fmt.Print(fmt.Errorf("????"))
				}
				m[Vertex{x1, y1}] = struct{}{}
			} else {
				switch c {
				case '^':
					y2++
				case 'v':
					y2--
				case '<':
					x2--
				case '>':
					x2++
				default:
					fmt.Print(fmt.Errorf("????"))
				}
				m[Vertex{x2, y2}] = struct{}{}
			}
		}
	}
	fmt.Println(len(m))
}

// 659
// 1305
