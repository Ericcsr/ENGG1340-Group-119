#include "screenplay.h"
/*==================line_start============================*/
//Below are member function of Line Class
//Attention: Len must be larger than lengh of text
line::line(string text,int len,int format,string fill = " ")
{
  int length = text.length();
  Line = text;
  switch (format)
  {
    case RIGHT_JUST:
    {
      for(int i=0;i<(len-length);i++)
      {
        Line = fill + Line;
      }
      break;
    }
    case LEFT_JUST:
    {
      for(int i=0;i<(len-length);i++)
        Line = Line + fill; //
      break;
    }
    case MIDDLE_JUST:
    {
      int seperator = (len - length)/2;
      int remain = (len-length)-seperator;
      for(int i=0;i<seperator;i++)
      {
        Line = fill + Line;
      }
      for(int i=0;i<remain;i++)
      {
        Line = Line + fill;
      }
      break;
    }
    default:
      Line = "Wrong Format!";   //This is left for debugging purpose
  }
}

line::line(){}

ostream &operator<<(ostream &output,const line &L)
{
  output<<L.Line;  //Becarful Not to Auto Shift lines
  return output;
}

//Over loaded L for assignment

void line::operator = (const line &L)
{
  Line = L.Line;
}

/*==================line_end============================*/

/*===================Screen_start=======================*/
//Below are member Function of screen
//Screen is an object can print a block of Lines ;
//It can be used for multi-purpose
//Attention: Screen w will be raise up to interface level
//Make sure the Width is enough
screen::screen(int w,int h)
{
  width = w;
  height = h+2; //+2 means include outline of the block
  lines = new vector<line>(height);
}

screen::screen(){}

void screen::screeninit(int w,int h) //For ourside init
{
  width = w;
  height = h+2; //+2 means include outline of the block
  lines = new vector<line>(height);
}

void screen::setHead(string heading)
{
  line header(heading,width,MIDDLE_JUST,"="); //Use "=" to regulate the head
  line end("",width,MIDDLE_JUST,"=") ;//This function Will print out the
  (*lines)[0] = header;
  (*lines)[height-1] = end;
}

void screen::setLine(string line_content,int format)
{
  line current_line(line_content,width,format);
  (*lines)[line_index] = current_line;
  line_index++;
}

void screen::screenprint(void)
{
  for(int i = 0;i<height;i++)
  {
    cout<<(*lines)[i]<<endl;
  }
}

screen::~screen()
{
  delete lines;
  lines = NULL;
}
/*===================Screen_end=========================*/

/*====================menu_start========================*/
menu::menu(string heading,int choce_num,int wid)
{
  screeninit(wid,choce_num);
  setHead(heading);
  choice_num = choce_num;
}

void menu::setMenuChoices(string choice_list[])
{
  for(int i=0;i<choice_num;i++)
  {
    setLine(choice_list[i],MIDDLE_JUST);
  }
}

void menu::menuPrint()
{
  screenprint();
}

menu::~menu()
{
  delete lines;
  lines = NULL;
}
/*====================menu_end========================*/

/*=================Question_start=====================*/
//Attention: Qustion heading is not question;
//Question heading indicate the number of question or other information

question::question(string heading,int choce_num,int wid)
{
  screeninit(wid,choce_num+1);  // Since there need space for Question description
  setHead(heading);
  choice_num = choce_num;
}

void question::setQuestion(string que,string choice_list[])
{
  setLine(que,MIDDLE_JUST);
  string prefix[4]={"A. ","B. ","C. ","D. "};
  for(int i = 0;i<choice_num;i++)
  {
    setLine(prefix[i]+choice_list[i],LEFT_JUST);
  }
}

void question::questionPrint()
{
  screenprint();
}

question::~question()
{
  delete lines;
  lines = NULL;
}
/*===================Question_end=======================*/

/*===================Message_start======================*/
//Attention: since the length of message is undeterminated
//Assume the description Might Have multiplelines/
// Default using Middle-justify
message::message(string heading,string content,int wid)
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
    begin_index +=width;
  }
  setLine(content.substr(begin_index),LEFT_JUST);//Show the last line of the string
}

void message::MessagePrint()
{
  screenprint();
}

message::~message()
{
  delete lines;
  lines = NULL;
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
