func flip(n, b){
    return (n ^ (0xFF << (b * 8)))
}
main {
    decl myHex = 0xFF00
    call print(myHex, call flip(myHex, 1))
    decl myFloat = -0.1f
    call print((myFloat + 5))
}