#include "word.h"
//=====================Start_class_word========================
word::word(vector<string> word_init)
{
    wordcontent = new vector<string>;
    *wordcontent = word_init;
}

string word::ShowWord()
{
    return *wordcontent[0];
}

string word::ShowDescription()
{
    return *wordcontent[1];
}

int word::getRank()
{
    return (int)(*wordcontent[2][0]-'0');
}

vector<string> word::getWord_raw()
{
    return *wordcontent;
}

void word::Right_Handler()
{
    *wordcontent[2][0]-=5;
}

void word::Wrong_Handler()
{
    
    *wordcontent[2][0]--; 
}

word::~word()
{
    delete wordcontent;
    wordcontent = NULL;
}
//=====================End_Class_word============================

//=====================Start_Class_wordlist======================
wordlist::wordlist(vector<vector<string>> new_list)
{
    word_list = new vector<word>;
    int index=0;
    while(index<new_list.size())
    {
        word new_word(new_list[index]);
        word_list->push_back(new_word);
    }
    size = new_list.size();
}

void wordlist::insert(word new_word)
{
    for(int i = 0;i<size;i++)
    {
        if(new_word.getRank()>*word_list[i].getRank())
        {
            word_list->insert(word_list->begin()+i,new_word);
            size++;
            return;
        }
    }
    word_list->push_back(new_word);
    size++;
    return;
}

void wordlist::push_back(word new_word)
{
    word_list->push_back(new_word);
    size++;
}

word wordlist::pop_front(void)
{
    if(size>0)
    {    
        word result = *word_list[0];
        word_list->erase(word_list->begin(),word_list->begin()+1);
        size--;
        return result;
    }
    cout<<"No Word to Pop!"<<endl;
    exit(1);
}

wordlist::~wordlist()
{
    delete word_list;
    word_list = NULL;
}
//=================================End_Wordlist=====================================


