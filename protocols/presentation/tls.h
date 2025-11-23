#pragma once

#include <iostream>
#include <string>
using namespace std;

// TLS Protocol
class TLSProtocol {
private:
    string version;     // TLS 1.3
    string cipher;      // AES-256-GCM
    
public:
    TLSProtocol(const string& ver = "TLS 1.3", 
                const string& c = "AES-256-GCM")
        : version(ver), cipher(c) {}
    
    string generateHeader() {
        return "TLS[Ver:" + version + "|Cipher:" + cipher + "]";
    }
    
    void displayInfo() {
        cout << "  Protocol: TLS (Transport Layer Security)" << endl;
        cout << "  Version: " << version << endl;
        cout << "  Cipher: " << cipher << endl;
        cout << "  Function: Encryption & Data security" << endl;
    }
};