#include <CommonCrypto/CommonCrypto.h>
#include <iostream>
#include <sstream>

class AESEncrypt {

public:
    std::string getEncrypt(const char data[],const char key[], const char iv[]) {
    
        size_t keyLength = sizeof(&key)/sizeof(char);
        size_t dataLength = sizeof(&data)/sizeof(char);
        unsigned char buffer[1024];
        size_t numBytesEncrypted = 0;

        std::cout << keyLength <<std::endl;
        std::cout << dataLength << std::endl;
        
        //FIXME: parameter err need reference
        CCCryptorStatus cryptorStatus = CCCrypt(
                                kCCEncrypt,
                                kCCAlgorithmAES,
                                kCCOptionECBMode,
                                &key,
                                keyLength,
                                &iv,
                                &data,
                                dataLength,
                                &buffer,
                                1024,
                                &numBytesEncrypted);

        if (cryptorStatus == kCCSuccess) {
            std::string ret;
            std::stringstream ss;
            for(int i = 0 ; i < numBytesEncrypted; ++i) {
                ss << buffer[i];
            }
            return ss.str();
        } else {
            std::cout << cryptorStatus << std::endl;
        }
        return "";
    }
};


class MD5Digest{
private:
    CC_MD5_CTX context;
    
public:
    MD5Digest() {
        CC_MD5_Init(&context);
    }

    std::string getDigest(const char string[]) {
        unsigned char digest[CC_MD5_DIGEST_LENGTH];
        CC_MD5_Update(&context, string, (CC_LONG)strlen(string));
        CC_MD5_Final(digest, &context);
        std::string ret;
        std::stringstream ss;
        for(int i = 0 ; i < CC_MD5_DIGEST_LENGTH; ++i) {
            //printf("%.2x", digest[i]);
            ss << std::hex << (int)digest[i];
        }
        return ss.str();
    }
};

class Facade {
    
    
public:
    std::string getDigest(const char str[]) {
        MD5Digest m;
        return m.getDigest(str);
    }
    
    std::string getEncryptDataAndDigest(const char data[],const char key[], const char iv[]) {
        AESEncrypt a;
        return a.getEncrypt(data, key, iv);
    }
    
    std::string getCiperAndDigest(const char data[],const char key[], const char iv[]) {
        std::string tmp = getEncryptDataAndDigest(data, key, iv);
        return tmp.append(getDigest(tmp.c_str()));
    
    }
};

int main(int argc, const char * argv[]) {
    Facade f;
    std::string result = f.getCiperAndDigest("Hello", "world", NULL);
    std::cout << result << std::endl;
    return 0;
}
