#include "word.h"
//=====================Start_class_word========================
//Function: Init the Word
//Input: the raw vector
//Output: Nothing
Word::Word(vector<string> word_init)
{
    //wordcontent = new vector<string>;
    word_content_ = word_init;
}

//Function: Overload in case I want to create a word without initialization
Word::Word(){}
//Function this shows the content of word
//Input: Nothing
//Output: The content string of the word
string Word::ShowWord()
{
    return word_content_[0];
}
//Function: show the description of the word
//Input:Nothing
//Output: the description of the word (String)
string Word::ShowDescription()
{
    return word_content_[1];
}
//function: Show the explanation of the word
//Input: Nothing
//Output:The string explanation. 
string Word::ShowExplain()
{
  return word_content_[2];
}
//Function: show the rank of of the word
//Input:Nothing
//Output: The rank (int) of the word
int Word::getRank()
{
    return (int)(word_content_[3][0]-'0');
}
//Function:When dealing with insert 
//input: none
//output: a string containing all the scores of all the words
vector<string> Word::getWord_raw()
{
    return word_content_;
}

//function: change the score of the word when user answer a question right
//input: none
//output: set the score of this word to zero
void Word::Right_Handler()
{
    //(*wordcontent)[2][0]-=5;
    (word_content_)[3][0] = '0';
}

//function: change the score of the word when user answer a question wrong
//input: none
//output: the score of this word minus one
void Word::Wrong_Handler()
{

    word_content_[3][0]--;
}

Word::~Word()
{
    //delete wordcontent;
    //wordcontent = NULL;
}
//=====================End_Class_word============================

//=====================Start_Class_wordlist======================

//function: init the Wordlist object
//input: a 2D vector containing all the words and their information
//output: none
Wordlist::Wordlist(vector<vector<string>> new_list)
{
    //word_list = new vector<word>;
    int index=0;
    size_ = new_list.size();
    while(index<size_)
    {

        Word new_word(new_list[index]);
        //cout<<new_word.getRank()<<endl;
        word_list_.push_back(new_word);
        //cout<<<<end;

        //cout<<"I am alive"<<endl;
        //cout<<new_word.ShowDescription()<<endl;
        //cout<<"I am alive"<<endl;
        index++;

    }
    //cout<<"I am alive"<<endl;


}

//function: insert a word to Wordlist subject ascending order
//input: the Word(1D vector)
//output: none
int Wordlist::insert(Word new_word)
{
    for(int i = 0;i<size_;i++)
    {
        //cout<<new_word.getRank()<<" "<<word_list[i].getRank()<<endl;
        if(new_word.getRank()>word_list_[i].getRank())
        {
            word_list_.insert(word_list_.begin()+i,new_word);
            size_++;
            return i;
        }
    }
    word_list_.push_back(new_word);
    //cout<<"Fool"<<endl;
    size_++;
    return size_-1;
}

//function: push a word to the back of a Wordlist
void Wordlist::push_back(Word new_word)
{
    word_list_.push_back(new_word);
    size_++;
}

//function: popup the front Word in Wordlist and then delete it.
Word Wordlist::pop_front(void)
{
    if(size_>0)
    {
        Word result = word_list_[0];
        word_list_.erase(word_list_.begin(),word_list_.begin()+1);
        size_--;
        return result;
    }
    cout<<"No Word to Pop!"<<endl;
    exit(1);
}

//function: get the size of a Wordlist
//input: none
//output: a int indicating the size
int Wordlist::getSize()
{
  return size_;
}

//function: destructor
Wordlist::~Wordlist()
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
