# Leet-code problem 258
func addDigits(num){
    if ((num <= 9)){
        return num
    }

    decl sum = 0
    for(, (num > 0), num = (num / 10)){
        sum = (sum + (num % 10))
    }

    return sum
}

main {
    call print(call addDigits(1111))
}