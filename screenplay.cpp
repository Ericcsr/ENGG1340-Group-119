#include "screenplay.h"
/*==================line_start============================*/
//Below are member function of Line Class
//Attention: Len must be larger than lengh of text
line::line(string text,int len,int format,char fill = ' ')
{
  int length = text.length();
  switch format
  {
    case RIGHT_JUST:
      Line = fill*(len-length)+text;
      break;
    case LEFT_JUST:
      Line = text + fill*(len - length);
      break;
    case MIDDLE_JUST:
      int seperator = (len - length)/2;
      int remain = (len-length)-seperator;
      Line = seperator*fill+text+remain*fill;
      break;
    default:
      Line = "Wrong Format!";   //This is left for debugging purpose
  }
}

ostream line::&operator<<(&ostream output)
{
  output<<Line;  //Becarful Not to Auto Shift lines
  return output;
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
  lines = new line [height];
}

void screen::screeninit(int w,int h) //For ourside init
{
  width = w;
  height = h+2; //+2 means include outline of the block
  lines = new line [height];
}

void screen::setHead(string heading)
{
  line header(heading,width,MIDDLE_JUST,'='); //Use "=" to regulate the head
  line end("",w,MIDDLE_JUST,'=')
  lines[0] = header;
  lines[height - 1] = end;
}

void screen::setLine(string line_content,int format)
{
  line current_line(line_content,width,format);
  lines[index] = current_line;
  line_index++;
}

void screen::screenprint(void)
{
  for(int i = 0;i<height<i++)
  {
    cout<<lines[i]<<endl;
  }
}

screen::~screen()
{
  delete lines;
}
/*===================Screen_end=========================*/

/*====================menu_start========================*/
menu::menu(string heading,int choice_num,int wid)
{
  screeninit(wid,choice_num);
  setHead(heading);
}

void setMenuChoices(string choice_list[])
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
/*====================menu_end========================*/

/*=================Question_start=====================*/
//Attention: Qustion heading is not question;
//Question heading indicate the number of question or other information

question::question(string heading,int choice_num,int wid)
{
  screeninit(wid,choice_num+1);  // Since there need space for Question description
  setHead(heading);
}

void question::setQuestion(string que,string choice_list[])
{
  setLine(que,MIDDLE_JUST);
  for(int i = 0;i<choice_num;i++)
  {
    setLine(choice_list[i],LEFT_JUST);
  }
}

void question::questionPrint()
{
  screenprint();
}

question::~question()
{
  delete lines;
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
  for(int i = 0;i<line_num;i++)
  {
    setLine(content.substr(begin_index,wid),LEFT_JUST);
    begin_index +=width;
  }
}

void MessagePrint()
{
  screenprint();
}
/*===================Message_End=======================*/
