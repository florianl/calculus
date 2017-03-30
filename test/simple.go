package main

/*
#cgo linux LDFLAGS: -L../lib
#cgo linux LDFLAGS: -lcalculus
#cgo linux  CFLAGS: -I../include
#include <calculus.h>
#include <stdlib.h>
*/
import "C"
import "fmt"
import "unsafe"

func main() {
	var input *C.char = C.CString("0xFFF")
	var result [1]float64
	C.parse(0, (*C.double)(unsafe.Pointer(&result[0])), input)
	fmt.Printf("%#v\n", result)
}
