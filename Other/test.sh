for ((i=0;;i++)); do
    echo -n "$i: "
    ./$1 $i > in
    diff <(./$2 < in) <(./$3 < in) || break
    echo -e "\e[92mAC\e[39m"    
    rm in
done
