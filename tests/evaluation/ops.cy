main {
    # Integers
    call assert((1 + 1), 2, "Addition failed")
    call assert((1 - 1), 0, "Subtraction failed")
    call assert((1 / 1), 1, "Division failed")
    call assert((1 * 2), 2, "Multiplication failed")
    call assert((1 << 1), 2, "Left Shift failed")
    call assert((1 >> 1), 0, "Right Shift failed")
    call assert(-(1 + 1), -2, "Negation failed")
}