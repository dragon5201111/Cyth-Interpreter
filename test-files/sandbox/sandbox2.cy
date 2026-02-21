func getFreqs(str, delim){
    decl freqs = {{}}
    decl split = call split(str, delim)

    decl splitLen = call length(split)
    for (decl i = 0, (i < splitLen), i = (i + 1)){
        decl curr = split[i]
        if (!freqs[curr]){
            freqs[curr] = 1
        }else {
            freqs[curr] = (freqs[curr] + 1)
        }
    }
    return freqs
}

main {
    call print(call getFreqs("The brown dog jumped over the brown dog at the market in france.", " "))
}