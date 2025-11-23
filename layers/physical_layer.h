#pragma once

#include "../core/layer.h"
#include "../protocols/physical/ethernet_physical.h"

class PhysicalLayer : public Layer {
private:
    EthernetPhysicalProtocol* protocol;
    
public:
    PhysicalLayer(EthernetPhysicalProtocol* proto = nullptr) 
        : Layer("Physical", 1), protocol(proto) {}
    
    void setProtocol(EthernetPhysicalProtocol* proto) {
        protocol = proto;
    }
    
    string getProtocolHeader() override {
        if (protocol != nullptr) {
            return protocol->generateHeader();
        }
        return "PHY_HEADER";
    }
    
    void processProtocol() override {
        cout << "  Layer: Physical Layer (Layer 1)" << endl;
        if (protocol != nullptr) {
            protocol->displayInfo();
        } else {
            cout << "  No specific protocol configured" << endl;
        }
    }
};
