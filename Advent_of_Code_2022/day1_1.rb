ans=0
tmp=0
while 1 do
    line=gets.chomp
    break if line=='end'
    tmp+=line.to_i
    if line==""
        ans=tmp if ans<tmp
        tmp=0
    end
end
p ans