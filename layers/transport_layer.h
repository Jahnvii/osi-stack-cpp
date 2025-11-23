#pragma once

#include "../core/layer.h"
#include "../protocols/transport/tcp.h"

class TransportLayer : public Layer {
private:
    TCPProtocol* protocol;
    
public:
    TransportLayer(TCPProtocol* proto = nullptr) 
        : Layer("Transport", 4), protocol(proto) {}
    
    void setProtocol(TCPProtocol* proto) {
        protocol = proto;
    }
    
    string getProtocolHeader() override {
        if (protocol != nullptr) {
            return protocol->generateHeader();
        }
        return "TRANS_HEADER";
    }
    
    void processProtocol() override {
        cout << "  Layer: Transport Layer (Layer 4)" << endl;
        if (protocol != nullptr) {
            protocol->displayInfo();
        } else {
            cout << "  No specific protocol configured" << endl;
        }
    }
};
