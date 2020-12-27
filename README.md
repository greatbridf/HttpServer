# HttpServer

# build and installation

For debugging, run the following command
``` bash
cmake --config=Debug <destination>
```

For releasing, run the following command
``` bash
cmake --config=Release -DCMAKE_INSTALL_PREFIX=<install prefix> <destination>
cd <destination>
make && make install
```

# usage
to show compile flags, run:
``` bash
./HttpParser --print-compile-flags
```
