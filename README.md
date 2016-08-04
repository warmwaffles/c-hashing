# C Hashing

This is just a collection of hashing functions I have found that interest me.

Murmurhash2 and Murmurhash3 have been converted from C++ to C.

## Building

```sh
mkdir build
cd build
cmake ..
make
```

## Goals

  * Make the hashing algorithims more modular
  * Make an interface that doesn't care about implementation

## TODO

 - [ ] murmurhash1 needs tests
 - [ ] murmurhash2 needs tests
 - [ ] murmurhash3 needs tests
 - [ ] SpookyV2 needs tests
 - [ ] xxhash needs tests
 - [ ] metrohash needs tests
 - [ ] metrohash does not compile on osx with SSE 4.1

I do not claim ownership of any of these hashing functions.
