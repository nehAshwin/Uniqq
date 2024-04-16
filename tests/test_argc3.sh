# Create a file with a test input
echo "0123456789bcdefimjusttypingsmthere" > xd_input.txt


# Run your binary with the test input and redirect the output and errors to a separate file
./uniqq xd_input.txt blank
my_returncode=$?

# Compare the return codes.
if [ 127 -ne $my_returncode ] ; then
    echo "Return codes don't match!"
    rm xd_input.txt
    exit 1
fi

# Everything matches as expected!
echo "Working Correctly"
rm xd_input.txt
exit 0
