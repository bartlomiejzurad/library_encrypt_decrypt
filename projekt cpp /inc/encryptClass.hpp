#pragma once 

#include <string> 

namespace bz {

class Encryptor { 
    public: 
        Encryptor(); 
        Encryptor(const std::string& key);                          
        Encryptor(const std::string& key, int maxKeyLength);          // overload

        void setKey(const std::string& key); 
        std::string encrypt(const std::string& data, const std::string& algorithm, int shift = 3);

        bool operator==(const Encryptor& other) const;
        bool operator!=(const Encryptor& other) const; 
        Encryptor& operator=(const Encryptor& other);

    private: 
        std::string encKey; 
        static constexpr int maxKeyLength = 256;

        std::string xorEncrypt(const std::string& data);
        std::string caesarEncrypt(const std::string& data, int shift); 
};
}