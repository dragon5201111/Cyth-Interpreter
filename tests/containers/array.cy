main {
    decl myArr = [1,2,3,4]
    call assert(myArr[0], 1, "Array first element")
    myArr[0] = 22
    call assert(myArr[0], 22, "Array first element reassign")
    myArr[3] = 44
    call assert(myArr[3], 44, "Array last element reassign")
    call assert(([1,2] == [1,2]), true, "Arrays are equal")
    call assert(([1,2] != [1,2]), false, "Arrays are not equal")
    decl mat = [[1, 2], [3, 4]]
    call assert(mat[0][0], 1, "2d Array first element")
    mat[0][0] = 25
    call assert(mat[0][0], 25, "2d Array first element reassign")
    call assert((mat[0][0] + mat[0][1]), 27, "2d Array addition")
    call assert(([[1,2]] == [[1,2]]), true, "2d Arrays are equal")
    call assert(([[1,2]] != [[1,2]]), false, "2d Arrays are equal")
    call print("All tests passed.")
}