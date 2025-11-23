#pragma once

#include "../core/layer.h"
#include "../protocols/session/netbios.h"

class SessionLayer : public Layer {
private:
    NetBIOSProtocol* protocol;
    
public:
    SessionLayer(NetBIOSProtocol* proto = nullptr) 
        : Layer("Session", 5), protocol(proto) {}
    
    void setProtocol(NetBIOSProtocol* proto) {
        protocol = proto;
    }
    
    string getProtocolHeader() override {
        if (protocol != nullptr) {
            return protocol->generateHeader();
        }
        return "SESS_HEADER";
    }
    
    void processProtocol() override {
        cout << "  Layer: Session Layer (Layer 5)" << endl;
        if (protocol != nullptr) {
            protocol->displayInfo();
        } else {
            cout << "  No specific protocol configured" << endl;
        }
    }
};