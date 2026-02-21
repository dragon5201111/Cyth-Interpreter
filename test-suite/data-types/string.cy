main {
    decl str = "f"
    call assert((str + "b"), "fb", "String add")
    call assert(str, "f", "String add doesn't modify string")
    str = "b"
    call assert(str, "b", "String reassign")
    str[0] = "c"
    call assert(str, "c", "String index reassign")
    str = "foo"
    str[1] = "a"
    call assert(str, "fao", "String middle index reassign")
    call assert(("fao" == str), true, "String compare")
    call assert(("fao" != str), false, "String false compare")
}