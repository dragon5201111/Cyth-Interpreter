main {
    decl age = call number(call input("Enter your age:"))
    if ((age < 18)){
        call print("Access denied, too young.")
    }else{
        call print("Access granted.")
    }

    call exit(0)
}