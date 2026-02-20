main {
    decl m = {{
        "foo" : "bar",
        1 : 2
    }}

    m["foo"] = "baz"
    call print(m)
}