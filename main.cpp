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


int main() {
    cout << "========================================" << endl;
    cout << "   OSI Model - Complete Implementation" << endl;
    cout << "========================================" << endl;
    
    // Create packet with data
    Packet<string> packet("Hello World!");
    
    cout << "\n\n*** SENDING DATA (Encapsulation - Layer 7 to 1) ***" << endl;

    // Create all protocol objects
    HTTPProtocol httpProtocol("GET", "/index.html", "HTTP/1.1");
    TLSProtocol tlsProtocol("TLS 1.3", "AES-256-GCM");
    NetBIOSProtocol netbiosProtocol(54321, "WEB-SESSION");
    TCPProtocol tcpProtocol(443, 80, 1000, "SYN");
    IPv4Protocol ipv4Protocol("192.168.1.100", "142.250.185.46", 64);
    EthernetProtocol ethernetProtocol("AA:BB:CC:DD:EE:01", "FF:EE:DD:CC:BB:AA");
    EthernetPhysicalProtocol physicalProtocol("Copper Cable (Cat6)", 1000);
        
    // Create layer objects with protocols
    ApplicationLayer appLayer(&httpProtocol);
    PresentationLayer presLayer(&tlsProtocol);
    SessionLayer sessLayer(&netbiosProtocol);
    TransportLayer transLayer(&tcpProtocol);
    NetworkLayer netLayer(&ipv4Protocol);
    DataLinkLayer dlLayer(&ethernetProtocol);
    PhysicalLayer phyLayer(&physicalProtocol);
    
    // Encapsulation: Go down the stack (Layer 7 -> 1)
    appLayer.encapsulate(packet);
    presLayer.encapsulate(packet);
    sessLayer.encapsulate(packet);
    transLayer.encapsulate(packet);
    netLayer.encapsulate(packet);
    dlLayer.encapsulate(packet);
    phyLayer.encapsulate(packet);
    
    cout << "\n\n>>> DATA TRANSMITTED OVER NETWORK <<<\n" << endl;
    
    cout << "\n*** RECEIVING DATA (Decapsulation - Layer 1 to 7) ***" << endl;
    
    // Decapsulation: Go up the stack (Layer 1 -> 7)
    phyLayer.decapsulate(packet);
    dlLayer.decapsulate(packet);
    netLayer.decapsulate(packet);
    transLayer.decapsulate(packet);
    sessLayer.decapsulate(packet);
    presLayer.decapsulate(packet);
    appLayer.decapsulate(packet);
    
    cout << "\n\n*** FINAL RECEIVED DATA ***" << endl;
    cout << "Data: " << packet.data << endl;
    
    return 0;
}