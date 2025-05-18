#include "page.h"
#include<stdexcept>
#include<iostream>
#include<string>
#ifndef VOLATILE_MEMORY_H 
#define VOLATILE_MEMORY_H 

class volatile_memory{
    unsigned int addressable_bits;
    unsigned int page_size;
    unsigned int pages_in_memory;
    unsigned long long int *words;
    bool *occupied;
    public:
    volatile_memory() : addressable_bits(0), page_size(0), pages_in_memory(0), words(nullptr), occupied(nullptr) {}
    volatile_memory(unsigned int addressable_bits, unsigned int page_size);
    ~volatile_memory();
    unsigned long long int read_word_at(unsigned int address);
    void write_word_at(unsigned int address, unsigned long long int word);
    page read_page(unsigned int address);
    void write_page(unsigned int address, page &page_to_write);
    unsigned int write_page_in_empty_space(page &page_to_write);
    bool has_empty_page_frame();
};
volatile_memory::volatile_memory(unsigned int addressable_bits, unsigned int page_size){
    pages_in_memory = 0;
    this->addressable_bits = addressable_bits;
    this->page_size = page_size;
    words = new unsigned long long int[1 << addressable_bits];
    occupied = new bool[(1 << addressable_bits) / page_size];
    for(int i=0;i<((1 << addressable_bits) / page_size);i++){
        occupied[i] = false;
    }
    for(int i=0;i<(1 << addressable_bits);i++){
        words[i] = 4000000000ULL;
    }
}
volatile_memory::~volatile_memory(){
    if (words != nullptr) {
        delete []words;
        words = nullptr;
    }
    if (occupied != nullptr) {
        delete []occupied;
        occupied = nullptr;
    }
}
unsigned long long int volatile_memory::read_word_at(unsigned int address){
    if(address < 0 || address >= (1 << addressable_bits)){
        throw std::invalid_argument("volatile_memory.read_word_at() : address=" + std::to_string(address) + " is out of bounds\nAddress should be in [0," + std::to_string(1 << addressable_bits) + ")");
    }else{
        return words[address];
    }
}
void volatile_memory::write_word_at(unsigned int address, unsigned long long int word){
    if(address < 0 || address >= (1 << addressable_bits)){
        throw std::invalid_argument("volatile_memory.write_word_at() : address=" + std::to_string(address) + " is out of bounds\nAddress should be in [0," + std::to_string(1 << addressable_bits) + ")");
    }else{
        words[address] = word;
    }
}
page volatile_memory::read_page(unsigned int address){
    if(address < 0 || (address + page_size > (1 << addressable_bits))){
        throw std::domain_error("volatile_memory.read_page(): Out of Bounds Error\nValid Range [0," + std::to_string(1 << addressable_bits) + ")\n" + "Range Given in Arguement [" + std::to_string(address) + "," + std::to_string(address + page_size) + ")");
    }else{
        page p(page_size);
        for(int i=0;i<page_size;i++){
            p.words[i] = words[address + i];
        }
        return p;
    }
}
void volatile_memory::write_page(unsigned int address, page &page_to_write){
    if(address < 0 || (address + page_size > (1 << addressable_bits))){
        throw std::domain_error("volatile_memory.write_page(): Out of Bounds Error\nValid Range [0," + std::to_string(1 << addressable_bits) + ")\n" + "Range Given in Arguement [" + std::to_string(address) + "," + std::to_string(address + page_size) + ")");
    }else{
        for(int i=0;i<page_size;i++){
            words[address + i] = page_to_write.words[i];
        }
    }
}
unsigned int volatile_memory::write_page_in_empty_space(page &page_to_write){
    int num = (1<<addressable_bits) / page_size;
    for(int i=0;i<num;i++){
        if(!occupied[i]){
            occupied[i] = true;
            write_page(i*page_size, page_to_write);
            return i*page_size;
        }
    }
    throw std::exception();
}
bool volatile_memory::has_empty_page_frame(){
    int num = (1<<addressable_bits) / page_size;
    for(int i=0;i<num;i++){
        if(!occupied[i]){
            return true;
        }
    }
    return false;
}
#endif