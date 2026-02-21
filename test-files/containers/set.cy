main {
    decl mySet = {1,2,3,3}
    call assert((mySet == {1,2,3}), true, "Sets are equal")
    call assert((mySet != {1,2,3}), false, "Sets are not equal")
}