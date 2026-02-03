main {
    decl i = 77

    for (decl i = 1, (i < 2), i = (i + 1)) {
        for (decl i = 10, (i < 11), i = (i + 1)) {
            for (decl i = 100, (i < 1000), i = (i + 1)) {
                if ((i == 105)) {
                    break
                }
            }
            call print(i) #// Expect: 10
        }
        call print(i) #// Expect: 1
    }

    call print(i) #// Expect: 77
    return 666
}