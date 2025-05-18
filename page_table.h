#include "page_table_entry.h"
#include<iostream>
#include<string>
#ifndef PAGE_TABLE_H 
#define PAGE_TABLE_H 
class page_table{
    public:
    page_table_entry *table;
    unsigned int num_virtual_pages;
    page_table(): table(nullptr), num_virtual_pages(0){}
    page_table(unsigned int num_virtual_pages);
    ~page_table();
};
page_table::page_table(unsigned int num_virtual_pages){
    this->num_virtual_pages = num_virtual_pages;
    table = new page_table_entry[num_virtual_pages];
    for(int i=0;i<num_virtual_pages;i++){
        table[i] = page_table_entry();
    }
}
page_table::~page_table(){
    if(table != nullptr){
        delete []table;
        table = nullptr;
    }
}
#endif 