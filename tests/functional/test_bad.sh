error_happend=0

echo "Testing bad file..."
for FILE in $(ls tests/nts_files/bad/*.nts | sort)
do
    output=$(echo -n "" | ./nanotekspice $FILE 2>&1)
    RES=$?
    if [ "$RES" != 84 ]
    then
        error_happend=84
        echo "Unexpected code $RES for $FILE"
        echo "output: [$error_msg]"
        echo ""
    fi
done

if [ "$error_happened" != 0 ]
then
    echo "Bad files KO"
    exit $error_happend
else
    echo "Bad files OK"
fi
