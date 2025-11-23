#pragma once

#include "../core/layer.h"
#include "../protocols/presentation/tls.h"

class PresentationLayer : public Layer {
private:
    TLSProtocol* protocol;
    
public:
    PresentationLayer(TLSProtocol* proto = nullptr) 
        : Layer("Presentation", 6), protocol(proto) {}
    
    void setProtocol(TLSProtocol* proto) {
        protocol = proto;
    }
    
    string getProtocolHeader() override {
        if (protocol != nullptr) {
            return protocol->generateHeader();
        }
        return "PRES_HEADER";
    }
    
    void processProtocol() override {
        cout << "  Layer: Presentation Layer (Layer 6)" << endl;
        if (protocol != nullptr) {
            protocol->displayInfo();
        } else {
            cout << "  No specific protocol configured" << endl;
        }
    }
};