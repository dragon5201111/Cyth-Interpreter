func foo(a){}

main {
    decl myHex = call hex(call number("521"))
    if ((myHex == "0x209")){
        call print("Yay!")
    }
}