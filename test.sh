echo "Compiling..."
make

echo "Running test 1..."
./disassem tests/test1/test.obj tests/test1/test.sym
diff -w out.lst tests/test1/out.lst

echo "Running test 2..."
./disassem tests/test2/test.obj tests/test2/test.sym
diff -w out.lst tests/test2/out.lst
