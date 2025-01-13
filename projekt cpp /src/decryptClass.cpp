#include "decryptClass.hpp"
#include <stdexcept>
#include <cctype>

namespace bz {

    Decryptor::Decryptor() 
        : decryptKey(" ") {}

    Decryptor::Decryptor(const std::string& key)
        : decryptKey(key) {
        if (key.length() > maxKeyLength) { 
            throw std::invalid_argument("key length is too long...");
        }
    }

    Decryptor::Decryptor(const std::string& key, int maxKey)
        : decryptKey(key) {
        if (key.length() > maxKey) {
            throw std::invalid_argument("key length is too long...");
        }
    }

    void Decryptor::setKey(const std::string& key) { 
        if (key.length() > maxKeyLength) {
            throw std::invalid_argument("key length is too long...");
        }
        decryptKey = key;
    }

    std::string Decryptor::decrypt(const std::string& encrypted, const std::string& algorithm, int shift) { 
        if (algorithm == "xor") { 
            return xorDecrypt(encrypted);
        } 
        else if (algorithm == "caesar") { 
            return caesarDecrypt(encrypted, shift);
        } 
        else { 
            throw std::invalid_argument("no encryption algorithm: " + algorithm);
        }
    }

    std::string Decryptor::xorDecrypt(const std::string& encrypted) { 
        if (decryptKey.empty()) {
            throw std::runtime_error("no key set...");
        }
        std::string final = encrypted;
        for (size_t i = 0; i < encrypted.size(); ++i) { 
            final[i] ^= decryptKey[i % decryptKey.size()];
        }
        return final;
    }

    std::string Decryptor::caesarDecrypt(const std::string& encrypted, int shift) { 
        std::string final = encrypted;
        for (char& figure : final) { 
            if (std::isalpha(figure)) { 
                char base = std::islower(figure) ? 'a' : 'A';
                int relativePosition = figure - base;
                int shiftedPosition = (relativePosition - shift) % 26;

                if (shiftedPosition < 0) { 
                    shiftedPosition += 26;
                }
                figure = static_cast<char>(base + shiftedPosition);
            }
        }
        return final;
    }

    bool Decryptor::operator==(const Decryptor& other) const {
        return decryptKey == other.decryptKey;
    }

    bool Decryptor::operator!=(const Decryptor& other) const {
        return !(*this == other);
    }

    Decryptor& Decryptor::operator=(const Decryptor& other) {
        if (this != &other) { 
            decryptKey = other.decryptKey;
        }
        return *this;
    }
}