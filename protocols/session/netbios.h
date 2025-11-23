#pragma once

#include <iostream>
#include <string>
using namespace std;

// NetBIOS Protocol
class NetBIOSProtocol {
private:
    int sessionId;
    string sessionName;
    
public:
    NetBIOSProtocol(int id = 12345, const string& name = "USER-SESSION")
        : sessionId(id), sessionName(name) {}
    
    string generateHeader() {
        return "NetBIOS[SessionID:" + to_string(sessionId) + "|Name:" + sessionName + "]";
    }
    
    void displayInfo() {
        cout << "  Protocol: NetBIOS (Network Basic Input/Output System)" << endl;
        cout << "  Session ID: " << sessionId << endl;
        cout << "  Session Name: " << sessionName << endl;
        cout << "  Function: Session establishment & management" << endl;
    }
};
