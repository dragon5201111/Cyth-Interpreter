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
        if ((i == 19)){
            continue
        }

        if ((i == 6)){
            call print("Broke at 6!", "\n")
            break
        }
    }

    decl str = "f_o bar"
    for (decl j = 0, (j < 7), j = (j + 1)){
        if ((j == 1)){
            continue
        }
        call print(str[j][1])
    }

    return i
}