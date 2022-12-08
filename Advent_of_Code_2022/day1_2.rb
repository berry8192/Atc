ans=Array.new(4, 0)
tmp=0
while 1 do
    line=gets.chomp
    break if line=='end'
    tmp+=line.to_i
    if line==""
        ans[0]=tmp
        ans.sort!
        tmp=0
    end
end
p ans[1..3].sum