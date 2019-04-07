#include <iostream>
#include "DistSSE.Util.h"
#include "logger.h"

int m = 100;
// 用来生成 kw
byte k_s[17] = "0123456789abcdef";
byte iv_s[17] = "0123456789abcdef";

// 用来生成 kw
byte k_s_256[33] = "0123456789abcdef0123456789abcdef";
byte iv_s_256[33] = "0123456789abcdef0123456789abcdef";


// 对token加密
std::string enc(const std::string token) {
    std::string token_padding;
    std::string enc_token;
    try {
        CFB_Mode<AES>::Encryption e;
        e.SetKeyWithIV(k_s, AES128_KEY_LEN, iv_s, (size_t) AES::BLOCKSIZE);
        token_padding = DistSSE::Util::padding(token);
        byte cipher_text[token_padding.length()];
        e.ProcessData(cipher_text, (byte *) token_padding.c_str(), token_padding.length());
        enc_token = std::string((const char *) cipher_text, token_padding.length());
    } catch (const CryptoPP::Exception &e) {
        std::cerr << "in gen_enc_token() " << e.what() << std::endl;
        exit(1);
    }
    return enc_token;
}


std::string dec(const std::string enc_token) {
    // 仅仅用来测试token是否加密正确，最后返回的字符串需要去掉padding
    std::string token;
    try {
        CFB_Mode<AES>::Decryption d;

        d.SetKeyWithIV((byte *) k_s, AES128_KEY_LEN, (byte *) iv_s, (size_t) AES::BLOCKSIZE);
        size_t cipher_length = enc_token.length();
        byte plain_text[cipher_length];
        d.ProcessData(plain_text, (byte *) enc_token.c_str(), cipher_length);
        token = std::string((const char *) plain_text, cipher_length);
    }
    catch (const CryptoPP::Exception &e) {
        std::cerr << "in Dec() " << e.what() << std::endl;
        exit(1);
    }
    return DistSSE::Util::remove_padding(token);
}



// 对token加密
std::string enc_256(const std::string token) {
    std::string token_padding;
    std::string enc_token;
    try {
        CFB_Mode<AES>::Encryption e;
        e.SetKeyWithIV(k_s_256, AES256_KEY_LEN, iv_s_256, (size_t) AES::BLOCKSIZE);
        token_padding = DistSSE::Util::padding(token);
        byte cipher_text[token_padding.length()];
        e.ProcessData(cipher_text, (byte *) token_padding.c_str(), token_padding.length());
        enc_token = std::string((const char *) cipher_text, token_padding.length());
    } catch (const CryptoPP::Exception &e) {
        std::cerr << "in gen_enc_token() " << e.what() << std::endl;
        exit(1);
    }
    return enc_token;
}


std::string dec_256(const std::string enc_token) {
    // 仅仅用来测试token是否加密正确，最后返回的字符串需要去掉padding
    std::string token;
    try {
        CFB_Mode<AES>::Decryption d;

        d.SetKeyWithIV((byte *) k_s_256, AES256_KEY_LEN, (byte *) iv_s_256, (size_t) AES::BLOCKSIZE);
        size_t cipher_length = enc_token.length();
        byte plain_text[cipher_length];
        d.ProcessData(plain_text, (byte *) enc_token.c_str(), cipher_length);
        token = std::string((const char *) plain_text, cipher_length);
    }
    catch (const CryptoPP::Exception &e) {
        std::cerr << "in Dec() " << e.what() << std::endl;
        exit(1);
    }
    return DistSSE::Util::remove_padding(token);
}

int binary_seacher(std::vector<int> &v, int target){
    if (v.empty())
        return -1;
    int index1 = 0, index2 = v.size() - 1, mid = 0;
    while (index1 <= index2){
        mid = (index1 + index2) / 2;
        if (v[mid] == target)
            return mid;

        if (v[mid] > target)
            index2 = mid-1;
        if (v[mid] < target)
            index1 = mid+1;
    }
    return -1;
}


int test1(int n){
    int times = n * log(n) * log(n) + n;
    std::cout <<"times of decryption & encryption: " <<times << std::endl;
    // 测试机正确性
    std::cout << dec_256(enc_256("hello")) << std::endl;

    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
    for(int i=0;i<times;i++){
        dec_256(enc_256("hello"));
    }
    gettimeofday(&t2, NULL);
    std::cout << ">> time of decryption & encryption: " << ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0 << " ms" << std::endl;
    return 0;
}

int test2(int n){
    int target = random(n);
    int sqrt_m = std::sqrt(m);
    std::cout <<"number of elements to be walked through: " <<sqrt_m << std::endl;
    std::cout <<"target of binary search is: " <<target << std::endl;
    std::vector<int> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = i;
    }
    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
    binary_seacher(v, target);
    for(int i=0;i<sqrt_m;i++){
        int temp = v[i];
    }
    gettimeofday(&t2, NULL);
    std::cout << ">> time of search & walk throgh: " << ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0 << " ms" << std::endl;
    return 0;
}

int test256And512(){
    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
    for(int i=0;i<1000;i++){
        dec_256(enc_256("hello"));
    }
    gettimeofday(&t2, NULL);
    std::cout << ">> time of search & walk throgh: " << ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0 << " ms" << std::endl;

    gettimeofday(&t1, NULL);
    for(int i=0;i<1000;i++){
        dec(enc("hello"));
    }
    gettimeofday(&t2, NULL);
    std::cout << ">> time of search & walk throgh: " << ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0 << " ms" << std::endl;
    return 0;
}
int main() {
    //int arr[5] = {31928,72900,100951,146400,200704};
    int arr[5] = {20000,40000,60000,80000,100000};
    for(int i=0;i<5;i++){
        m = arr[i];
        std::cout <<"m: " <<m << std::endl;
        int n = m + std::sqrt(m);
        test1(n);
        test2(n);
    }
     return 0;
}
