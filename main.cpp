#include <bits/stdc++.h>
#include "page.h"
#include "page_table_entry.h"
#include "page_table.h"
#include "operating_system.h"
#include "non_volatile_memory.h"
#include "volatile_memory.h"
#include "not_recently_used_page_replacement.h"
#include "memory_management_unit.h"
#define ll long long int
#define all(x) x.begin(), x.end()
using namespace std;
int get_file_size(string file_path){
    return filesystem::file_size(filesystem::path(file_path));
}
void cpu(const unsigned int addr_space_start, const unsigned int addr_space_end, memory_management_unit &mmu){
    srand(time(0));
    const unsigned int addr_space_length = addr_space_end - addr_space_start + 1;
    unsigned int fault(0), page_hit(0);
    for(int i=0;i<5000;i++){
        unsigned int virtual_address = rand() % addr_space_length;
        bool page_fault = false;
        const unsigned long long int memory_word = mmu.read_word_at(virtual_address + addr_space_start, page_fault);
        cout<<"MEMORY REFERENCE: at virtual address = "<<virtual_address<<" is = "<<memory_word<<endl;
        if(page_fault){
            fault++;
        }else{
            page_hit++;
        }
    }
    std::cout<<"NUMBER OF WORDS REFERENCED = 5000"<<std::endl;
    std::cout<<"NUMBER OF PAGE FAULTS = "<<fault<<std::endl;
    std::cout<<"NUMBER OF PAGE HITS = "<<page_hit<<std::endl;
}
int main(int argc, char *argv[])
{
    unsigned int page_bits = 6;
    unsigned int page_size = 1 << page_bits;
    unsigned int addr_space_start = 0;
    unsigned int addr_space_end = get_file_size("./large_file.txt") - 1;
    unsigned int num_virtual_pages = (addr_space_end - addr_space_start + 1 + page_size - 1) / page_size;
    non_volatile_memory disk(20, page_size);
    disk.initialise_with_file("./large_file.txt");
    volatile_memory ram(10, page_size);
    page_table p_table(num_virtual_pages);
    not_recently_used_page_replacement replacement_algo(&p_table, num_virtual_pages);
    operating_system os(&disk, &ram, &p_table, &replacement_algo, page_size, addr_space_start, addr_space_end);
    memory_management_unit mmu(&p_table, &ram, &os, addr_space_start, page_size);
    cpu(addr_space_start, addr_space_end, mmu);
    return 0;
}