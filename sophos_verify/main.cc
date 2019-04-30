#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include <map>
#include <vector>
#include <stdexcept>
#include <csignal>
#include <unordered_set>
#include <unistd.h>

#include <sys/time.h>

#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/base64.h>

#include "logger.h"


int main(int argc, char **argv) {
    // Instantiate the client and channel isn't authenticated

    std::map <std::string, std::string> sc_mapper;

    sc_mapper.insert(std::pair<std::string,std::string>("hello","map works"));

    std::map <std::string, std::string>::iterator iterator;
    iterator = sc_mapper.find("hello");

    if(iterator != sc_mapper.end()){
        std::cout << iterator->second << std::endl;
    }else{
        std::cout << "Do not find" << std::endl;
    }

    DistSSE::logger::set_benchmark_file("benchmark_server.out");

    CryptoPP::AutoSeededRandomPool prng;

    for(int i=0;i<10;i++){
        struct timeval t1, t2;
        int num = 10;
        gettimeofday(&t1, NULL);
        for(int i=0;i<num;i++){
            int ind_len = 16; // AES::BLOCKSIZE = 16
            CryptoPP::byte tmp[ind_len];
            prng.GenerateBlock(tmp, sizeof(tmp));
            std::string ind = (std::string((const char *) tmp, ind_len));
            sc_mapper.insert(std::pair<std::string,std::string>(ind, ind));
        }
        gettimeofday(&t2, NULL);
        DistSSE::logger::log_benchmark()<< std::to_string(num)+" entries "+"update time: "
                                        << ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0 << " ms"
                                        << std::endl;
        sc_mapper.clear();

        num = 100;
        gettimeofday(&t1, NULL);
        for(int i=0;i<num;i++){
            int ind_len = 16; // AES::BLOCKSIZE = 16
            CryptoPP::byte tmp[ind_len];
            prng.GenerateBlock(tmp, sizeof(tmp));
            std::string ind = (std::string((const char *) tmp, ind_len));
            sc_mapper.insert(std::pair<std::string,std::string>(ind, ind));
        }
        gettimeofday(&t2, NULL);
        DistSSE::logger::log_benchmark()<< std::to_string(num)+" entries "+"update time: "
                                        << ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0 << " ms"
                                        << std::endl;
        sc_mapper.clear();

        num = 1000;
        gettimeofday(&t1, NULL);
        for(int i=0;i<num;i++){
            int ind_len = 16; // AES::BLOCKSIZE = 16
            CryptoPP::byte tmp[ind_len];
            prng.GenerateBlock(tmp, sizeof(tmp));
            std::string ind = (std::string((const char *) tmp, ind_len));
            sc_mapper.insert(std::pair<std::string,std::string>(ind, ind));
        }
        gettimeofday(&t2, NULL);
        DistSSE::logger::log_benchmark()<< std::to_string(num)+" entries "+"update time: "
                                        << ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0 << " ms"
                                        << std::endl;
        sc_mapper.clear();

        num = 10000;
        gettimeofday(&t1, NULL);
        for(int i=0;i<num;i++){
            int ind_len = 16; // AES::BLOCKSIZE = 16
            CryptoPP::byte tmp[ind_len];
            prng.GenerateBlock(tmp, sizeof(tmp));
            std::string ind = (std::string((const char *) tmp, ind_len));
            sc_mapper.insert(std::pair<std::string,std::string>(ind, ind));
        }
        gettimeofday(&t2, NULL);
        DistSSE::logger::log_benchmark()<< std::to_string(num)+" entries "+"update time: "
                                        << ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0 << " ms"
                                        << std::endl;
        sc_mapper.clear();

        num = 100000;
        gettimeofday(&t1, NULL);
        for(int i=0;i<num;i++){
            int ind_len = 16; // AES::BLOCKSIZE = 16
            CryptoPP::byte tmp[ind_len];
            prng.GenerateBlock(tmp, sizeof(tmp));
            std::string ind = (std::string((const char *) tmp, ind_len));
            sc_mapper.insert(std::pair<std::string,std::string>(ind, ind));
        }
        gettimeofday(&t2, NULL);
        DistSSE::logger::log_benchmark()<< std::to_string(num)+" entries "+"update time: "
                                        << ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0 << " ms"
                                        << std::endl;
        sc_mapper.clear();
    }



    return 0;
}

