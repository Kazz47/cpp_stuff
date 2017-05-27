mkdir build
pushd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j
make test
popd
