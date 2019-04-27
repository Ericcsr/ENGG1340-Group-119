#include "screenplay.h"
/*==================line_start============================*/
//Below are member function of Line Class
//Attention: Len must be larger than lengh of text

//function: it's the constructor of Line
//input: text is the text you want to show, len is the length of the screen, format has three options
//output: show things on the screen therefore no output
Line::Line(string text,int len,int format,string fill = " ")
{
  int length = text.length();
  Line_ = text;
  switch (format)
  {
    case RIGHT_JUST:
    {
      for(int i=0;i<(len-length);i++)
      {
        Line_ = fill + Line_;
      }
      break;
    }
    case LEFT_JUST:
    {
      for(int i=0;i<(len-length);i++)
        Line_ = Line_ + fill; //
      break;
    }
    case MIDDLE_JUST:
    {
      int seperator = (len - length)/2;
      int remain = (len-length)-seperator;
      for(int i=0;i<seperator;i++)
      {
        Line_ = fill + Line_;
      }
      for(int i=0;i<remain;i++)
      {
        Line_ = Line_ + fill;
      }
      break;
    }
    default:
      Line_ = "Wrong Format!";   //This is left for debugging purpose
  }
}

//function: When init a dymamic vector of this class,
//vector can be successfully init without parameter
Line::Line(){}

//function: to simplify the print procedure
//operator overload
ostream &operator<<(ostream &output,const Line &L)
{
  output<<L.Line_;  //Becarful Not to Auto Shift lines
  return output;
}

//Over loaded L for assignment
void Line::operator = (const Line &L)
{
  Line_ = L.Line_;
}

/*==================line_end============================*/

/*===================Screen_start=======================*/
//Below are member Function of screen
//Screen is an object can print a block of Lines ;
//It can be used for multi-purpose
//Attention: Screen w will be raise up to interface level
//Make sure the Width is enough

//Constructor of Screen
//input: the width and height of the screen
Screen::Screen(int w,int h)
{
  width_ = w;
  height_ = h+2; //+2 means include outline of the block
  lines_ = new vector<Line>(height_);
}

Screen::Screen(){}

//function: init a screen object with a width of w and height of h
//input: the width and height of the screen
void Screen::screeninit(int w,int h) //For ourside init
{
  width_ = w;
  height_ = h+2; //+2 means include outline of the block
  lines_ = new vector<Line>(height_);
}

//function: set the heading of this screen
//input: string heading
void Screen::setHead(string heading)
{
  Line header(heading,width_,MIDDLE_JUST,"="); //Use "=" to regulate the head
  Line end("",width_,MIDDLE_JUST,"=") ;//This function Will print out the
  (*lines_)[0] = header;
  (*lines_)[height_-1] = end;
}

//function: set each line of the screen display
//input: string line_content, format has three options
void Screen::setLine(string line_content,int format)
{
  Line current_line(line_content,width_,format);
  (*lines_)[line_index_] = current_line;
  line_index_++;
}

//function: print out this screen object as a whole
//an sample will be like this:
/*
===============heading==================
line
line
line
========================================
*/
void Screen::screenprint(void)
{
  for(int i = 0;i<height_;i++)
  {
    cout<<(*lines_)[i]<<endl;
  }
}

//destructor
Screen::~Screen()
{
  delete lines_;
  lines_ = NULL;
}
/*===================Screen_end=========================*/

/*====================menu_start========================*/
//constructor
Menu::Menu(string heading,int chose_num,int wid)
{
  screeninit(wid,chose_num);
  setHead(heading);
  choice_num_ = chose_num;
}

//Because the inheritance from screen functions below are similar
void Menu::setMenuChoices(string choice_list[])
{
  for(int i=0;i<choice_num_;i++)
  {
    setLine(choice_list[i],MIDDLE_JUST);
  }
}

void Menu::menuPrint()
{
  screenprint();
}

Menu::~Menu()
{
  delete lines_;
  lines_ = NULL;
}
/*====================menu_end========================*/

/*=================Question_start=====================*/
//Attention: Qustion heading is not question;
//Question heading indicate the number of question or other information

Question::Question(string heading,int chose_num,int wid)
{
  screeninit(wid,chose_num+1);  // Since there need space for Question description
  setHead(heading);
  choice_num_ = chose_num;
}

//Because the inheritance from screen functions below are similar
void Question::setQuestion(string que,string choice_list[])
{
  setLine(que,MIDDLE_JUST);
  string prefix[4]={"A. ","B. ","C. ","D. "};
  for(int i = 0;i<choice_num_;i++)
  {
    setLine(prefix[i]+choice_list[i],LEFT_JUST);
  }
}

void Question::questionPrint()
{
  screenprint();
}

Question::~Question()
{
  delete lines_;
  lines_ = NULL;
}
/*===================Question_end=======================*/

/*===================Message_start======================*/
//Attention: since the length of message is undeterminated
//Assume the description Might Have multiplelines/
// Default using Middle-justify

//constructor of Message, init a Message object
//input: the heading the content and the width of the message
Message::Message(string heading,string content,int wid)
{
  int length = content.length();
  int line_num = 0;
  int begin_index = 0;
  (length%wid)?(line_num = length/wid+1):(line_num = length/wid);
  screeninit(wid,line_num);
  setHead(heading);
  for(int i = 0;i<line_num-1;i++)
  {
    setLine(content.substr(begin_index,wid),LEFT_JUST);
    begin_index +=width_;
  }
  setLine(content.substr(begin_index),LEFT_JUST);//Show the last line of the string
}

//print the Message object out
void Message::MessagePrint()
{
  screenprint();
}

Message::~Message()
{
  delete lines_;
  lines_ = NULL;
}
/*===================Message_End=======================*/
/*
// below are main for debug
#define DEBUG
#define SCREEN_DEBUG
#define MENU_DEBUG
#define QUESTION_DEBUG
#define MESSAGE_DEBUG
#ifdef DEBUG
int main()
{
  #ifdef SCREEN_DEBUG
  screen test_screen(50,5);
  test_screen.setHead("Test");
  for(int i=0;i<5;i++)
  {
    test_screen.setLine("This is new test",MIDDLE_JUST);
  }
 test_screen.screenprint();
  #endif

  #ifdef MENU_DEBUG
  menu test_menu("Main Menu",4,50);
  string list[] = {"This is new","This is new","This is new","This is new"};
  test_menu.setMenuChoices(list);
  test_menu.menuPrint();
  #endif

  #ifdef QUESTION_DEBUG
  if(1)
  {
  question test_question("Question 1",4,50);
  //string list[] = {"This is new","This is new","This is new","This is new"};
  test_question.setQuestion("What is debugging",list);
  test_question.questionPrint();
  }
  #endif

  #ifdef MESSAGE_DEBUG
  string msg ="There is a man names bruce and an apple named jobs they are best friend forever!!!";
  message test_message("Message 1",msg,50);
  test_message.MessagePrint();
  #endif
  cout<<"I am Alive"<<endl;
}
#endif */
