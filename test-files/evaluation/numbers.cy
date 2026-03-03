func sort(arr){
    decl arrLength = call length(arr)
    for (decl i = 1, (i < arrLength), i = (i + 1)){
        decl key = arr[i]
        decl j = (i - 1)

        while (((j >= 0) && (key < arr[j]))){
            arr[(j + 1)] = arr[j]
            j = (j - 1)
        }

        arr[(j + 1)] = key
    }
}

main {
    decl arr = ["f", "a", 5b, 1b]
    call sort(arr)
    call print(arr)
}