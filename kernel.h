#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "word.h"
#include "screenplay.h"
#include "fiomanip.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
//int file_condition[3] = {0,0,0}; //This saves the ustage condition of files


class Kernel
{
    public:
        Kernel(int vocabulary_bag,string menu_name,bool new_old);
        void kernel_run(void); //Local main
        ~Kernel();
    private:
        Wordlist *old_wordlist_;
        Wordlist *new_wordlist_;
        vector<string> candidate_bar_; //Select random candidate
        char right_answer_;
        //These three strings discribe three related files for program to run
        string sourcefile_;
        string new_word_file_;
        string old_word_file_;
        Filelist *new_filelist_; // Creat this file to be run time init file
        Filelist *old_filelist_;
        Filelist *source_filelist_;
        //These are runtime functions
        void judge(Word candidate); //determine the direction of the candidate
        Word valve(void); //Determine which Guy to be poped
        vector<string> wrong_gen(Word candidate); //generate wrong answer vector with 3 wrong answer.
        //Below is running condition diagnal function
        //This can show weather learning procedure has been completed
        int check_watermark(); //return 0 if both list is empty 1 is both is not empty 2: new 3: old is empty
};

#endif
