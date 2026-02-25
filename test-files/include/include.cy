include "C:\\Users\\drago\\CLionProjects\\Cyth-Interpreter\\test-files\\include\\include4.cy"
include "../lib/math.cy"

main {
    decl a = [
        [0, 1],
        [3, 4]
    ]

    decl b = [
        [1, 0],
        [0, 1]
    ]

    /*
        Adds b into a.
    */
    call print_mat(call add_mat(a, b))
    call print(a)
}