#include<iostream>
#include<iostream>
#include<string>
#ifndef PAGE_H
#define PAGE_H
class page
{
public:
    unsigned int page_size;
    unsigned long long int *words;
    page(): page_size(-1), words(nullptr){}
    page(unsigned int page_size);
    ~page();
    void print_page(){
        for(int i=0;i<page_size;i++){
            std::cout<<words[i]<<" ";
        }
        std::cout<<std::endl;
    }
};

page::page(unsigned int page_size)
{
    this->page_size = page_size;
    words = new unsigned long long int[page_size];
    for(int i=0;i<page_size;i++){
        words[i] = 3e9;
    }
}

page::~page()
{
    if(words != nullptr){
        delete []words;
        words = nullptr;
    }
}
#endif
