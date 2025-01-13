#pragma once 

#include <string> 

namespace bz {

class Decryptor { 
    public: 
        Decryptor(); 
        Decryptor(const std::string& key); 
        Decryptor(const std::string& key, int maxKeyLength);

        void setKey(const std::string& key); 
        std::string decrypt(const std::string& encrypted, const std::string& algorithm, int shift = 3);

        bool operator==(const Decryptor& other) const;
        bool operator!=(const Decryptor& other) const;
        Decryptor& operator=(const Decryptor& other);

    private: 
        std::string decryptKey; 
        static constexpr int maxKeyLength = 256;
        std::string xorDecrypt(const std::string& encrypted);
        std::string caesarDecrypt(const std::string& encrypted, int shift);  
};
} 