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
# generate the database firstly
./rpc_client 1 /tmp/fast.cdb /tmp/filename_keywords.db benchmark_client.out 32770
// there are no parameter indicates the path of log file
// the log of search process can be found in benchmark_server.out
./rpc_client 2 /tmp/fast.cdb 000

./rpc_client 1 /tmp/fast.cdb /tmp/filename_keywords.db benchmark_client.out 65550
./rpc_client 2 /tmp/fast.cdb 000

./rpc_client 1 /tmp/fast.cdb /tmp/filename_keywords.db benchmark_client.out 131090
./rpc_client 2 /tmp/fast.cdb 000

./rpc_client 1 /tmp/fast.cdb /tmp/filename_keywords.db benchmark_client.out 262170
./rpc_client 2 /tmp/fast.cdb 000

./rpc_client 1 /tmp/fast.cdb /tmp/filename_keywords.db benchmark_client.out 524290
./rpc_client 2 /tmp/fast.cdb 000

./rpc_client 1 /tmp/fast.cdb /tmp/filename_keywords.db benchmark_client.out 1048576
./rpc_client 2 /tmp/fast.cdb 000
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