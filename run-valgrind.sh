# Build
cd build
cmake ../ -DCMAKE_BUILD_TYPE=Debug
make
# Run unit tests
cd ../bin
valgrind --leak-check=full --track-origins=yes ./run_tests