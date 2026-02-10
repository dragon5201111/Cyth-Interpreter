main {
    decl i = 0
    for (, (i < 8), i = (i + 1)){
        if ((i == 2)){
            continue
        }
        call print(i, "\n")
    }

    i = 25
    for (decl i = 0, (i < 20), i = (i + 1)){
        if ((i != 19)){
            continue
        }
    }

    return i
}