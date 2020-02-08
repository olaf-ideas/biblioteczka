make $1
make $2
maka $3
for ((i=0;i<=1000000;i++)); do
    echo $i
    ./$1 $i > $i.in
    ./$2 < $i.in > $i.brut
    ./$3 < $i.in > $i.out
    diff $i.brut $i.out || break
    rm $i.in $i.brut $i.out
done
