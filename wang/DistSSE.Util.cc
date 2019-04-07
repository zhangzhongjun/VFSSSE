#include "DistSSE.Util.h"

using namespace CryptoPP;

// 系统参数
int max_keyword_length = 20;
int max_nodes_number = 10;

namespace DistSSE {

    std::string Util::H1(const std::string message) {
        byte buf[SHA256::DIGESTSIZE];
        std::string salt = "01";
        SHA256().CalculateDigest(buf, (byte * )((message + salt).c_str()), message.length() + salt.length());
        return std::string((const char *) buf, (size_t) SHA256::DIGESTSIZE);
    }

    std::string Util::H2(const std::string message) {
        byte buf[SHA256::DIGESTSIZE];
        std::string salt = "02";
        SHA256().CalculateDigest(buf, (byte * )((message + salt).c_str()), message.length() + salt.length());
        return std::string((const char *) buf, (size_t) SHA256::DIGESTSIZE);
    }


    std::string Util::padding(const std::string str) {
        size_t BS = (size_t) AES::BLOCKSIZE;
        size_t pad_len = BS - str.length() % BS;
        return str + std::string(char(pad_len), pad_len);
    }

    std::string Util::remove_padding(const std::string str) {
        int len = str.length();
        int pad_len = int(str[len - 1]);
        bool flag = false;
        for (int i = len - pad_len; i < len; i++) {
            if (int(str[i]) != pad_len){
                flag = true;
                break;
            }
        }
        if (flag) std::cout << "wrong padding" << std::endl;
        else return std::string(str, 0, len - pad_len);
    }

    std::string Util::Xor(const std::string s1, const std::string s2) {
        // std::cout<< "in len = "<< s1.length()<<", s1 = "<<s1<<std::endl;
        std::string result = s1;
        if (s1.length() > s2.length()) {
            //ERROR
            std::cout << "not sufficient size: " << s1.length() << ", " << s2.length() << std::endl;
            return "";
        }

        for (int i = 0; i < result.length(); i++) {
            result[i] ^= s2[i];
        }
        return result;
    }

    void Util::split(const std::string &s, char delim, std::set <std::string> &ID) {
        std::stringstream ss;
        ss.str(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            ID.insert(item);
        }
    }

    void Util::split(const std::string &s, char delim, std::vector <std::string> &elems) {
        std::stringstream ss;
        ss.str(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
    }

/*
std::vector<std::string> Util::split(const std::string &s, char delim) {
		std::vector<std::string> elems;
		split(s, delim, elems);
		return elems;
	}
*/

    std::string Util::dec_token(const void *key, int key_len, const void *iv, std::string enc_token) {
        // 仅仅用来测试token是否加密正确，最后返回的字符串需要去掉padding
        std::string token;
        try {
            CFB_Mode<AES>::Decryption d;

            d.SetKeyWithIV((byte *) key, key_len, (byte *) iv, (size_t) AES::BLOCKSIZE);
            size_t cipher_length = enc_token.length();
            byte plain_text[cipher_length];
            //cout<<enc_token<<endl;
            d.ProcessData(plain_text, (byte *) enc_token.c_str(), cipher_length);
            token = std::string((const char *) plain_text, cipher_length);
        }
        catch (const CryptoPP::Exception &e) {
            std::cerr << "in Dec() " << e.what() << std::endl;
            exit(1);
        }
        return remove_padding(token);
    }

    std::string Util::Enc(const void *key, int key_len, const std::string plain) {

        std::string cipher;

        AutoSeededRandomPool prng;
        byte iv[AES::BLOCKSIZE];
        prng.GenerateBlock(iv, sizeof(iv));
        try {
            CFB_Mode<AES>::Encryption e;

            e.SetKeyWithIV((byte *) key, key_len, iv, (size_t) AES::BLOCKSIZE);
            byte cipher_text[plain.length()];
            e.ProcessData(cipher_text, (byte *) plain.c_str(), plain.length());
            cipher = std::string((const char *) iv, (size_t) AES::BLOCKSIZE) +
                     std::string((const char *) cipher_text, plain.length());
            if (std::string((const char *) iv, (size_t) AES::BLOCKSIZE).size() != (size_t) AES::BLOCKSIZE)
                std::cout << "iv error" << std::endl;
        }
        catch (const CryptoPP::Exception &e) {
            std::cerr << "in Enc() " << e.what() << std::endl;
            exit(1);
        }

        return cipher;
    }

    std::string Util::Dec(const void *key, int key_len, const std::string cipher) {
        std::string plain;
        try {
            CFB_Mode<AES>::Decryption d;

            d.SetKeyWithIV((byte *) key, key_len, (byte *) cipher.c_str(), (size_t) AES::BLOCKSIZE);
            size_t cipher_length = cipher.length() - (size_t) AES::BLOCKSIZE;
            byte plain_text[cipher_length];
            d.ProcessData(plain_text, (byte *) cipher.substr((size_t) AES::BLOCKSIZE).c_str(), cipher_length);
            plain = std::string((const char *) plain_text, cipher_length);
        }
        catch (const CryptoPP::Exception &e) {
            std::cerr << "in Dec() " << e.what() << std::endl;
            exit(1);
        }
        return plain;
    }

    std::string Util::str2hex(const std::string &input) {
        static const char *const lut = "0123456789ABCDEF";
        size_t len = input.length();

        std::string output;
        output.reserve(2 * len);
        for (size_t i = 0; i < len; ++i) {
            const unsigned char c = input[i];
            output.push_back(lut[c >> 4]);
            output.push_back(lut[c & 15]);
        }
        return output;
    }

    std::string Util::hex2str(const std::string &input) {
        static const char *const lut = "0123456789ABCDEF";
        size_t len = input.length();
        if (len & 1) throw std::invalid_argument("odd length");

        std::string output;
        output.reserve(len / 2);
        for (size_t i = 0; i < len; i += 2) {
            char a = input[i];
            const char *p = std::lower_bound(lut, lut + 16, a);
            if (*p != a) throw std::invalid_argument("not a hex digit");

            char b = input[i + 1];
            const char *q = std::lower_bound(lut, lut + 16, b);
            if (*q != b) throw std::invalid_argument("not a hex digit");

            output.push_back(((p - lut) << 4) | (q - lut));
        }
        return output;
    }

}// namespace DistSSE
