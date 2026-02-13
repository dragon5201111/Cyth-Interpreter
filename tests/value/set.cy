func foo(){
    return nil
}

main {
    decl mySet = {1,2,1,2}
    call print(mySet, " ")
    call print((mySet == {1,2}), " ")
    call print((mySet != {1,2}))
    decl x = 2
    call foo()
}