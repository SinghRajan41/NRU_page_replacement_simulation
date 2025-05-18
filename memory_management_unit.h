#include "page_table.h"
#include "volatile_memory.h"
#include "operating_system.h"
#include<iostream>
#include<string>
#ifndef MEMORY_MANAGEMENT_UNIT_H 
#define MEMORY_MANAGEMENT_UNIT_H 

class memory_management_unit{
    page_table *p_table;
    volatile_memory *ram;
    operating_system *os;
    unsigned int virt_addr_space_start;
    unsigned int page_size;
    public:
    memory_management_unit(page_table *p_table, volatile_memory *ram, operating_system *os, unsigned int virt_addr_space_start, unsigned int page_size): p_table(p_table), ram(ram), os(os), virt_addr_space_start(virt_addr_space_start), page_size(page_size){

    }
    unsigned long long int read_word_at(unsigned int virtual_address, bool &page_fault){
        int idx = (virtual_address - virt_addr_space_start) / page_size;
        std::cout<<("MMU:read_word_at() " + std::to_string(virtual_address))<<"\n";
        if(!p_table->table[idx].present_bit){
            os->handle_page_fault(virtual_address);
            page_fault = true;
        }
        return ram->read_word_at(p_table->table[idx].address + (virtual_address - virt_addr_space_start) % page_size);
    }
};
#endif 