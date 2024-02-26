#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include<cstdlib>
// #include <string>
// #include<limits>

class BitcoinExchange{


    public :

        BitcoinExchange(const std::string &filename);
        BitcoinExchange(const BitcoinExchange &src);
        BitcoinExchange& operator=(const BitcoinExchange &rhs);
        ~BitcoinExchange();

        void data_in_map();
        void print_map()const;
        void parse_input();
        bool is_date_valid(const std::string &date);
        bool is_number_valid(const std::string &number_str);
        void compare_date(const std::string &date,const std::string &value_str);
        
    private :

        BitcoinExchange();
        std::string filename_;
        std::map<std::string, double> datamap_;
};


#endif