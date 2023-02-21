echo "Testing single..."

for FOLDER in $(find tests/functional/single/* -type d)
do
    cat "$FOLDER/in.txt" | ./nanotekspice "$FOLDER/file.nts" | tail -n +2 | head -n -1 > res.txt
    diff "$FOLDER/out.txt" res.txt > /dev/null
    if [ $? -ne 0 ]
    then
        echo -e "\tTest failed for $FOLDER\n"
        exit 84
    else
        echo -e "\tFolder $FOLDER"
    fi
done

echo "Single OK"
echo
