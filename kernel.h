#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "word.h"
#include "screenplay.h"
#include "fiomanip.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>



class kernel
{
    public:
        kernel(int vocabulary_bag,string menu_name,bool new_old);
        kernel_run(void); //Local main
    private:
        wordlist *old_wordlist;
        wordlist *new_wordlist;
        vector<string> candidate_bar; //Select random candidate
        char right_answer;
        //These three strings discribe three related files for program to run
        string sourcefile;
        string new_word_file;
        string old_word_file;
        filelist *new_filelist; // Creat this file to be run time init file
        filelist *old_filelist;
        filelist *source_filelist;
        //These are runtime functions
        void judge(word candidate); //determine the direction of the candidate
        word valve(void); //Determine which Guy to be poped
        vector<string> wrong_gen(); //generate wrong answer vector with 3 wrong answer.
        //Below is running condition diagnal function
        //This can show weather learning procedure has been completed
        int check_watermark(); //return 0 if both list is empty 1 is both is not empty 2: new 3: old is empty
};

#endif