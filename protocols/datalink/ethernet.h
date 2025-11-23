#pragma once

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// Ethernet Protocol
class EthernetProtocol {
private:
    string srcMAC;
    string dstMAC;
    
public:
    EthernetProtocol(const string& src = "AA:BB:CC:DD:EE:FF",
                     const string& dst = "11:22:33:44:55:66")
        : srcMAC(src), dstMAC(dst) {}
    
    string generateHeader() {
        stringstream ss;
        ss << "Ethernet[SrcMAC:" << srcMAC << "|DstMAC:" << dstMAC << "|CRC]";
        return ss.str();
    }
    
    void displayInfo() {
        cout << "  Protocol: Ethernet (IEEE 802.3)" << endl;
        cout << "  MAC Addressing: " << srcMAC << " -> " << dstMAC << endl;
        cout << "  Function: Physical addressing & framing" << endl;
    }
};