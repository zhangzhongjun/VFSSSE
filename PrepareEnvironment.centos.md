# RocksDB

> https://github.com/facebook/rocksdb
>
> Platform：centos 7

```bash
# gflags
git clone https://github.com/gflags/gflags.git
cd gflags
git checkout v2.0
./configure && make && make install

# snappy snappy-devel
yum install -y snappy snappy-devel

# zlib zlib-devel
yum install -y zlib zlib-devel

# bzip2 bzip2-devel
yum install -y bzip2 bzip2-devel

# lz4
yum install lz4-devel

# ASAN
yum install libasan

# zstandard
wget https://github.com/facebook/zstd/archive/v1.1.3.tar.gz
mv v1.1.3.tar.gz zstd-1.1.3.tar.gz
tar zxvf zstd-1.1.3.tar.gz
cd zstd-1.1.3
make && sudo make install

# RocksDB
git clone https://github.com/facebook/rocksdb.git
cd rocksdb
# get librocksdb.a
make static_lib
# get librocksdb.so
make shared_lib
cp -r ./include/rocksdb /usr/include
cp librocksdb.so.5.18.0 /usr/lib
ln -s /usr/lib/librocksdb.so.5.18.0 /usr/lib/librocksdb.so.5
ln -s /usr/lib/librocksdb.so.5.18.0 /usr/lib/librocksdb.so
```


# cryptopp

```bash
git clone https://github.com/weidai11/cryptopp.git
cd cryptopp
make
make test
make install
```


# grpc

> platform：centos 7


## build essential

```bash
yum groups mark install "Development Tools"
yum groups mark convert "Development Tools"
yum groupinstall "Development Tools"
```

## cmake

```bash
yum install -y cmake
```

## autoconf

```bash
yum install -y autoconf
```

## libtool

```bash
yum install -y libtool
```

##  Compile

```bash
git clone -b $(curl -L https://grpc.io/release) https://github.com/grpc/grpc
cd grpc
git submodule update --init
```

if there is some error occurs, then


```bash
# vi .gitmodules
```

```txt
[submodule "third_party/gflags"]
	    path = third_party/gflags
	    url = https://github.com/tangmi360/gflags.git
```

```bash
# make
# make install
```

## protobuf

```bash
# cd third_party/protobuf
# make && sudo make install
```

## Set environment

make sure where `pkgconfig` is on your computer, mine is `usr/local/lib/pkgconfig`

```bash
# export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
```

set the path of library, otherwise we cannot find where `libgrpc++.so.1` is


```bash
# vi /etc/ld.so.conf.d/grpc.conf
# add the line "/usr/local/lib"
# ldconfig
```

## run the example project

```bash
cd grpc/examples/cpp/helloworld
make
./greeter_server
./greeter_client
```
