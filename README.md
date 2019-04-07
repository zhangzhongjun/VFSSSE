# FAST/FASTIO
Implementation of forward private SSE scheme, including FAST and FASTIO (see https://arxiv.org/abs/1710.00183)

# Pre-requisites
C++11, Crypto++, RocksDB and gRPC

## Installing gRPC
Install gRPC's C++ binding (see [here](https://github.com/grpc/grpc/tree/release-0_14/src/cpp) for the 0.14 release).

## Installing RocksDB
Rocksdb 5.7 release. See the [installation guide](https://github.com/facebook/rocksdb/blob/master/INSTALL.md).

## Getting the code
```sh
 $ git clone -b 2.0 https://github.com/BintaSong/DistSSE
```
please check into 2.0 version for building

# Building
```sh
 $ make
```
