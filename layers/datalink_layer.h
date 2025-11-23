#pragma once

#include "../core/layer.h"
#include "../protocols/datalink/ethernet.h"

class DataLinkLayer : public Layer {
private:
    EthernetProtocol* protocol;
    
public:
    DataLinkLayer(EthernetProtocol* proto = nullptr) 
        : Layer("DataLink", 2), protocol(proto) {}
    
    void setProtocol(EthernetProtocol* proto) {
        protocol = proto;
    }
    
    string getProtocolHeader() override {
        if (protocol != nullptr) {
            return protocol->generateHeader();
        }
        return "DL_HEADER";
    }
    
    void processProtocol() override {
        cout << "  Layer: Data Link Layer (Layer 2)" << endl;
        if (protocol != nullptr) {
            protocol->displayInfo();
        } else {
            cout << "  No specific protocol configured" << endl;
        }
    }
};
