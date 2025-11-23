#pragma once

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// IPv4 Protocol
class IPv4Protocol {
private:
    string srcIP;
    string dstIP;
    int ttl;
    
public:
    IPv4Protocol(const string& src = "192.168.1.10", 
                 const string& dst = "8.8.8.8",
                 int timeToLive = 64)
        : srcIP(src), dstIP(dst), ttl(timeToLive) {}
    
    string generateHeader() {
        stringstream ss;
        ss << "IPv4[Src:" << srcIP << "|Dst:" << dstIP << "|TTL:" << ttl << "]";
        return ss.str();
    }
    
    void displayInfo() {
        cout << "  Protocol: IPv4 (Internet Protocol v4)" << endl;
        cout << "  Routing: " << srcIP << " -> " << dstIP << endl;
        cout << "  TTL: " << ttl << " hops" << endl;
        cout << "  Function: Logical addressing & routing" << endl;
    }
};