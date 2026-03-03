main {
    decl myFile = call open("../test-files/containers/test.txt", "r")
    while (true){
        decl line = call readLine(myFile)
        if (!line){
            break
        }

        call print(line, "\n")
    }
    return 22
}