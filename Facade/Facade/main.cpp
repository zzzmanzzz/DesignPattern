#include <CommonCrypto/CommonCrypto.h>
#include <iostream>
#include <sstream>
#include <vector>


class AESEncrypt {

public:
    std::string getEncrypt(const std::string data,const std::string key, const std::string iv) {
        std::vector<uint8_t> datav(data.begin(), data.end());
        const uint8_t* d = &datav[0];
        
        std::vector<uint8_t> ivv(iv.begin(), iv.end());
        const uint8_t* i = &ivv[0];
        
        std::vector<uint8_t> keyv(key.begin(), key.end());
        const uint8_t* k = &keyv[0];
        
        size_t dataLength = datav.size();
        size_t bufferSize = dataLength + kCCBlockSizeDES;
        uint8_t buffer[bufferSize];
        size_t numBytesEncrypted = 0;

        
        CCCryptorStatus cryptorStatus = CCCrypt(
                                kCCEncrypt,
                                kCCAlgorithmDES,
                                kCCOptionPKCS7Padding,
                                k,
                                key.size(),
                                i,
                                d,
                                data.size(),
                                (void *)buffer,
                                bufferSize,
                                &numBytesEncrypted);

        if (cryptorStatus == kCCSuccess) {
            std::string ret;
            std::stringstream ss;
            for(int i = 0 ; i < numBytesEncrypted; ++i) {
                ss << std::hex << (int)buffer[i];
            }
            std::cout << "encrypted: " << ss.str() << std::endl;
            return ss.str();
        } else {
            std::cout << "err: "<<cryptorStatus << std::endl;
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
    
    std::string getEncryptDataAndDigest(const std::string data,const std::string key, const std::string iv) {
        AESEncrypt a;
        return a.getEncrypt(data, key, iv);
    }
    
    std::string getCiperAndDigest(const std::string data,const std::string key, const std::string iv) {
        std::string tmp = getEncryptDataAndDigest(data, key, iv);
        return tmp.append(getDigest(tmp.c_str()));
    
    }
};

int main(int argc, const char * argv[]) {
    Facade f;
    std::string result = f.getCiperAndDigest("Hello hh", "world hh", "ivvv");
    std::cout << result << std::endl;
    return 0;
}
