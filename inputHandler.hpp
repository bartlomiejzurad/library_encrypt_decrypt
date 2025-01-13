#pragma once                                             

#include <iostream>
#include <string> 

namespace bz{ 

class InputHandler { 
    public: 
        InputHandler();
        InputHandler(const std::string& inData);
        InputHandler(const std::string& inData, int bufferSize);

        void readFromConsole(); 
        void loadFromFile(const std::string& filePath);
        void receiveFromSocket(int socket); 
        bool validateData(const std::string& data) const; 
        std::string getData() const; 
    
        bool operator==(const InputHandler& other) const;
        bool operator!=(const InputHandler& other) const; 
        InputHandler& operator=(const InputHandler& other);

    private: 
        std::string inData;                                 // container for data 
        static constexpr int BUFFER_SIZE = 1500;            // buffer size = MTU(Ethernet) for each object 
}; 
}



