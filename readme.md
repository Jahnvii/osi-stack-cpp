OSI Model Implementation
A C++ implementation of the 7-layer OSI networking model using OOP principles and templates.
Overview
This project simulates network data flow through all OSI layers with real protocol implementations. Data packets are encapsulated (headers added) going down the stack and decapsulated (headers removed) going up.
Features

✅ All 7 OSI layers implemented
✅ Real protocols: HTTP, TLS, NetBIOS, TCP, IPv4, Ethernet, Physical
✅ OOP: Inheritance, Polymorphism, Encapsulation, Abstraction, Composition
✅ Templates for generic packet handling
✅ Modular architecture with clear separation of concerns

Architecture
Composition Pattern (Layer HAS-A Protocol):
ApplicationLayer ──→ HTTPProtocol
PresentationLayer ──→ TLSProtocol
SessionLayer ──→ NetBIOSProtocol
TransportLayer ──→ TCPProtocol
NetworkLayer ──→ IPv4Protocol
DataLinkLayer ──→ EthernetProtocol
PhysicalLayer ──→ EthernetPhysicalProtocol
Project Structure

OSI_Model_Project/
├── core/                    # Base classes (Packet, Layer)
├── protocols/               # Protocol implementations
│   ├── application/        # HTTP
│   ├── presentation/       # TLS
│   ├── session/           # NetBIOS
│   ├── transport/         # TCP
│   ├── network/           # IPv4
│   ├── datalink/          # Ethernet
│   └── physical/          # Ethernet Physical
├── layers/                 # OSI layer implementations
└── main.cpp               # Driver program

Compilation & Execution
bash# Compile
g++ -std=c++11 -I. main.cpp -o osi_model

# Or use Makefile
make
make run

# Clean
make clean
How It Works
Encapsulation (Sending):
Data → Layer 7 adds HTTP header
     → Layer 6 adds TLS header
     → Layer 5 adds NetBIOS header
     → Layer 4 adds TCP header
     → Layer 3 adds IPv4 header
     → Layer 2 adds Ethernet header
     → Layer 1 converts to bits
     → Network transmission
Decapsulation (Receiving):
Received bits → Layer 1 processes
              → Layer 2 removes Ethernet header
              → Layer 3 removes IPv4 header
              → Layer 4 removes TCP header
              → Layer 5 removes NetBIOS header
              → Layer 6 removes TLS header
              → Layer 7 removes HTTP header
              → Original Data
Protocol Details
LayerProtocolKey Components7 - ApplicationHTTPMethod, Resource, Version6 - PresentationTLSVersion, Cipher Suite5 - SessionNetBIOSSession ID, Name4 - TransportTCPPorts, Seq Number, Flags3 - NetworkIPv4Source/Dest IP, TTL2 - Data LinkEthernetSource/Dest MAC, CRC1 - PhysicalEthernet PhysicalMedium, Speed
Key Design Decisions

Composition over Inheritance: Layers contain protocols (flexibility)
Template Packet: Type-safe generic data handling
Modular Structure: Easy to add new protocols
Clean Separation: Layer logic ≠ Protocol logic

OOP Concepts

Inheritance: All layers inherit from Layer base class
Polymorphism: Virtual functions for protocol-specific behavior
Encapsulation: Private protocol data with public interfaces
Abstraction: Abstract base Layer class
Composition: Layer HAS-A Protocol relationship
Templates: Generic Packet<T> class

Extensibility
Adding a new protocol (e.g., UDP):
cpp// 1. Create protocol class
class UDPProtocol { ... };

// 2. Use in existing layer
TransportLayer transport(&udpProtocol);

// No changes needed to layer code!
Technologies

Language: C++11
Compiler: g++ (GCC 4.8+)
Paradigm: Object-Oriented Programming
Patterns: Composition, Template Method

Future Enhancements

Multiple protocols per layer (UDP, FTP, DNS, IPv6)
TCP 3-way handshake simulation
Checksum calculation and validation
Error handling and packet validation
GUI visualization