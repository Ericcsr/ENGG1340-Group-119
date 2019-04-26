#ifndef __FIOMANIP_H__
#define __FIOMANIP_H__

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
//Same format read and write
//Input a 2-D list, save each sub-list as a line in a file
//Each Item is separated by given seperator default = '@'
//The sequence need to be First in First out
//Detailed Explanation and implementation please refers to CPP file
void file_error_handler(string name);
int check_file(int file_condition[]);
void reset_check_file(int index,int file_condition[]);
int file_condition[3] = {0,0,0}; //This saves the ustage condition of files

class filelist
{
    public:
        filelist(string infile,string outfile);
        vector<string> pop_end(void);
        vector<string> pop_front(void);
        void push_head(vector<string> new_item);
        void append(vector<string> new_item);
        void remove(int index);
        int search(vector<string> target);
        void insert(vector<string> target,int index);
        vector<vector<string>> getRawdata();
        void setRawdata(vector<vector<string>>);
        void refresh(void);
        int getSize(void);
        vector<string> &operator[](int i);
        ~filelist();
    private:
        vector<vector<string>> *buffer_list;
        vector<vector<string>>::iterator list_itr;
        string ifile;
        string ofile;
        int size = 0;
        void readFile(string infile);
        void writeFile(string outfile);
        string FormatHandler(vector<string>);
};

#endif
