Tests in C
----------

[test/calculus.c](test/calculus.c) contains a number of tests.

        $ make
        $ export LD_LIBRARY_PATH=../lib:$LD_LIBRARY_PATH
        $ ./calculus
          1 + 2 = 3.000000
          1 * 2 = 2.000000
          1 / 2 = 0.500000
          2 ** 2 = 4.000000
          [...]

Tests in go
-----------

[test/simple.go](test/simple.go) can be used as "live" calculator.

        $ export LD_LIBRARY_PATH=../lib:$LD_LIBRARY_PATH
        $ go run simple.go 123 + 345
          123 + 345 = 468.000000
        $ go run simple.go 123*9
          123*9 = 1107.000000
        $ go run simple.go xFF + b00001
          xFF + b00001 = 256.000000

Or give [test/live.go](test/live.go) a try:

        $ export LD_LIBRARY_PATH=../lib:$LD_LIBRARY_PATH
        $ go run live.go
          123 + 345
          >> 468.000000
          123*9
          >> 1107.000000
          xFF + b00001
          >> 256.000000
