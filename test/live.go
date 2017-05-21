package main

/*
#cgo linux LDFLAGS: -L../lib
#cgo linux LDFLAGS: -lcalculus
#cgo linux  CFLAGS: -I../include
#include <calculus.h>
*/
import "C"

import (
	"bufio"
	"fmt"
	"os"
	"unsafe"
)

func main() {
	var result [1]float64

	reader := bufio.NewReader(os.Stdin)

	for {
		text, err := reader.ReadString('\n')
		if err != nil {
			fmt.Println(err)
			break
		}
		if len(text) == 1 {
			break
		}
		C.parse(0, (*C.double)(unsafe.Pointer(&result[0])), C.CString(text))
		fmt.Println(">> ", result[0])
	}

}
