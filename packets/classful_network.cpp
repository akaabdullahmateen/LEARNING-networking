#include <iostream>
#include <string>
#include <bitset>

#include "classful_network.h"

Classful_network::Classful_network(){
	default_initialize();
}

Classful_network::Classful_network(const std::string &ipv4_address){
	if(is_address_valid(ipv4_address)) address = ipv4_address;
	else default_initialize();
}

void Classful_network::default_initialize(){
	address = "0.0.0.0";
	for(unsigned int &i : octets){
		i = 0;
	}
}

bool Classful_network::is_octets_valid(const std::string &ipv4_address){
	std::string dot = ".";
	std::size_t pos = 0;
	std::size_t begin = 0;
	std::size_t i 	= 0;
	std::string tokens[4];
	unsigned int temp_octets[4];

	while((pos = ipv4_address.find(dot, begin)) != std::string::npos){
		tokens[i++] = ipv4_address.substr(begin, pos - begin);
		begin = pos + 1;
	}
	tokens[i] = ipv4_address.substr(begin);
	
	for(std::size_t idx = 0; idx < 4; ++idx){
		temp_octets[idx] = std::stoi(tokens[idx]);
	}

	for(const unsigned int i : temp_octets){
		if(i > 255){
			return false;
		}
	}

	for(std::size_t idx = 0; idx < 4; ++idx){
		octets[idx] == temp_octets[idx];
	}

	return true;
}

std::size_t Classful_network::get_dot_count(const std::string &ipv4_address){
	std::string dot = ".";
	std::size_t dot_count = 0;
	std::size_t pos = 0;
	std::size_t begin = 0;

	while((pos = ipv4_address.find(dot, begin)) != std::string::npos){
		++dot_count;
		begin = pos + 1;
	}

	return dot_count;
}

bool Classful_network::is_length_valid(const std::string &ipv4_address){
	if(ipv4_address.empty()){
		return false;
	}
	if(ipv4_address.length() < 7){
		return false;
	}
	if(ipv4_address.length() > 15){
		return false;
	}

	return true;
}

bool Classful_network::is_address_valid(const std::string &ipv4_address){
	return (is_length_valid(ipv4_address) && (get_dot_count(ipv4_address) == 3) && is_octets_valid(ipv4_address));
}

std::string Classful_network::get_address_class(){
	std::string token = address.substr(0, address.find("."));
	std::bitset<8> octet(std::stoi(token));
		
	if(octet[7] == 0) return "A";
	if(octet[7] == 1 && octet[6] == 0) return "B";
	if(octet[7] == 1 && octet[6] == 1 && octet[5] == 0) return "C";
	if(octet[7] == 1 && octet[6] == 1 && octet[5] == 1 && octet[4] == 0) return "D";
	if(octet[7] == 1 && octet[6] == 1 && octet[5] == 1 && octet[4] == 1) return "E";
	return "Undefined";
}

void Classful_network::display_blueprint(){

	std::cout << "\t\'n\' indicates a bit used for network ID" << std::endl;
	std::cout << "\t\'H\' indicates a bit used for host ID" << std::endl;
	std::cout << "\t\'X\' indicates a bit without a specified purpose" << std::endl;
	std::cout << std::endl;

	std::cout << "\tClass A" << std::endl;
	std::cout << "\t  0.  0.  0.  0 = 00000000.00000000.00000000.00000000" << std::endl;
	std::cout << "\t127.255.255.255 = 01111111.11111111.11111111.11111111" << std::endl;
	std::cout << "\t                  0nnnnnnn.HHHHHHHH.HHHHHHHH.HHHHHHHH" << std::endl;
	std::cout << std::endl;

	std::cout << "\tClass B" << std::endl;
	std::cout << "\t128.  0.  0.  0 = 10000000.00000000.00000000.00000000" << std::endl;
	std::cout << "\t191.255.255.255 = 10111111.11111111.11111111.11111111" << std::endl;
	std::cout << "\t                  10nnnnnn.nnnnnnnn.HHHHHHHH.HHHHHHHH" << std::endl;
	std::cout << std::endl;


	std::cout << "\tClass C" << std::endl;
	std::cout << "\t192.  0.  0.  0 = 11000000.00000000.00000000.00000000" << std::endl;
	std::cout << "\t223.255.255.255 = 11011111.11111111.11111111.11111111" << std::endl;
	std::cout << "\t                  110nnnnn.nnnnnnnn.nnnnnnnn.HHHHHHHH" << std::endl;
	std::cout << std::endl;


	std::cout << "\tClass D" << std::endl;
	std::cout << "\t224.  0.  0.  0 = 11100000.00000000.00000000.00000000" << std::endl;
	std::cout << "\t239.255.255.255 = 11101111.11111111.11111111.11111111" << std::endl;
	std::cout << "\t                  1110XXXX.XXXXXXXX.XXXXXXXX.XXXXXXXX" << std::endl;
	std::cout << std::endl;


	std::cout << "\tClass E" << std::endl;
	std::cout << "\t240.  0.  0.  0 = 11110000.00000000.00000000.00000000" << std::endl;
	std::cout << "\t255.255.255.255 = 11111111.11111111.11111111.11111111" << std::endl;
	std::cout << "\t                  1111XXXX.XXXXXXXX.XXXXXXXX.XXXXXXXX" << std::endl;
}
