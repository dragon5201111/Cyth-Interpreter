main {
    decl x = 1
    x >>= 1
    call print(x, " r-shift - should be 0.")
    x+= 1
    call print(x, " add - should be 1.")
    x <<= 1
    call print(x, " l-shift - should be 2.")
    x -= 1
    call print(x, " sub - should be 1.")
    x *= (5 + 1)
    call print(x, " mult - should be 6.")
    x /= 2
    call print(x, " div - should be 3.")
    x %= 2
    call print(x, " mod - should be 1.")
    x &= 1
    call print(x, " b-and - should be 1.")
    x |= 1
    call print(x, " b-or - should be 1.")

    decl x = [1]
    x[0] += 1
}