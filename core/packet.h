#pragma once

#include <iostream>
#include <string>
using namespace std;

template<typename T>
class Packet {
public:
    T data;
    string header;
    
    Packet(const T& d) : data(d), header("") {}
    
    void addHeader(const string& h) {
        if (header.empty()) {
            header = h;
        } else {
            header = h + " | " + header;
        }
    }
    
    void removeHeader() {
        size_t pos = header.find(" | ");
        if (pos != string::npos) {
            header = header.substr(pos + 3);
        } else {
            header = "";
        }
    }
    
    void display() const {
        cout << "  [Packet State]" << endl;
        cout << "  Headers: " << (header.empty() ? "None" : header) << endl;
        cout << "  Data: " << data << endl;
    }
};
