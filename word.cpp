#include "word.h"
//=====================Start_class_word========================
word::word(vector<string> word_init)
{
    //wordcontent = new vector<string>;
    wordcontent = word_init;
}

word::word(){}

string word::ShowWord()
{
    return wordcontent[0];
}

string word::ShowDescription()
{
    return wordcontent[1];
}

string word::ShowExplain()
{
  return wordcontent[2];
}

int word::getRank()
{
    return (int)(wordcontent[3][0]-'0');
}

vector<string> word::getWord_raw()
{
    return wordcontent;
}

void word::Right_Handler()
{
    //(*wordcontent)[2][0]-=5;
    (wordcontent)[3][0] = '0';
}

void word::Wrong_Handler()
{

    wordcontent[3][0]--;
}

word::~word()
{
    //delete wordcontent;
    //wordcontent = NULL;
}
//=====================End_Class_word============================

//=====================Start_Class_wordlist======================
wordlist::wordlist(vector<vector<string>> new_list)
{
    //word_list = new vector<word>;
    int index=0;
    size = new_list.size();
    while(index<size)
    {

        word new_word(new_list[index]);
        //cout<<new_word.getRank()<<endl;
        word_list.push_back(new_word);
        //cout<<<<end;

        //cout<<"I am alive"<<endl;
        //cout<<new_word.ShowDescription()<<endl;
        //cout<<"I am alive"<<endl;
        index++;

    }
    //cout<<"I am alive"<<endl;


}

int wordlist::insert(word new_word)
{
    for(int i = 0;i<size;i++)
    {
        //cout<<new_word.getRank()<<" "<<word_list[i].getRank()<<endl;
        if(new_word.getRank()>word_list[i].getRank())
        {
            word_list.insert(word_list.begin()+i,new_word);
            size++;
            return i;
        }
    }
    word_list.push_back(new_word);
    //cout<<"Fool"<<endl;
    size++;
    return size-1;
}

void wordlist::push_back(word new_word)
{
    word_list.push_back(new_word);
    size++;
}

word wordlist::pop_front(void)
{
    if(size>0)
    {
        word result = word_list[0];
        word_list.erase(word_list.begin(),word_list.begin()+1);
        size--;
        return result;
    }
    cout<<"No Word to Pop!"<<endl;
    exit(1);
}

int wordlist::getSize()
{
  return size;
}

wordlist::~wordlist()
{
    //delete word_list;
    //word_list = NULL;
}
//=================================End_Wordlist=====================================
/*
//Below are functons for debugging
//#define DEBUG
#ifdef DEBUG
//#define WORD_DEBUG
#define WORD_LIST_DEBUG
int main()
{
  vector<string> apple = {"Apple","A red Fruit","9"};
  vector<string> pear = {"Pear","A Sweet Fruit","9"};
  vector<string> banana = {"Banana","A Yellow fruit","9"};
  vector<vector<string>> test_list = {apple,pear};
  #ifdef WORD_DEBUG
  word test_word(apple);
  cout<<test_word.ShowWord()<<endl;
  cout<<test_word.ShowDescription()<<endl;
  cout<<test_word.getRank()<<endl;
  test_word.Wrong_Handler();
  cout<<test_word.getRank()<<endl;
  test_word.Right_Handler();
  cout<<test_word.getRank()<<endl;
  #endif

  #ifdef WORD_LIST_DEBUG
  wordlist test_word_list(test_list);
  cout<<"I am alive"<<endl;
  word new_banana(banana);
  word new_apple(apple);
  new_banana.Wrong_Handler();
  cout<<"Value is: "<<new_banana.getRank()<<endl;
  test_word_list.insert(new_banana);
  test_word_list.push_back(new_apple);

  for(int i=0;i<4;i++)
  cout<<"Fruit is: "<<test_word_list.pop_front().ShowWord()<<endl;
  #endif

}
#endif */
