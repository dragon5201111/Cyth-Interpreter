func foo(){
    decl i = 25
    while (true){
        call print("In foo while i", i, "\n")
        decl i = 22
        call print("In foo while i new", i, "\n")
        break
    }
    i = (i * 2)
        call print("In foo outside while i new", i, "\n")
}

main {
    # Demonstration of binding and loops
    decl i = 20
    call print("main i before for", i, "\n")
    for (,,){
        i = (i + 1)
        call print("main i in for", i, "\n")
        break
    }
   call print("main i before while", i, "\n")
   call foo()
   call print("main i after", i, "\n")
}