main {
    decl myStr = "12345"
    for (decl i = 0, (i < 5), i = (i + 1)){
        myStr[i] = "0"
        for (,,){
            # Scoping with indexing
            decl myStr = "12345"
            myStr[i] = "1"
            break
        }
    }
    call print(myStr)
}