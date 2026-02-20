main {
    decl freqs = {{}}
    decl myNums = [1,1,1,2]

    for (decl i = 0, (i < 4), i = (i + 1)){
        decl nextNum = myNums[i]
        if (!freqs[nextNum]){
            freqs[nextNum] = 1
        }else{
            freqs[nextNum] = (freqs[nextNum] + 1)
        }
    }

    call print(freqs, "\n")
    call assert((freqs == {{1:3, 2:1}}), true, "Map equals")
    decl myI = 0xff
    decl map2 = {{
        "foo" : myI
    }}

    map2["foo"] = (-myI * 2)
    map2[myI] = myI
    map2[myI] = "bar"
    call print(myI, map2)
}