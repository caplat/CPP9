#include "BitcoinExchange.hpp"

int main(int argc,char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    BitcoinExchange exchange(argv[1]);
    exchange.data_in_map();
    // exchange.print_map();
    exchange.parse_input();
    return(0);
}