#pragma once

#include <iostream>
#include <string>
using namespace std;

// Ethernet Physical Protocol
class EthernetPhysicalProtocol {
private:
    string medium;
    int speed;          // Mbps
    
public:
    EthernetPhysicalProtocol(const string& med = "Copper Cable", int spd = 1000)
        : medium(med), speed(spd) {}
    
    string generateHeader() {
        return "Physical[Medium:" + medium + "|Speed:" + to_string(speed) + "Mbps]";
    }
    
    void displayInfo() {
        cout << "  Protocol: Ethernet Physical Layer" << endl;
        cout << "  Medium: " << medium << endl;
        cout << "  Speed: " << speed << " Mbps" << endl;
        cout << "  Function: Bits transmission over physical medium" << endl;
    }
};