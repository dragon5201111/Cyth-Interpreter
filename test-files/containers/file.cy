main {
    decl myFile = call open("./test.txt", "r")
    call close(myFile)
    decl i = 0
    call print(call id(myFile))
    call print(call id(myFile))

    return 22
}