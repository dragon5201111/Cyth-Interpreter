main {
    decl i = 10
    decl j = 5
    call print((i - j), "\n")
    call print((i + j), "\n")
    call print((i / j), "\n")
    call print((i * j), "\n")
    call print((i >> j), "\n")
    call print((i << j), "\n")
    call print((i | j), "\n")
    call print((i & j), "\n")
    call print((i > j), "\n")
    call print((i < j), "\n")
    call print((i >= j), "\n")
    call print((i <= j), "\n")
    call print((i == j), "\n")
    call print((i != j), "\n")
    call print((i ^ j), "\n")
    decl myA = [1,2,3,4]
    myA[0] = 23
    call print(myA[0], myA)
}