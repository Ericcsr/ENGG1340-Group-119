#ifndef __SCREENPLAY_H__
#define __SCREENPLAY_H__

#define WIDTH 80 // minimun is 80!
const int RIGHT_JUST = 0;
const int LEFT_JUST  = 1;
const int MIDDLE_JUST= 2;

#include <iostream>
#include <ostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;
//Superset: Screen class

//ostream operator<<(&ostream output,const line &L);
class Line
{
public:
  Line(string text,int len,int format,string fill);
  Line();
  void operator = (const Line &L);
  friend ostream &operator<<(ostream &output,const Line &L);  //Define the output stream
  //Since this has nothing to do with dynamic no need for destructor
private:
  string Line_;
};

class Screen
{
public:
  Screen(int w,int h);                                    //Initialize the screen object
  Screen();
  void screeninit(int w,int h);                           //If this is a father class
  void setHead(string heading);                           //Set the heading of the string
  void setLine(string line_content,int format);  //Set line index
  void screenprint(void);                                 //Print out content of the screen
  ~Screen();
protected:
  int width_;
  int height_;
  int line_index_ = 1;
  vector<Line> *lines_;                                      //Dynamic Line object pointer
  string head_;
};

class Menu: private Screen                                //Subclass menu set parameter and content
{
public:
  Menu(string heading,int choice_num,int wid);
  void setMenuChoices(string choice_list[]);
  void menuPrint(void);
  ~Menu();
private:
  int choice_num_;
};

class Question: private Screen                            //Subclass Question set parameter and content
{
public:
  Question(string heading,int choice_num,int wid);
  void setQuestion(string que,string choice_list[]);
  void questionPrint(void);
  ~Question();
private:
  int choice_num_;
};

class Message: private Screen                             //Subclass Message set Parameter and content
{
public:
  Message(string heading,string content,int wid);
  void MessagePrint(void);
  ~Message();
};

#endif
