#pragma once

#include <string>
#include <iostream>
using namespace std;

class HTTPProtocol {
private:
    string method;      // GET, POST
    string resource;    // /index.html
    string version;     // HTTP/1.1
    
public:
    HTTPProtocol(const string& m, 
                 const string& res,
                 const string& ver)
        : method(m), resource(res), version(ver) {}
    
    string generateHeader() {
        return "HTTP[" + method + " " + resource + " " + version + "]";
    }
    
    void displayInfo() {
        cout << "  Protocol: HTTP (HyperText Transfer Protocol)" << endl;
        cout << "  Request: " << method << " " << resource << " " << version << endl;
        cout << "  Function: Web communication" << endl;
    }
};