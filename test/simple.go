package main

/*
#cgo linux LDFLAGS: -L../lib
#cgo linux LDFLAGS: -lcalculus
#cgo linux  CFLAGS: -I../include
#include <calculus.h>
*/
import "C"
import "fmt"
import "unsafe"
import "strings"
import "os"

func main() {
	var input *C.char = C.CString(strings.Join(os.Args[1:], " "))
	var result [1]float64
	C.parse(0, (*C.double)(unsafe.Pointer(&result[0])), input)
	fmt.Printf("%s", C.GoString(input))
	fmt.Printf(" = %f\n", result[0])
}
