#include "page.h"
#include<exception>
#include<stdexcept>
#include<string>
#include<iostream>
#include<fstream>
#include<string>
#include<filesystem>
#include<ios>
#ifndef NON_VOLATILE_MEMORY_H 
#define NON_VOLATILE_MEMORY_H 

class non_volatile_memory {
    unsigned int addressable_bits;
    unsigned int page_size;
    unsigned long long int *words;
    public:
    non_volatile_memory(unsigned int addressable_bits, unsigned int page_size);
    ~non_volatile_memory();
    unsigned long long int read_word_at(unsigned int address);
    void write_word_at(unsigned int address, unsigned long long int word);
    page read_page(unsigned int start);
    void write_page(unsigned int start, page &page_to_write);
    void initialise_with_file(std::string file_path);
    int get_file_size(std::string file_path){
        return std::filesystem::file_size(std::filesystem::path(file_path));
    }
};

void non_volatile_memory::initialise_with_file(std::string file_path){
    std::ifstream ifs(file_path, std::ios::in);
    for(int i=0;!ifs.eof();i++){
        words[i] = ifs.get();
    }
    int fs = get_file_size(file_path);
    for(int i=get_file_size(file_path);i<(1<<addressable_bits);i++){
        words[i] = words[i % fs];
    }
    ifs.close();
}
non_volatile_memory::non_volatile_memory(unsigned int addressable_bits, unsigned int page_size){
    words = nullptr;
    this->addressable_bits = addressable_bits;
    this->page_size = page_size;
    words = new unsigned long long int[(1 << addressable_bits)];
    for(int i=0;i<(1<<addressable_bits);i++){
        words[i] = 4e9;
    }
}
non_volatile_memory::~non_volatile_memory(){
    if(words != nullptr){
        delete []words;
        words = nullptr;
    }
}
unsigned long long int non_volatile_memory::read_word_at(unsigned int address){
    if(address < 0 || address >= (1<<addressable_bits)){
        throw std::invalid_argument("non_volatile_memory.read_word_at() : address=" + std::to_string(address) + " is out of bounds\nAddress should be in [0," + std::to_string(1 << addressable_bits) + ")");
    }else{
        return words[address];
    }
}
void non_volatile_memory::write_word_at(unsigned int address, unsigned long long int word){
    if(address < 0 || address >= (1<<addressable_bits)){
        throw std::invalid_argument("non_volatile_memory.write_word_at() : address=" + std::to_string(address) + " is out of bounds\nAddress should be in [0," + std::to_string(1 << addressable_bits) + ")");
    }else{
        words[address] = word;
    }
}
page non_volatile_memory::read_page(unsigned int start){
    if(start < 0 || ((start + page_size) > (1 << addressable_bits))){
        throw std::invalid_argument("nonvolatile_memory.read_page() : Out of Bounds Error\nValid Range [0," + std::to_string(1 << addressable_bits) + ")\n" + "Range Given in Arguement [" + std::to_string(start) + "," + std::to_string(start + page_size) + ")");
    }
    page p(page_size);
    for(int i=0;i<page_size;i++){
        p.words[i] = words[start + i];
    }
    return p;
}
void non_volatile_memory::write_page(unsigned int start, page &page_to_write){
    if(start < 0 || (start + page_size > (1 << addressable_bits))){
        throw std::invalid_argument("non_volatile_memory:write_page(): Out of Bounds Error\nValid Range [0," + std::to_string(1 << addressable_bits) + ")\n" + "Range Given in Arguement [" + std::to_string(start) + "," + std::to_string(start + page_size) + ")");
    }else{
        for(int i=0;i<page_size;i++){
            words[start + i] = page_to_write.words[i];
        }
    }
}
#endif 