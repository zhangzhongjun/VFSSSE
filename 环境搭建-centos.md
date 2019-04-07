# RocksDB

> https://github.com/facebook/rocksdb
> 平台：centos 7

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
# 获得librocksdb.a
make static_lib
# 获得librocksdb.so
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

如果是ubuntu，则参考官方文档会顺利的安装完成
> 平台：下面给出centos系统的安装步骤


## 安装build essential

```bash
yum groups mark install "Development Tools"
yum groups mark convert "Development Tools"
yum groupinstall "Development Tools"
```

## 安装cmake

```bash
yum install -y cmake
```

## 安装autoconf

```bash
yum install -y autoconf
```

## 安装libtool

```bash
yum install -y libtool
```

##  编译

```bash
git clone -b $(curl -L https://grpc.io/release) https://github.com/grpc/grpc
cd grpc
git submodule update --init
```

如果上面一条指令发生错误，则

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

## 安装protobuf

```bash
# cd third_party/protobuf
# make && sudo make install
```

## 配置环境变量

首先确认pkgconfig的位置，我的电脑是`usr/local/lib/pkgconfig`

```bash
# export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
```

添加动态库的位置，否则找不到`libgrpc++.so.1`等动态库的位置

```bash
# vi /etc/ld.so.conf.d/grpc.conf
# 添加一行 "/usr/local/lib"
# ldconfig
```

## 运行示例程序

```bash
cd grpc/examples/cpp/helloworld
make
./greeter_server
./greeter_client
```
