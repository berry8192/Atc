:let total = 0
:while 1
: let str = input('文字列を入力してください:')
: if str == ""
: break
: endif
: let first_half = str[:len(str)/2]
: let second_half = str[len(str)/2:]
: let first_half_chars = {}
: for c in split(first_half, "")
: if c >= 'a' && c <= 'z'
: let first_half_chars[c] = 1
: elseif c >= 'A' && c <= 'Z'
: let first_half_chars[c] = 1
: endif
: endfor
: for c in split(second_half, "")
: if c >= 'a' && c <= 'z'
: if exists(first_half_chars, c, 0)
: let total += (ord(c) - ord('a') + 1)
: endif
: elseif c >= 'A' && c <= 'Z'
: if exists(first_half_chars, c, 0)
: let total += (ord(c) - ord('A') + 27)
: endif
: endif
: endfor
:endwhile
:echo "合計点: " . total