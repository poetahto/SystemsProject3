echo "Compiling..."
make

echo "Running test 1..."
./disassem tests/test1/test.obj tests/test1/test.sym
diff -w out.lst tests/test1/out.lst
rm out.lst