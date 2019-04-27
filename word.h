#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstdlib>

using namespace std;

//This is The main Data structure of the Project
//Word is the basic unit; It saves the content, discription and rank of a word
//The answer handler can automatically change the rank of the word.

class Word
{
    public:
        Word(vector<string> word_init);
        Word();
        string ShowWord();
        string ShowDescription();
        string ShowExplain();
        vector<string> getWord_raw(); //For file saving
        void Right_Handler(); //Change the index
        void Wrong_Handler();
        int getRank();
        ~Word(); //Since this class mentioned the dynamic memory the destructor is neccessary
    private:
        vector<string> word_content_; //This is a Struct Like vector
}; 

//This word list is actually a 2-D vector;
//It can work mutually better with filelist
//insert can insert a word into the word list automatically sorted with its ranking
//The Higher the ranking is, the former the word will be
class Wordlist
{
    public:
        Wordlist(vector<vector<string>> new_list);
        int insert(Word new_word);
        void push_back(Word new_word);
        Word pop_front(void);
        int getSize();
        ~Wordlist();
    private:
        vector<Word> word_list_;
        vector<Word>::iterator word_itr_;
        int size_;
};
