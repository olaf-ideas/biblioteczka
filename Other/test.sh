for ((i=0;;i++)); do
  ./$1 $i > in
  diff <(./$2 < in) <(./$3 < in) || break
  echo -e "$i: \e[92mAC\e[39m"
  rm in
done
