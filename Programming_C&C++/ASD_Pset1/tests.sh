n=0
while read -r line
do
    var=$(echo $line | xargs -L1 ./tests/tests {})
    code=$?
    n=$((n+1))
    if (( $code > 0 )); then
      echo "Code is" $n, $code 
      l=$(echo $line | sed -e "s/ /,/g")
      echo "{" $l "}"
    fi
done < "tests/tests.txt"
