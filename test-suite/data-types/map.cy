main {
    decl map = {{}}
    call assert(map, {{}}, "Empty map")
    map["foo"] = "bar"
    call assert(map["foo"], "bar", "Map insert")
    call assert(map["j"], nil, "Empty map index")
    map["foo"] = "b"
    call assert(map["foo"], "b", "Map reassign")
    call assert(map, {{"foo":"b", "j" : nil}}, "Map compare")
    map["a"] = [1,2,3]
    call assert(map["a"], [1,2,3], "Map nested structure")
    map["b"] = {{}}
    call assert(map["b"], {{}}, "Map inside map")
    decl b = {{}}
    call assert(map["b"], b, "Structural compare")
}