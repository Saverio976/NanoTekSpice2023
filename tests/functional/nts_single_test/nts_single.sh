error_happend=0

for FILE in $(ls tests/nts_files/single/*.nts | sort)
do
    error_msg=$(echo -n "" | ./nanotekspice $FILE 2>&1 >/dev/null)
    if [ $? -ne 0 ]
    then
        error_happend=84
        echo "Failed to load $FILE"
        echo "$error_msg"
        echo ""
    fi
done

exit $error_happend
