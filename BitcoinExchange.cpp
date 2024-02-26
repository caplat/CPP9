#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const std::string &filename):filename_(filename){}

BitcoinExchange::~BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src){

    filename_ = src.filename_;
    datamap_ = src.datamap_;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &rhs){

    if(this != &rhs){

        filename_ = rhs.filename_;
        datamap_ = rhs.datamap_;
    }
    return(*this);
}

void BitcoinExchange::data_in_map(){

    std::ifstream file("data.csv");
    if(!file.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    std::string line;
    bool firstline = true;
    while(std::getline(file,line))
    {
       if(firstline)
       {
            firstline = false;
            continue;
       }
        std::stringstream ss(line);
        std::string date, value_str;
        
        if(std::getline(ss,date,',') && std::getline(ss,value_str))
        {
            
            double value;
            std::stringstream(value_str) >> value;
            datamap_.insert(std::make_pair(date,value));
        }
        else
            std::cerr << "Error: Invalid output line" << std::endl;
    }
    file.close();
}

void BitcoinExchange::print_map()const{

    for (std::map<std::string, double>::const_iterator it = datamap_.begin(); it != datamap_.end(); ++it) {
        std::cout << "map_Date: " << it->first << ", map_Value: " << it->second << std::endl;
    }
}

void BitcoinExchange::parse_input(){

    std::ifstream file(filename_.c_str());
    if(!file.is_open()){
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    std::string line;
    bool firstline = true;
    while(std::getline(file,line))
    {
        if(firstline)
        {
            firstline = false;
            continue;
        }
        std::stringstream ss(line);
        std::string date, value_str;
        if(std::getline(ss,date,'|') && std::getline(ss,value_str)){

            date.erase(0, date.find_first_not_of(" \t"));
            date.erase(date.find_last_not_of(" \t") + 1);
            value_str.erase(0, value_str.find_first_not_of(" \t"));
            value_str.erase(value_str.find_last_not_of(" \t") + 1);
            if(date.empty() || value_str.empty()){
                std::cout << "Error: Date or/and value is empty" << std::endl;
                continue;
            }
            if(!is_date_valid(date)){
                std::cout << "Error: " << date << " is not a valid date" << std::endl;
            }
            else if(!is_number_valid(value_str)){
                std::cout << "Error: " << value_str << " is < 0 or > 1000" 
                << std::endl;
            }
            if(is_date_valid(date) && is_number_valid(value_str)){
                compare_date(date,value_str);
            }
        }
        else
            std::cout << "Error: bad input => " << line << std::endl;
    }
}

bool BitcoinExchange::is_date_valid(const std::string &date){

    if(date.length() != 10)
        return(false);
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (int i = 0; i < 10; ++i) {
        if (i != 4 && i != 7 && !isdigit(date[i]))
            return false;
    }
    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());

    if(year < 2009 || year > 2025 || month < 1 || month > 12
        || day < 1 || day > 31)
        return false;
    return(true);
}

bool BitcoinExchange::is_number_valid(const std::string &number_str){

    std::istringstream iss(number_str);
    int int_value;
    float float_value;

    iss >> int_value;
    if(!iss.fail() && int_value >= 0 && int_value <= 1000){
        return true;
    }

    iss.clear();
    iss.seekg(0);
    iss >> float_value;
    if(!iss.fail() && float_value >= 0 && float_value <= 1000){
        return(true);
    }
    return(false);
}

void BitcoinExchange::compare_date(const std::string &date,const std::string &value_str){

    std::map<std::string, double>::iterator it = datamap_.upper_bound(date);
    if(it != datamap_.begin())
        it--;
    std::istringstream iss(value_str);
    double double_value;
    iss >> double_value;
    std::cout << date << " => " << double_value << " = " << double_value * it->second << std::endl;
}