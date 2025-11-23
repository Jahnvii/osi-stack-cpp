#pragma once

#include "../core/layer.h"
#include "../protocols/network/ipv4.h"

class NetworkLayer : public Layer {
private:
    IPv4Protocol* protocol;
    
public:
    NetworkLayer(IPv4Protocol* proto = nullptr) 
        : Layer("Network", 3), protocol(proto) {}
    
    void setProtocol(IPv4Protocol* proto) {
        protocol = proto;
    }
    
    string getProtocolHeader() override {
        if (protocol != nullptr) {
            return protocol->generateHeader();
        }
        return "NET_HEADER";
    }
    
    void processProtocol() override {
        cout << "  Layer: Network Layer (Layer 3)" << endl;
        if (protocol != nullptr) {
            protocol->displayInfo();
        } else {
            cout << "  No specific protocol configured" << endl;
        }
    }
};
