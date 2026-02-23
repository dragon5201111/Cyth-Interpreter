func print_mat(mat){
    decl m = call length(mat)
    decl n = call length(mat[0])

    for (decl i = 0, (i < m), i = (i + 1)){
        for (decl j = 0, (j < n), j = (j + 1)){
            call print(mat[i][j], " ")
        }
        call print("\n")
    }
}