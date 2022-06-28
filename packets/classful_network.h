#ifndef CLASSFUL_NETWORK_H
#define CLASSFUL_NETWORK_H

class Classful_network{
private:
	std::string address;
	unsigned int octets[4];

	void default_initialize();
	bool is_octets_valid(const std::string &ipv4_address);
	std::size_t get_dot_count(const std::string &ipv4_address);
	bool is_length_valid(const std::string &ipv4_address);
	bool is_characters_dot_or_digit(const std::string &ipv4_address);
	bool is_address_valid(const std::string &ipv4_address);

public:
	Classful_network();
	Classful_network(const std::string &ipv4_address);
	void display_blueprint();
	std::string get_address_class();
};

#endif