#ifndef __SCREENPLAY_H__
#define __SCREENPLAY_H__

#define WIDTH 50
#include <iostream>
#include <ostream>
#include <string>
#include <iomanip>
#include <vector>

const int RIGHT_JUST = 0;
const int LEFT_JUST  = 1;
const int MIDDLE_JUST= 2;

using namespace std;
//Superset: Screen class

//ostream operator<<(&ostream output,const line &L);
class line
{
public:
  line(string text,int len,int format,string fill);
  line();
  void operator = (const line &L);
  friend ostream &operator<<(ostream &output,const line &L);  //Define the output stream
private:
  string Line; //Since this has nothing to do with dynamic no need for destructor
};

class screen
{
public:
  screen(int w,int h);                                    //Initialize the screen object
  screen();
  void screeninit(int w,int h);                           //If this is a father class
  void setHead(string heading);                           //Set the heading of the string
  void setLine(string line_content,int format);  //Set line index
  void screenprint(void);                                 //Print out content of the screen
  ~screen();
protected:
  int width;
  int height;
  int line_index = 1;
  vector<line> *lines;                                      //Dynamic Line object pointer
  string head;
};

class menu: private screen                                //Subclass menu set parameter and content
{
public:
  menu(string heading,int choice_num,int wid);
  void setMenuChoices(string choice_list[]);
  void menuPrint(void);
  ~menu();
private:
  int choice_num;
};

class question: private screen                            //Subclass Question set parameter and content
{
public:
  question(string heading,int choice_num,int wid);
  void setQuestion(string que,string choice_list[]);
  void questionPrint(void);
  ~question();
private:
  int choice_num;
};

class message: private screen                             //Subclass Message set Parameter and content
{
public:
  message(string heading,string content,int wid);
  void MessagePrint(void);
  ~message();
};

#endif
