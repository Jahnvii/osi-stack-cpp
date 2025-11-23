#pragma once

#include <iostream>
#include <string>
#include "packet.h"
using namespace std;

class Layer {
protected:
    string layerName;
    int layerNumber;
    
public:
    Layer(const string& name, int num) : layerName(name), layerNumber(num) {}
    virtual ~Layer() {}
    
    virtual string getProtocolHeader() = 0;
    virtual void processProtocol() = 0;
    
    template<typename T>
    void encapsulate(Packet<T>& packet) {
        cout << "\n--- Layer " << layerNumber << ": " << layerName << " ---" << endl;
        cout << "Action: Encapsulating (adding header)" << endl;
        
        processProtocol();
        string header = getProtocolHeader();
        packet.addHeader(header);
        
        packet.display();
    }
    
    template<typename T>
    void decapsulate(Packet<T>& packet) {
        cout << "\n--- Layer " << layerNumber << ": " << layerName << " ---" << endl;
        cout << "Action: Decapsulating (removing header)" << endl;
        
        packet.display();
        packet.removeHeader();
        
        processProtocol();
    }
};