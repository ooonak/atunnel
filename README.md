# A Tunnel

## Build
```bash
$ mkdir build; cd build
$ cmake -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug ..
$ cmake --build .
$ ./at <port>
```
