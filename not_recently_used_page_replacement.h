#include "page_table.h"
#include "page_table_entry.h"
#include<stdexcept>
#include<iostream>
#include<string>
#ifndef NOT_RECENTLY_USED_PAGE_REPLACEMENT_H 
#define NOT_RECENTLY_USED_PAGE_REPLACEMENT_H
class not_recently_used_page_replacement{
    page_table *p_table;
    unsigned int num_virtual_pages;
    public:
    not_recently_used_page_replacement() : p_table(), num_virtual_pages(0) {}
    not_recently_used_page_replacement(page_table *p_table, int num_virtual_pages);
    int get_victim_page();
};


not_recently_used_page_replacement::not_recently_used_page_replacement(page_table *p_table, int num_virtual_pages): p_table(p_table), num_virtual_pages(num_virtual_pages) {

}
int not_recently_used_page_replacement::get_victim_page(){
    int mx = 4;
    for(int i=0;i<num_virtual_pages;i++){
        if(p_table->table[i].present_bit == false)  continue;
        int bit = 0;
        if(p_table->table[i].modified_bit) bit += 1;
        if(p_table->table[i].referenced_bit)    bit += 2;
        mx = std::min(mx, bit);
    }
    if(mx == 4){
        throw std::runtime_error("not_recently_used_page_replacement.get_victim_page: Cannot Evict a Page from an Empty page table");
    }else{
        for(int i=0;i<num_virtual_pages;i++){
            if(p_table->table[i].present_bit == false)  continue;
            int bit = 0;
            if(p_table->table[i].modified_bit) bit += 1;
            if(p_table->table[i].referenced_bit)    bit += 2;
            if(bit == mx){
                return i;
            }
        }
        throw std::runtime_error("not_recently_used_page_replacement.get_victim_page: victim page not found");
    }
}
#endif 