# 获得代码

bost的实现中的一个文件夹名称为aux，这在windows中为保留字
如果在windows下进行clone，aux文件为空
所以在clone代码时应该在ubuntu环境下

# build

```bash
# to build the libraries
scons deps
# to build the sophos itself
scons
```

# 功能测试

需要首先删除sophos/14e5.csdb/ 和 sophos/14e5.ssdb

```bash
sh ./scripts/clear.sh
```

服务器端
```bash
./server -b /tmp/sophos.ssdb
```

客户端
```bash
# 生成100000个keyword-document对
./client -b /tmp/14e5.csdb -r 100000
# 生成100000个随机keyword-document对，将输出记录在/tmp/output.txt
./client -b /tmp/14e5.csdb -r 100000 -o /tmp/output.txt
# 生成10000个随机keyword-document对，将client端的输出记录在benchmark_client.10.out
./client -b /tmp/14e5.csdb -r 100000 -v benchmark_client.100000.out
```

```bash
# 以四线程运行trace_evl
./client -b /tmp/14e5.csdb -f 4
```

```bash
# 使用指定的关键词生成10个keyword-document对
./client -b /tmp/14e5.csdb -u keyword_10e1 -c 10 -v benchmark_client_10e1.update.out
./client -b /tmp/14e5.csdb -u keyword_10e2 -c 100
./client -b /tmp/14e5.csdb -u keyword_10e3 -c 1000
./client -b /tmp/14e5.csdb -u keyword_10e4 -c 10000
./client -b /tmp/14e5.csdb -u keyword_10e5 -c 100000
```

```bash
# use the enwiki dataset to update the database
./client -b /tmp/sophos.csdb -x /tmp/filename_keywords.db -m 100 -v benchmark_client.out
```


```bash
# 搜索
./client -b /tmp/sophos.csdb keyword_10e1
```
