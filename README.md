# HttpServer

# build and installation

Be aware that the default configuration and plugin directory
relies directly on CMAKE_INSTALL_PREFIX you assigned on compiling
So when you compile it, be sure to set it properly to what you'd
like to place it in.

For auto completion tools such as YouCompleteMe, compile_commands.json
file will be automatically generated and placed in the root of the
project when build type is set to Debug.

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
