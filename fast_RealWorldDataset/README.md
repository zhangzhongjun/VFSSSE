# OnTheRealWorld

# build

```bash
$ make clean
$ make
```

# write to database

open the server

```bash
# path of database, path of cache dadabase, number of threads, path of output log
./rpc_server /tmp/fast.sdb /tmp/fast.scadb 1 benchmark_server.out
```

update

```bash
# path of database, path of sources database, path of log file, number of keyword-document pairs
./rpc_client 1 /tmp/fast.cdb /tmp/filename_keywords.db benchmark_client.out 32769
```

search

```bash
# flag, path of database, keyword
./rpc_client 2 /tmp/fast.cdb hello
```

# core code

```cplusplus
gen_update_token(){
    uc = get_update_time(w);
    tw = gen_enc_token(w);
    l = H1(tw+(uc+1));
    e = XOR((op+ind),H2(tw+(uc+1)))
}
gen_search_token(){
    uc = get_update_time(w);
    tw = gen_enc_token(w);
    kw = gen_enc_token(tw+uc);
}
```

# use scripts
## Update
```bash
sh ./scripts/clear.sh
sh ./scripts/runserver.sh
sh ./scripts/update_batch.sh
sh ./scripts/update_out.sh
```

## Search
```bash
sh ./scripts/clear.sh
sh ./scripts/runserver.sh
sh ./scripts/search_batch.sh
sh ./scripts/search_out.sh
```