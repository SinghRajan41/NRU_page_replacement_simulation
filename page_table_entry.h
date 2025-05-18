#include<iostream>
#include<string>
#ifndef PAGE_TABLE_ENTRY_H 
#define PAGE_TABLE_ENTRY_H 

class page_table_entry{
    public:
    unsigned int address;
    bool present_bit;
    bool read_permission_bit;
    bool write_permission_bit;
    bool execute_permission_bit;
    bool referenced_bit;
    bool modified_bit;
    page_table_entry();
    page_table_entry(unsigned int address, bool present_bit, bool read_permission_bit, bool write_permission_bit, bool execute_permission_bit, bool referenced_bit, bool modified_bit);
};

page_table_entry::page_table_entry(){\
    this->address = 2e9;
    this->present_bit = false;
    this->read_permission_bit = false;
    this->write_permission_bit = false;
    this->execute_permission_bit = false;
    this->referenced_bit = false;
    this->modified_bit = false;
}
page_table_entry::page_table_entry(unsigned int address, bool present_bit, bool read_permission_bit, bool write_permission_bit, bool execute_permission_bit, bool referenced_bit, bool modified_bit){
    this->address = address;
    this->present_bit = present_bit;
    this->read_permission_bit = read_permission_bit;
    this->write_permission_bit = write_permission_bit;
    this->execute_permission_bit = execute_permission_bit;
    this->referenced_bit = referenced_bit;
    this->modified_bit = modified_bit;
}
#endif