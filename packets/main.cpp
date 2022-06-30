#include <iostream>
#include <string>
#include <map>

#include "ipv4_header.h"
#include "classful_network.h"

int main(int argc, char *argv[]){
    unsigned char ipv4_dump[] =  {0x45,0x88,0x00,0x34,0x73,0x0a,0x00,0x00,0x79,0x06,0x4b,0x20,0xac,0xd9,0x15,0x23,0xc0,0xa8,0x00,0x6d};

    Ipv4_header ipv4_header(std::begin(ipv4_dump), std::end(ipv4_dump));

    std::cout << std::endl;
    std::cout << "IPv4 Packet Analyzer v1.0-beta" << std::endl;
    std::cout << "Copyright (C) 2022 Yahya Mateen" << std::endl;
    std::cout << "Licensed under GNU-GPLv3" << std::endl;

    std::cout << std:: endl;
    std::cout << "IPv4 Header Raw:" << std::endl;
    std::cout << std::endl;
    ipv4_header.display_raw();
    
    std::cout << std::endl;
    std::cout << "IPv4 Header Blueprint:" << std::endl;
    std::cout << std::endl;
    ipv4_header.display_blueprint();
    
    std::cout << std::endl;
    std::cout << "IPv4 Header Analysis:" << std::endl;
    std::cout << std::endl;
    ipv4_header.display_header();
    
    Classful_network classful_network;

    std::cout << std::endl;
    std::cout << "Classful Network Blueprint:" << std::endl;
    std::cout << std::endl;
    classful_network.display_blueprint();
    

    return 0;
}