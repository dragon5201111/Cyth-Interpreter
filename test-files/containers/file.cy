main {
    decl list = [1,2,3]
    decl set = {1,2,3}
    decl map = {{
        "one" : 1,
        "two" : 2
    }}

    call put(list, call length(list), 4)
    call put(set, call length(set), 4)
    call put(map, "three", 3)

    call print(list, set, map)
}