main {
    decl m = {{
        "foo" : "bar"
    }}

    m["foo"] = "baz"
    call print(m)
}