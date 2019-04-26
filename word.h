#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstdlib>

using namespace std;

//This is The main Data structure of the Project
//Word is the basic unit; It saves the content, discription and rank of a word
//The answer handler can automatically change the rank of the word.

class word
{
    public:
        word(vector<string> word_init);
        word();
        string ShowWord();
        string ShowDescription();
        string ShowExplain();
        vector<string> getWord_raw(); //For file saving
        void Right_Handler(); //Change the index
        void Wrong_Handler();
        int getRank();
        ~word(); //Since this class mentioned the dynamic memory the destructor is neccessary
    private:
        vector<string> wordcontent; //This is a Struct Like vector
}; //其实这里写成动态内存没有实际意义。。。要不要该前面的结构，全部写成指针？？？可以节省空间

//This word list is actually a 2-D vector;
//It can work mutually better with filelist
//insert can insert a word into the word list automatically sorted with its ranking
//The Higher the ranking is, the former the word will be
class wordlist
{
    public:
        wordlist(vector<vector<string>> new_list);
        int insert(word new_word);
        void push_back(word new_word);
        word pop_front(void);
        int getSize();
        ~wordlist();
    private:
        vector<word> word_list;
        vector<word>::iterator word_itr;
        int size;
};
