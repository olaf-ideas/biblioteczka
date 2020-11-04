for((i=1; ; i++)); do
    echo -n "$i: "
    ./gen $i > in
    ./brute < in > ans
    command time -f "%Mkb %es status: %x" ./gan < in > out 2> log
    diff -bwq ans out || break
    echo -e "$(cat log) \e[92mok\e[39m" 
done
