#ifndef IPV4_HEADER
#define IPV4_HEADER

#include <string>
#include <map>

class Ipv4_header{
private:
	unsigned char dump[60];
	std::map<std::string, std::string> header;

	void default_initialize_dump();
	void initialize_header();
	unsigned int calculate_checksum();
	std::string get_dscp_keyword(unsigned int n);
	std::string get_ecn_keyword(unsigned int n);
	std::string get_protocol_keyword(unsigned int n);


public:
	Ipv4_header();
	Ipv4_header(unsigned char *begin, unsigned char *end);
	void display_blueprint();
	void display_header();
	void display_raw();
	std::map<std::string, std::string> get_header();
};

#endif