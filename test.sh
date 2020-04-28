make $1
make $2
make $3
for ((i=0;i<=1000000;i++)); do
    ./$1 $i > $i.in
    diff <(./$2 < $i.in) <(time ./$3 < $i.in) || break
    echo -e "$i: \e[92mAC\e[39m"
    rm $i.in
done
