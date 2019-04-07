# 功能测试
## 服务器
```bash
# 数据库的路径 缓存数据的路径 线程数
./rpc_server /tmp/my.sdb /tmp/my.scadb 1 benchmark_server.out
```

## 客户端
```bash
# 更新1个keyword-filename对
./rpc_client /tmp/my.cdb 1

# 更新3个keyword-filename对
./rpc_client /tmp/my.cdb 2

# 查询
./rpc_client /tmp/my.cdb 3
```

# 正式测试

## 服务器端
```bash
# 数据库的路径 缓存数据的路径 线程数
./rpc_server /tmp/my.sdb /tmp/my.scadb 1 benchmark_server.out
```
## Update
```bash
# 数据库的路径、实体数、关键词、flag、线程数
./rpc_client /tmp/my.cdb 10 keyword_10e1 2 1 benchmark_client_10e1.update.out
./rpc_client /tmp/my.cdb 100 keyword_10e2 2 1 benchmark_client_10e2.update.out
./rpc_client /tmp/my.cdb 1000 keyword_10e3 2 1 benchmark_client_10e3.update.out
./rpc_client /tmp/my.cdb 10000 keyword_10e4 2 1 benchmark_client_10e4.update.out
./rpc_client /tmp/my.cdb 100000 keyword_10e5 2 1 benchmark_client_10e5.update.out
```
## Search
```bash
# 数据库的路径、实体数、关键词、flag、线程数
./rpc_client /tmp/my.db 4 keyword_10e1 3 1 benchmark_client_10e1.out
./rpc_client /tmp/my.db 4 keyword_10e2 3 1 benchmark_client_10e2.out
./rpc_client /tmp/my.db 4 keyword_10e3 3 1 benchmark_client_10e3.out
./rpc_client /tmp/my.db 4 keyword_10e4 3 1 benchmark_client_10e4.out
./rpc_client /tmp/my.db 4 keyword_10e5 3 1 benchmark_client_10e5.out
```

# 核心代码
```cplusplus
gen_update_token(){
    sc = get_search_time(w);
    tw = gen_enc_token(w);
    uc = get_update_time(w);
    l = Util::H1(tw + std::to_string(uc + 1));
    e = Util::Xor(op + ind, Util::H2(tw + std::to_string(uc + 1)));
    set_update_time(w, uc + 1);
    // 在search_time存放证据
    set_search_time(w, Xor(sc, ind));
}

gen_search_token(){
    tw = gen_enc_token(w);
    uc = get_update_time(w);
}

search() {
    for(i=uc to 1){
        u = H1(tw + uc);
        e = get(u);
        (op, ind) = Xor(e, u);
    }
}
```

# 使用脚本

测试update的时间
```bash
sh ./scripts/update_batch.sh
sh ./scripts/update_out.sh
```

测试search的时间
```bash
sh ./scripts/search_batch.sh
sh ./scripts/search_out.sh
```