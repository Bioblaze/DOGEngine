
mkdir -p build

cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=/usr/local/share/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_CXX_COMPILER=g++
cmake --build .
cd ..