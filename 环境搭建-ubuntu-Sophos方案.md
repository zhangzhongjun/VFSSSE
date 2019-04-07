# 环境

```bash
sudo apt-get install -y build-essential autoconf libtool pkg-config
sudo apt-get install -y yasm openssl scons libssl-dev
sudo apt-get install -y libboost-dev
```

# 获得代码

获得主代码

```bash
 git clone https://gitlab.com/sse/sophos.git
```

获得第三方代码

```bash
git submodule update --init
```

# building

Building is done through SConstruct.
To build the submodules, you can either run

```bash
 $ scons deps
```

or do it by hand:

```bash
$ (cd third_party/crypto; scons lib); 
$ (cd third_party/ssdmap; scons lib); 
$ (cd third_party/db-parser; scons lib); 
```

Then, to build Sophos itself, just enter in your terminal
```bash
$ scons 
```

# 问题1

libssl-dev版本过高问题：bost的方案中使用的版本为1.0.0；如果你安装的是1.1.0版本的，则会出现找不到AES_CTR加密函数的问题

您可以使用以下列表中的任何一个源镜像只要往您的 /etc/apt/sources.list 文件中像下面这样添加一行：
```bash
deb http://security.debian.org/debian-security jessie/updates main 
```

然后
```bash
aptitude update
aptitude install libssl1.0-dev
```

# 问题2

rocksdb的options问题：bost的方案中使用的rocksdb版本较低，有不支持的options，把报错的位置注释即可