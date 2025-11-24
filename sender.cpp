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

int main() {
    system("clear");
    
    cout << "╔════════════════════════════════════════╗" << endl;
    cout << "║          SENDER PROGRAM                ║" << endl;
    cout << "║    OSI Model - Data Transmission       ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    
    // Get user input
    string message;
    cout << "\n Enter message to send: ";
    getline(cin, message);
    
    if (message.empty()) {
        message = "Hello from Sender!";
        cout << "   (Using default message)" << endl;
    }
    
    // Create packet with data
    Packet<string> packet(message);
    
    cout << "\n\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << "  ENCAPSULATION PROCESS" << endl;
    cout << "  Layer 7 → Layer 1" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << endl;
    
    // Create all protocol objects
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
    
    // Encapsulation: Go down the stack
    appLayer.encapsulate(packet);
    this_thread::sleep_for(chrono::milliseconds(300));
    
    presLayer.encapsulate(packet);
    this_thread::sleep_for(chrono::milliseconds(300));
    
    sessLayer.encapsulate(packet);
    this_thread::sleep_for(chrono::milliseconds(300));
    
    transLayer.encapsulate(packet);
    this_thread::sleep_for(chrono::milliseconds(300));
    
    netLayer.encapsulate(packet);
    this_thread::sleep_for(chrono::milliseconds(300));
    
    dlLayer.encapsulate(packet);
    this_thread::sleep_for(chrono::milliseconds(300));
    
    phyLayer.encapsulate(packet);
    
    cout << "\n\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << "    TRANSMITTING OVER NETWORK" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    
    // Simulate transmission delay
    cout << "\n  [";
    for (int i = 0; i < 20; i++) {
        cout << "█" << flush;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << "] 100%" << endl;
    
    // Save packet to file (simulating network transmission)
    ofstream outFile("network_packet.dat");
    if (outFile.is_open()) {
        outFile << packet.header << "\n";
        outFile << "<<<DATA_SEPARATOR>>>\n";
        outFile << packet.data << "\n";
        outFile.close();
        
        cout << "\n Packet successfully transmitted!" << endl;
        cout << " Data written to: network_packet.dat" << endl;
        cout << "\n The RECEIVER should now process the packet." << endl;
    } else {
        cerr << "\n Error: Could not create packet file!" << endl;
        return 1;
    }
    
    cout << "\n" << string(40, '-') << endl;
    cout << "Sender completed. Press Enter to exit...";
    cin.get();
    
    return 0;
}
