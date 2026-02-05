func foo(a){}

main {
    decl myHex = call hex(call number("521"))
    if ((myHex == "0x209")){
        call print("Yay!", "\n")
    }
    call print("Max number:", call hex(NUMBER_MAX), "\n")
    call print("Min number:", call hex(NUMBER_MIN))
}