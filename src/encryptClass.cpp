#include "encryptClass.hpp"
#include <stdexcept>
#include <algorithm>
#include <cctype> 

namespace bz {

    Encryptor::Encryptor() 
        : encKey(" ") {}

    Encryptor::Encryptor(const std::string& key) 
        : encKey(key) { 
        if (key.length() > maxKeyLength) { 
            throw std::invalid_argument("key length is too long...");
        }
    }

    void Encryptor::setKey(const std::string& key) { 
        if (key.length() > maxKeyLength) { 
            throw std::invalid_argument("key length is too long...");
        }
        encKey = key; 
    }

    std::string Encryptor::encrypt(const std::string& data, const std::string& algorithm, int shift) {
        if (algorithm == "xor") { 
            return xorEncrypt(data); 
        } 
        else if (algorithm == "caesar") { 
            return caesarEncrypt(data, shift); 
        } 
        else { 
            throw std::invalid_argument("no encryption algorithm: " + algorithm);
        }
    }

    bool Encryptor::operator==(const Encryptor& other) const {
        return encKey == other.encKey;
    }

    bool Encryptor::operator!=(const Encryptor& other) const {
        return !(*this == other);   
    }

    Encryptor& Encryptor::operator=(const Encryptor& other) {
        if (this != &other) { 
            encKey = other.encKey;
        }
        return *this;
    }

    std::string Encryptor::xorEncrypt(const std::string& data) { 
        if (encKey.empty()) { 
            throw std::runtime_error("no key set..."); 
        }
        std::string final = data; 
        for (size_t i = 0; i < data.size(); i++) { 
            final[i] ^= encKey[i % encKey.size()];
        }
        return final;
    }

    std::string Encryptor::caesarEncrypt(const std::string& data, int shift) { 
        std::string final = data; 
        char base;
        for (char& figure : final) { 
            if (std::isalpha(figure)) { 
                if (std::islower(figure)){
                    base = 'a';
                }
                else{ 
                    base = 'A';
                }
                int relativePosition = figure - base; 
                int shiftedPosition = (relativePosition + shift) % 26;
                if (shiftedPosition < 0){ 
                    shiftedPosition += 26; 
                }
                figure = static_cast<char>(base + shiftedPosition);
            }
        }
        return final;
    }
}