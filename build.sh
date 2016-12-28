mkdir build
pushd build
cmake ..
make -j
make test
popd
