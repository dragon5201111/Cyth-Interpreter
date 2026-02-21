main{
    decl crazy_var = -(~((45 % 9) >> ((1 | (77 & 24)) * 256)) + 254) # This should evaluate to -253
    call print("Crazy Var =", crazy_var)
    # Returns 0 by default
}