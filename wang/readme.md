<u>此文件夹为王师姐让我测试的时间</u>
# 2019.1.24

1. 测试 【 n(logn)^{2} 次（加密，解密）+ n 次加解密的时间】其中 n = m+sqrt{m}

2. 测试【（二分法访问一个 n 长 array的时间） +（ 遍历 squ{m} 的时间）】



# 代码实现

使用aes128加解密

test1实现功能1

test2实现功能2

# 结果记录

rm -f *.o *.pb.cc *.pb.h test
g++ -std=c++11 `pkg-config --cflags protobuf grpc`  -c -o main.o main.cpp
g++ -std=c++11 `pkg-config --cflags protobuf grpc`  -c -o DistSSE.Util.o DistSSE.Util.cc
g++ -std=c++11 `pkg-config --cflags protobuf grpc`  -c -o logger.o logger.cc
g++ main.o DistSSE.Util.o logger.o -L/usr/local/lib `pkg-config --libs protobuf grpc++ grpc` -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -ldl -lcryptopp -o test

===result===
m: 20000
times of decryption & encryption: 1998355
hello
>> time of decryption & encryption: 8951.86 ms
number of elements to be walked through: 141
target of binary search is: 18321
>> time of search & walk throgh: 0.002 ms
m: 40000
times of decryption & encryption: 4558454
hello
>> time of decryption & encryption: 20635.8 ms
number of elements to be walked through: 200
target of binary search is: 37486
>> time of search & walk throgh: 0.001 ms
m: 60000
times of decryption & encryption: 7357932
hello
>> time of decryption & encryption: 33914.8 ms
number of elements to be walked through: 244
target of binary search is: 41761
>> time of search & walk throgh: 0.001 ms
m: 80000
times of decryption & encryption: 10319339
hello
>> time of decryption & encryption: 46519 ms
number of elements to be walked through: 282
target of binary search is: 54241
>> time of search & walk throgh: 0.001 ms
m: 100000
times of decryption & encryption: 13404234
hello
>> time of decryption & encryption: 59930.1 ms
number of elements to be walked through: 316
target of binary search is: 81053
>> time of search & walk throgh: 0.002 ms

