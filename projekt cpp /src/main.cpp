#include <iostream>
#include <string> 
#include "inputHandler.hpp" 
#include "outputHandler.hpp"
#include "decryptClass.hpp"
#include "encryptClass.hpp"

int main() { 
    bz::InputHandler inputHandler;
    bz::Encryptor encryptor;
    bz::Decryptor decryptor;
    bz::OutputHandler outputHandler;

    std::string data, filePath, algorithm, key;
    int socket = -1, shift = 3; 

    std::cout << "choose your data source: \n";
    std::cout << "1. console \n 2. file \n 3. socket \n source: ";
    int source; 
    std::cin >> source;
    std::cin.ignore(); 
    
    if (source == 1) {
        inputHandler.readFromConsole();
        data = inputHandler.getData();
    } else if (source == 2) {
        std::cout << "file path: ";
        std::cin >> filePath;
        inputHandler.loadFromFile(filePath);
        data = inputHandler.getData();
    } else if (source == 3) {
        std::cout << "socket no.: ";
        std::cin >> socket;
        inputHandler.receiveFromSocket(socket);
        data = inputHandler.getData();
    } else {
        std::cerr << "invalid source... \n";
        return 1;
    }
    std::cout << "loaded data: " << data << "\n";

    std::cout << "choose operation: \n"; 
    std::cout << "1. encryption \n 2. decryption \n operation: "; 
    int operation; 
    std::cin >> operation; 

    if (operation == 1) { 
        std::cout << "choose algorithm (xor/caesar): ";
        std::cin >> algorithm; 
        
        if (algorithm == "xor") { 
            std::cout << "enter encryption key: "; 
            std::cin >> key; 
            encryptor.setKey(key); 
            data = encryptor.encrypt(data, "xor");
        } else if (algorithm == "caesar") { 
            std::cout << "enter shift: "; 
            std::cin >> shift; 
            data = encryptor.encrypt(data, "caesar", shift);
        } else { 
            std::cerr << "invalid algorithm... \n";
            return 1;
        }
    } else if (operation == 2) {
        std::cout << "choose algorithm (xor/caesar): ";
        std::cin >> algorithm; 
        
        if (algorithm == "xor") { 
            std::cout << "enter decryption key: "; 
            std::cin >> key; 
            decryptor.setKey(key); 
            data = decryptor.decrypt(data, "xor");
        } else if (algorithm == "caesar") { 
            std::cout << "enter shift: "; 
            std::cin >> shift; 
            data = decryptor.decrypt(data, "caesar", shift);
        } else { 
            std::cerr << "invalid algorithm... \n";
            return 1;
        }
    } else {
        std::cerr << "invalid operation... \n";
        return 1;
    }

    std::cout << "choose data output: \n";
    std::cout << "1. console \n 2. file \n 3. socket \n output: ";
    int output;
    std::cin >> output;

    if (output == 1) {
        outputHandler.writeToConsole(data);
    } else if (output == 2) {
        std::cout << "file path: ";
        std::cin >> filePath;
        outputHandler.writeToFile(filePath, data);
        std::cout << "data saved to file... \n";
    } else if (output == 3) {
        std::cout << "socket no.: ";
        std::cin >> socket;
        outputHandler.sendToSocket(socket, data);
        std::cout << "data sent via socket... \n";
    } else {
        std::cerr << "invalid output... \n";
        return 1;
    }

    return 0;
}