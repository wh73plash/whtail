#include "Header.h"

using namespace std;
using namespace rang;

#define clr_red 0
#define clr_yellow 1
#define clr_green 2

static unsigned long long int read_char = 0;

const static std::vector<std::pair<std::string, uint8_t>> key_word = {
    std::make_pair("ERROR", clr_red),
    std::make_pair("WARNING", clr_yellow),
    std::make_pair("SUCCESS", clr_green)
};

inline void display_log(std::vector<std::string> log_list){
    for(const auto& i : log_list){
        if(i.find(key_word[0].first) != std::string::npos){
            std::cout << rang::fg::red << i;
            std::cout.flush();
        }else if(i.find(key_word[1].first) != std::string::npos){
            std::cout << rang::fg::yellow << i;
            std::cout.flush();
        }else if(i.find(key_word[2].first) != std::string::npos){
            std::cout << rang::fg::green << i;
            std::cout.flush();
        }else{
            std::cout << rang::fg::reset << i;
            std::cout.flush();
        }
    }
    return;
}

inline void read_log(std::string path, FILE* fp){
    std::vector<std::string> log_pool;
    
    char line[1024];
    std::fseek(fp, read_char, SEEK_SET);
    while(std::fgets(line, sizeof(line), fp) != NULL){
        log_pool.push_back(line);
        ++read_char;
    }
    read_char = std::ftell(fp);
    display_log(log_pool);
    
    return;
}

int32_t main(const int argc, const char** argv, const char** env){
    std::cout << "Run in : [ " << argv[0] << " ] argc : " << argc << std::endl;
    std::string log_file_path;
    rang::setControlMode(rang::control::Auto);
    if(argc != 2){
        std::cout << rang::fg::yellow << "[Please type log file] > " << rang::style::reset;
        std::string buffer;
        std::getline(std::cin, buffer);
        log_file_path = buffer;
    }else{
        std::string buffer = argv[1];
        for(const auto& i : buffer)
            if(i == '-'){
                std::cout << rang::fg::red << "usage : ./whtail (target file path)" << std::endl;
                return EXIT_FAILURE;
            }
        log_file_path = argv[1];
    }
    do{
        FILE* fp = NULL;
        fp = std::fopen(log_file_path.c_str(), "rt");
        if(fp == NULL){
            std::cout << rang::fg::red << "File open error" << std::endl;
            return EXIT_FAILURE;
        }else{
            read_log(log_file_path, fp);
            std::fclose(fp);
        }
    }while(true);
    
    return EXIT_SUCCESS;
}
