#pragma once

#include "../core/layer.h"
#include "../protocols/application/http.h"

class ApplicationLayer : public Layer {
private:
    HTTPProtocol* protocol;  // HAS-A relationship (Composition)
    
public:
    // Constructor with protocol
    ApplicationLayer(HTTPProtocol* proto = nullptr) 
        : Layer("Application", 7), protocol(proto) {}
    
    // Set protocol dynamically
    void setProtocol(HTTPProtocol* proto) {
        protocol = proto;
    }
    
    string getProtocolHeader() override {
        if (protocol != nullptr) {
            return protocol->generateHeader();
        }
        return "APP_HEADER";  // Default if no protocol set
    }
    
    void processProtocol() override {
        cout << "  Layer: Application Layer (Layer 7)" << endl;
        if (protocol != nullptr) {
            protocol->displayInfo();
        } else {
            cout << "  No specific protocol configured" << endl;
        }
    }
};
