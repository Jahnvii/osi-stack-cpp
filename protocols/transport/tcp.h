#pragma once

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// TCP Protocol
class TCPProtocol {
private:
    int srcPort;
    int dstPort;
    int seqNum;
    string flags;       // SYN, ACK, FIN
    
public:
    TCPProtocol(int src = 8080, int dst = 80, int seq = 1000, const string& f = "SYN")
        : srcPort(src), dstPort(dst), seqNum(seq), flags(f) {}
    
    string generateHeader() {
        stringstream ss;
        ss << "TCP[Src:" << srcPort << "|Dst:" << dstPort 
           << "|Seq:" << seqNum << "|Flags:" << flags << "]";
        return ss.str();
    }
    
    void displayInfo() {
        cout << "  Protocol: TCP (Transmission Control Protocol)" << endl;
        cout << "  Type: Connection-oriented, Reliable" << endl;
        cout << "  Ports: " << srcPort << " -> " << dstPort << endl;
        cout << "  Sequence: " << seqNum << " | Flags: " << flags << endl;
        cout << "  Function: Reliable data delivery" << endl;
    }
};