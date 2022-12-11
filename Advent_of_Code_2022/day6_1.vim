let filename = "./day6.txt"

let input_str = readfile(filename)
let str = input_str[0]

let len = strlen(str)

for i in range(3,len-1)
    let cnt = 0
    for j in range(i-3,i-1)
        for k in range(j+1,i)
            if str[j]!=str[k]
                let cnt += 1
            endif
        endfor
    endfor
    if cnt==6
        echo i+1
        break
    endif
endfor
