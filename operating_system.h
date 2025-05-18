#include "non_volatile_memory.h"
#include "volatile_memory.h"
#include "page_table.h" 
#include "not_recently_used_page_replacement.h"
#include<iostream>
#include<string>
#ifndef OPERATING_SYSTEM_H 
#define OPERATING_SYSTEM_H 
class operating_system{
    non_volatile_memory *disk;
    volatile_memory *ram;
    page_table *p_table;
    not_recently_used_page_replacement *replacement_algo;
    unsigned int page_size;
    unsigned int virt_addr_space_start;
    unsigned int virt_addr_space_end;
    public:
    
    operating_system();

    operating_system(non_volatile_memory *disk, volatile_memory *ram, page_table *p_table, not_recently_used_page_replacement *replacement_algo, unsigned int page_size, unsigned int virt_addr_space_start, unsigned int virt_addr_space_end)
        : disk(disk), ram(ram), p_table(p_table), replacement_algo(replacement_algo), page_size(page_size), virt_addr_space_start(virt_addr_space_start), virt_addr_space_end(virt_addr_space_end) {
    }
    void handle_page_fault(int virtual_address);
};

void operating_system::handle_page_fault(int virtual_address){
    unsigned int req_page_start_addr = (virtual_address - virt_addr_space_start) / page_size;
    req_page_start_addr *= page_size;
    page required_page = disk->read_page(req_page_start_addr);
    if(ram->has_empty_page_frame()){
        unsigned int address = ram->write_page_in_empty_space(required_page);
        p_table->table[req_page_start_addr / page_size] = page_table_entry(address, true, true, true, true, false, false);
    }else{
        int victim_page_idx = replacement_algo->get_victim_page();
        unsigned int victim_page_phy_addr = p_table->table[victim_page_idx].address;
        if(p_table->table[victim_page_idx].modified_bit){
            page victim_page = ram->read_page(victim_page_phy_addr);
            disk->write_page(victim_page_idx*page_size, victim_page);
        }
        p_table->table[victim_page_idx] = page_table_entry((int)0, false, false, false, false, false, false);
        ram->write_page(victim_page_phy_addr, required_page);
        p_table->table[req_page_start_addr / page_size] = page_table_entry(victim_page_phy_addr, true, true, true, true, false, false);
    }
}
#endif 