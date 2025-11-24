#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

#include "core/packet.h"
#include "protocols/application/http.h"
#include "protocols/presentation/tls.h"
#include "protocols/session/netbios.h"
#include "protocols/transport/tcp.h"
#include "protocols/network/ipv4.h"
#include "protocols/datalink/ethernet.h"
#include "protocols/physical/ethernet_physical.h"

#include "layers/application_layer.h"
#include "layers/presentation_layer.h"
#include "layers/session_layer.h"
#include "layers/transport_layer.h"
#include "layers/network_layer.h"
#include "layers/datalink_layer.h"
#include "layers/physical_layer.h"


using namespace std;

bool waitForPacket(const string& filename, int timeout_seconds = 60) {
    cout << "\n Waiting for incoming packet";
    int dots = 0;
    
    for (int i = 0; i < timeout_seconds * 2; i++) {
        ifstream check(filename);
        if (check.good()) {
            check.close();
            cout << " ✓" << endl;
            return true;
        }
        
        cout << "." << flush;
        dots++;
        if (dots % 10 == 0) cout << " ";
        
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    
    cout << "\nTimeout: No packet received!" << endl;
    return false;
}

int main() {
    system("clear");  // Use "cls" on Windows
    
    cout << "╔════════════════════════════════════════╗" << endl;
    cout << "║         RECEIVER PROGRAM               ║" << endl;
    cout << "║    OSI Model - Data Reception          ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    
    cout << "\n🔌 Receiver is READY and LISTENING..." << endl;
    cout << "📡 Waiting for data from sender..." << endl;
    
    // Wait for packet file to be created by sender
    if (!waitForPacket("network_packet.dat", 60)) {
        cout << "\n Make sure to run SENDER in another terminal!" << endl;
        cout << "\nPress Enter to exit...";
        cin.get();
        return 1;
    }
    
    // Small delay to ensure file write is complete
    this_thread::sleep_for(chrono::milliseconds(500));
    
    cout << "\n\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << "    PACKET RECEIVED!" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    
    // Load packet from file
    ifstream inFile("network_packet.dat");
    if (!inFile.is_open()) {
        cerr << "\n Error: Could not open packet file!" << endl;
        return 1;
    }
    
    string line, headers, dataStr;
    bool readingData = false;
    
    while (getline(inFile, line)) {
        if (line == "<<<DATA_SEPARATOR>>>") {
            readingData = true;
            continue;
        }
        
        if (readingData) {
            dataStr += line;
        } else {
            headers = line;
        }
    }
    inFile.close();
    
    // Create packet with received data
    Packet<string> packet(dataStr);
    packet.header = headers;
    
    cout << "\n📦 Raw packet received from network" << endl;
    
    cout << "\n\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << "    DECAPSULATION PROCESS" << endl;
    cout << "  Layer 1 → Layer 7" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << endl;
    
    // Create all protocol objects (same as sender)
    HTTPProtocol httpProtocol("POST", "/message", "HTTP/1.1");
    TLSProtocol tlsProtocol("TLS 1.3", "AES-256-GCM");
    NetBIOSProtocol netbiosProtocol(54321, "SENDER-SESSION");
    TCPProtocol tcpProtocol(8080, 9090, 1000, "SYN");
    IPv4Protocol ipv4Protocol("192.168.1.100", "192.168.1.200", 64);
    EthernetProtocol ethernetProtocol("AA:BB:CC:DD:EE:01", "FF:EE:DD:CC:BB:AA");
    EthernetPhysicalProtocol physicalProtocol("Ethernet Cable", 1000);
    
    // Create layer objects with protocols
    ApplicationLayer appLayer(&httpProtocol);
    PresentationLayer presLayer(&tlsProtocol);
    SessionLayer sessLayer(&netbiosProtocol);
    TransportLayer transLayer(&tcpProtocol);
    NetworkLayer netLayer(&ipv4Protocol);
    DataLinkLayer dlLayer(&ethernetProtocol);
    PhysicalLayer phyLayer(&physicalProtocol);
    
    // Decapsulation: Go up the stack
    phyLayer.decapsulate(packet);
    this_thread::sleep_for(chrono::milliseconds(300));
    
    dlLayer.decapsulate(packet);
    this_thread::sleep_for(chrono::milliseconds(300));
    
    netLayer.decapsulate(packet);
    this_thread::sleep_for(chrono::milliseconds(300));
    
    transLayer.decapsulate(packet);
    this_thread::sleep_for(chrono::milliseconds(300));
    
    sessLayer.decapsulate(packet);
    this_thread::sleep_for(chrono::milliseconds(300));
    
    presLayer.decapsulate(packet);
    this_thread::sleep_for(chrono::milliseconds(300));
    
    appLayer.decapsulate(packet);
    
    cout << "\n\n╔════════════════════════════════════════╗" << endl;
    cout << "║     MESSAGE RECEIVED SUCCESSFULLY!    ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    
    cout << "\nDecoded Message: \"" << packet.data << "\"" << endl;
    cout << "\nAll protocol headers removed" << endl;
    cout << "Original data extracted" << endl;
    
    // Clean up the packet file
    cout << "\n Cleaning up network packet file..." << endl;
    remove("network_packet.dat");
    
    cout << "\n" << string(40, '-') << endl;
    cout << "Receiver completed. Press Enter to exit...";
    cin.get();
    
    return 0;
}