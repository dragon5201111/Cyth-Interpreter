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
    decl myDubs = {0.25, 0.25, 0.5}
    call print(myDubs)
}