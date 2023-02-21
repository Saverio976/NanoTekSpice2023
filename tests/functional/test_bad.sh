echo "Testing bad file..."
for FILE in $(ls tests/nts_files/bad/*.nts | sort)
do
    output=$(echo -n "" | ./nanotekspice $FILE 2>&1)
    RES=$?
    if [ "$RES" != 84 ]
    then
        echo "Unexpected code $RES for $FILE"
        echo "output: [$error_msg]"
        echo
        exit
    fi
done
echo "Bad file OK"
echo
