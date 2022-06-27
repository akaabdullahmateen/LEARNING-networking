#include <iostream>
#include <string>
#include <bitset>
#include <iomanip>
#include <map>

#include "Ipv4_header.h"


void Ipv4_header::initialize_header(){
	header["version"]               = std::to_string(dump[0] >> 4);
    header["ihl"]                   = std::to_string((dump[0] & 0xf) * 4) + " bytes";
    header["dscp"]                  = get_dscp_keyword(dump[1] >> 2);
    header["ecn"]                   = get_ecn_keyword(dump[1] & 0x3);
    header["length"]                = std::to_string((dump[2] << 8) + dump[3]) + " bytes";
    header["flags"]                 = "0b" + std::bitset<3>(dump[6] >> 5).to_string();
    header["is_flag_reserved_set"]  = (dump[6] >> 5 & 0x4) ? "Set" : "Not set";
    header["is_flag_df_set"]        = (dump[6] >> 5 & 0x2) ? "Set" : "Not set";
    header["is_flag_mf_set"]        = (dump[6] >> 5 & 0x1) ? "Set" : "Not set";
    header["fragment_offset"]       = std::to_string(((dump[6] & 0x1f) << 8) + dump[7]);
    header["ttl"]                   = std::to_string(dump[8]);
    header["protocol"]              = get_protocol_keyword(dump[9]);
    header["source_address"]        = std::to_string(dump[12]) + "." + std::to_string(dump[13]) + "." + std::to_string(dump[14]) + "." + std::to_string(dump[15]);
    header["destination_address"]   = std::to_string(dump[16]) + "." + std::to_string(dump[17]) + "." + std::to_string(dump[18]) + "." + std::to_string(dump[19]);
   
    std::stringstream stream;
    stream << std::hex << ((dump[4] << 8) + dump[5]);
    header["identification"]        = "0x" + stream.str();
    stream.str(std::string());
    stream << std::hex << ((dump[10] << 8) + dump[11]);
    header["checksum"]              = "0x" + stream.str();

    unsigned int provided_checksum      = (dump[10] << 8) + dump[11];
    unsigned int calculated_checksum    = calculate_checksum();
    bool is_checksum_valid              = (provided_checksum == calculated_checksum);
    header["is_checksum_valid"]         = (is_checksum_valid) ? "Valid" : "Invalid";
}

unsigned int Ipv4_header::calculate_checksum(){
    unsigned int checksum = 0x00;
    std::size_t ihl = (dump[0] & 0xf) * 4;
    for(std::size_t idx = 0; idx < ihl; idx+=2){
        checksum += ((dump[idx] << 8) + dump[idx + 1]);
    }
    checksum -= ((dump[10] << 8) + dump[11]);
    unsigned int carry = checksum >> 16;
    while(carry){
        checksum &= 0xffff;
        checksum += carry;
        carry = checksum >> 16;
    }
    checksum = ~checksum;
    checksum &= 0xffff;
    return checksum;
}

std::string Ipv4_header::get_dscp_keyword(unsigned int n){
    switch(n){
        case 0:
            return "Default Forwarding";
        case 8:
            return "Class Selector 1";
        case 10:
            return "Assured Forwarding 11";
        case 12:
            return "Assured Forwarding 12";
        case 14:
            return "Assured Forwarding 13";
        case 16:
            return "Class Selector 2";
        case 18:
            return "Assured Forwarding 21";
        case 20:
            return "Assured Forwarding 22";
        case 22:
            return "Assured Forwarding 23";
        case 24:
            return "Class Selector 3";
        case 26:
            return "Assured Forwarding 31";
        case 28:
            return "Assured Forwarding 32";
        case 30:
            return "Assured Forwarding 33";
        case 32:
            return "Class Selector 4";
        case 34:
            return "Assured Forwarding 41";
        case 36:
            return "Assured Forwarding 42";
        case 38:
            return "Assured Forwarding 43";
        case 40:
            return "Class Selector 5";
        case 44:
            return "VOICE-ADMIT";
        case 46:
            return "Expedited Forwarding";
        case 48:
            return "Class Selector 6";
        case 56:
            return "Class Selector 7";
        default:
            return "Undefined";
    }
}

std::string Ipv4_header::get_ecn_keyword(unsigned int n){
	if(n > 3) return "Undefined";
    std::string keywords[] = {
        "Not ECN-Capable Transport",
        "ECN-Capable Transport(1)",
        "ECN-Capable Transport(0)",
        "Congestion Experienced"
	};
    return keywords[n];
}

void Ipv4_header::default_initialize_dump(){
	for(std::size_t i = 0; i < 60; ++i){
		dump[i] = 0x00;
	}
	dump[9] = 0xff;
}

Ipv4_header::Ipv4_header(){
	default_initialize_dump();
	initialize_header();
}

Ipv4_header::Ipv4_header(unsigned char *begin, unsigned char *end){
    if(end < begin + 20){
    	default_initialize_dump();
    }
    else{
   		std::size_t i = 0;
   		while(begin != end){
   		    dump[i++] = *begin++;
   		}	
    }
    initialize_header();
}

void Ipv4_header::display_blueprint(){
    std::cout << "|----------------------------------------------------------------------------------------|" << std::endl;
    std::cout << "| Offset |  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 | 11 | 12 | 13 | 14 | 15 |" << std::endl;
    std::cout << "|----------------------------------------------------------------------------------------|" << std::endl;
    std::cout << "|    0   |      Version      |        IHL        |             DSCP            |   ECN   |" << std::endl;
    std::cout << "|----------------------------------------------------------------------------------------|" << std::endl;
    std::cout << "|   16   |                                 Total Length                                  |" << std::endl;
    std::cout << "|----------------------------------------------------------------------------------------|" << std::endl;
    std::cout << "|   32   |                                Identification                                 |" << std::endl;
    std::cout << "|----------------------------------------------------------------------------------------|" << std::endl;
    std::cout << "|   48   |     Flags    |                 Fragment Offset                                |" << std::endl;
    std::cout << "|----------------------------------------------------------------------------------------|" << std::endl;
    std::cout << "|   64   |             Time To Live              |               Protocol                |" << std::endl;
    std::cout << "|----------------------------------------------------------------------------------------|" << std::endl;
    std::cout << "|   80   |                                Header Checksum                                |" << std::endl;
    std::cout << "|----------------------------------------------------------------------------------------|" << std::endl;
    std::cout << "|   96   |                               Source IP Address                               |" << std::endl;
    std::cout << "|----------------------------------------------------------------------------------------|" << std::endl;
    std::cout << "|   112  |                         Source IP Address (continued)                         |" << std::endl;
    std::cout << "|----------------------------------------------------------------------------------------|" << std::endl;
    std::cout << "|   128  |                             Destination IP Address                            |" << std::endl;
    std::cout << "|----------------------------------------------------------------------------------------|" << std::endl;
    std::cout << "|   144  |                       Destination IP Address (continued)                      |" << std::endl;
    std::cout << "|----------------------------------------------------------------------------------------|" << std::endl;
    std::cout << "|   160  |                                    Options                                    |" << std::endl;
    std::cout << "|----------------------------------------------------------------------------------------|" << std::endl;
}

void Ipv4_header::display_header(){
    std::cout << "Version ................................. : " << header["version"] << std::endl;
    std::cout << "Internet Header Length .................. : " << header["ihl"] << std::endl;
    std::cout << "Differentiated Services Code Point ...... : " << header["dscp"] << std::endl;
    std::cout << "Explicit Congestion Notification ........ : " << header["ecn"] << std::endl;
    std::cout << "Total Length ............................ : " << header["length"] << std::endl;
    std::cout << "Identification .......................... : " << header["identification"] << std::endl;
    std::cout << "Flags ................................... : " << header["flags"] << std::endl;
    std::cout << "    Reserved ............................ : " << header["is_flag_reserved_set"] << std::endl;
    std::cout << "    Don't Fragment ...................... : " << header["is_flag_df_set"] << std::endl;
    std::cout << "    More Fragments ...................... : " << header["is_flag_mf_set"] << std::endl;
    std::cout << "Fragment Offset ......................... : " << header["fragment_offset"] << std::endl;
    std::cout << "Time To Live ............................ : " << header["ttl"] << std::endl;
    std::cout << "Protocol ................................ : " << header["protocol"] << std::endl;
    std::cout << "Header Checksum ......................... : " << header["checksum"] << std::endl;
    std::cout << "    Checksum Validation ................. : " << header["is_checksum_valid"] << std::endl;
    std::cout << "Source Address .......................... : " << header["source_address"] << std::endl;
    std::cout << "Destination Address ..................... : " << header["destination_address"] << std::endl;
}

void Ipv4_header::display_raw(){
	bool is_last_newline = false;
	std::size_t ihl = (dump[0] & 0xf) * 4;
	for(size_t idx = 0; idx < ihl; ++idx){
		std::bitset<8> dump_byte = dump[idx];
		std::cout << dump_byte.to_string() << " ";
		if(!((idx + 1) % 4)){
			std::cout << std::endl;
			is_last_newline = true;
		}
		else is_last_newline = false;
	}
	if(!is_last_newline) std::cout << std::endl;
}

inline std::map<std::string, std::string> Ipv4_header::get_header(){
    return header;
}

std::string Ipv4_header::get_protocol_keyword(unsigned int n){
    if (n > 143 && n < 253) return "Unassigned";
    if (n == 253 || n == 254) return "Use for experimentation and testing";
    if (n == 255) return "Reserved";

    const std::string keywords[] = {
    "HOPOPT - IPv6 Hop-by-Hop Option",
    "ICMP - Internet Control Message Protocol",
    "IGMP - Internet Group Management Protocol",
    "GGP - Gateway-to-Gateway Protocol",
    "IP-in-IP - IP in IP",
    "ST - Internet Stream Protocol",
    "TCP - Transmission Control Protocol",
    "CBT - Core-based trees",
    "EGP - Exterior Gateway Protocol",
    "IGP - Interior Gateway Protocol",
    "BBN-RCC-MON - BBN RCC Monitoring",
    "NVP-II - Network Voice Protocol",
    "PUP - Xerox PUP",
    "ARGUS - ARGUS",
    "EMCON - EMCON",
    "XNET - Cross Net Debugger",
    "CHAOS - Chaos",
    "UDP - User Datagram Protocol",
    "MUX - Multiplexing",
    "DCN-MEAS - DCN Measurement Subsystems",
    "HMP - Host Monitoring Protocol",
    "PRM - Packet Radio Measurement",
    "XNS-IDP - XEROX NS IDP",
    "TRUNK-1 - Trunk-1",
    "TRUNK-2 - Trunk-2",
    "LEAF-1 - Leaf-1",
    "LEAF-2 - Leaf-2",
    "RDP - Reliable Data Protocol",
    "IRTP - Internet Reliable Transaction Protocol",
    "ISO-TP4 - ISO Transport Protocol Class 4",
    "NETBLT - Bulk Data Transfer Protocol",
    "MFE-NSP - MFE Network Services Protocol",
    "MERIT-INP - MERIT Internodal Protocol",
    "DCCP - Datagram Congestion Control Protocol",
    "3PC - Third Party Connect Protocol",
    "IDPR - Inter-Domain Policy Routing Protocol",
    "XTP - Xpress Transport Protocol",
    "DDP - Datagram Delivery Protocol",
    "IDPR-CMTP - IDPR Control Message Transport Protocol",
    "TP - TP++ Transport Protocol",
    "IL - IL Transport Protocol",
    "IPv6 - IPv6 Encapsulation",
    "SDRP - Source Demand Routing Protocol",
    "IPv6-Route - Routing Header for IPv6",
    "IPv6-Frag - Fragment Header for IPv6",
    "IDRP - Inter-Domain Routing Protocol",
    "RSVP - Resource Reservation Protocol",
    "GRE - Generic Routing Encapsulation",
    "DSR - Dynamic Source Routing Protocol",
    "BNA - Burroughs Network Architecture",
    "ESP - Encapsulating Security Payload",
    "AH - Authentication Header",
    "I-NLSP - Integrated Net Layer Security Protocol",
    "SwIPe - SwIPe",
    "NARP - NBMA Address Resolution Protocol",
    "MOBILE - IP Mobility",
    "TLSP - Transport Layer Security Protocol ",
    "SKIP - Simple Key-Management for Internet Protocol",
    "IPv6-ICMP - ICMP for IPv6",
    "IPv6-NoNxt - No Next Header for IPv6",
    "IPv6-Opts - Destination Options for IPv6",
    "ANY_HOST - Any host internal Protocol",
    "CFTP - CFTP",
    "ANY_LOCAL - Any local network",
    "SAT-EXPAK - SATNET and Backroom EXPAK",
    "KRYPTOLAN - Kryptolan",
    "RVD - MIT Remote Virtual Disk Protocol",
    "IPPC - Internet Pluribus Packet Core",
    "ANY_DISTRIBUTED - Any distributed file system",
    "SAT-MON - SATNET Monitoring",
    "VISA - VISA Protocol",
    "IPCU - Internet Packet Core Utility",
    "CPNX - Computer Protocol Network Executive",
    "CPHB - Computer Protocol Heart Beat",
    "WSN - Wang Span Network",
    "PVP - Packet Video Protocol",
    "BR-SAT-MON - Backroom SATNET Monitoring",
    "SUN-ND - SUN ND Protocol",
    "WB-MON - WIDEBAND Monitoring",
    "WB-EXPAK - WIDEBAND EXPAK",
    "ISO-IP - International Organization for Standardization Internet Protocol",
    "VMTP - Versatile Message Transaction Protocol",
    "SECURE-VMTP - Secure Versatile Message Transaction Protocol",
    "VINES - VINES",
    "TTP - TTP",
    "IPTM - Internet Protocol Traffic Manager",
    "NSFNET-IGP - NSFNET-IGP",
    "DGP - Dissimilar Gateway Protocol",
    "TCF - TCF",
    "EIGRP - EIGRP",
    "OSPF - Open Shortest Path First",
    "Sprite-RPC - Sprite RPC Protocol",
    "LARP - Locus Address Resolution Protocol",
    "MTP - Multicast Transport Protocol",
    "AX.25 - AX.25",
    "OS - KA9Q NOS compatible IP over IP tunneling",
    "MICP - Mobile Internetworking Control Protocol",
    "SCC-SP - Semaphore Communications Sec Pro",
    "ETHERIP - Ethernet-within-IP Encapsulation",
    "ENCAP - Encapsulation Header",
    "ANY_PRIVATE - Any private encryption scheme",
    "GMTP - GMTP",
    "IFMP - Ipsilon Flow Management Protocol",
    "PNNI - PNNI over IP",
    "PIM - Protocol Independent Multicast",
    "ARIS - Aggregate Route IP Switching Protocol",
    "SCPS - Space Communications Protocol Standards",
    "QNX - QNX",
    "A/N - Active Networks",
    "IPComp - IP Payload Compression Protocol",
    "SNP - Sitara Networks Protocol",
    "Compaq-Peer - Compaq Peer Protocol",
    "IPX-in-IP - IPX in IP",
    "VRRP - Virtual Router Redundancy Protocol",
    "PGM - PGM Reliable Transport Protocol",
    "ANY_ZERO_HOP - Any 0-hop protocol",
    "L2TP - Layer Two Tunneling Protocol Version 3",
    "DDX - D-II Data Exchange",
    "IATP - Interactive Agent Transfer Protocol",
    "STP - Schedule Transfer Protocol",
    "SRP - SpectraLink Radio Protocol",
    "UTI - Universal Transport Interface Protocol",
    "SMP - Simple Message Protocol",
    "SM - Simple Multicast Protocol",
    "PTP - Performance Transparency Protocol",
    "IS-IS over IPv4 - Intermediate System to Intermediate System (IS-IS) Protocol over IPv4",
    "FIRE - Flexible Intra-AS Routing Environment",
    "CRTP - Combat Radio Transport Protocol",
    "CRUDP - Combat Radio User Datagram",
    "SSCOPMCE - Service-Specific Connection-Oriented Protocol in a Multilink and Connectionless Environment",
    "IPLT - IPLT",
    "SPS - Secure Packet Shield",
    "PIPE - Private IP Encapsulation within IP",
    "SCTP - Stream Control Transmission Protocol",
    "FC - Fibre Channel",
    "RSVP-E2E-IGNORE - Reservation Protocol (RSVP) End-to-End Ignore",
    "Mobility Header - Mobility Extension Header for IPv6",
    "UDPLite - Lightweight User Datagram Protocol",
    "MPLS-in-IP - Multiprotocol Label Switching Encapsulated in IP",
    "Manet - MANET Protocols",
    "HIP - Host Identity Protocol",
    "Shim6 - Site Multihoming by IPv6 Intermediation",
    "WESP - Wrapped Encapsulating Security Payload",
    "ROHC - Robust Header Compression",
    "Ethernet - IPv6 Segment Routing"
    };

    return keywords[n];
}