#include "kernel.h"
//Open and read related files
//需要一个检查是不是第一次打开的函数。
kernel::kernel(int vocabulary_bag,string menu_name,bool new_old)
{
    switch (vocabulary_bag)
    {
        case 1:
            //sourcefile = "business.txt";
            sourcefile = "business.txt";//This line is for debugging
            break;
        case 2:
            sourcefile = "physics.txt";
            break;
        case 3:
            sourcefile = "sports.txt";
            break;
        default:
            cout<<"vocabulary bag out of range"<<endl;
    }
    new_word_file = menu_name+"new_word.txt";
    old_word_file = menu_name+"old_word.txt";
    if (!new_old) //1 is old 0 is new
    {
        filelist kernel_list(sourcefile,new_word_file); //Create read source file to new_word_buffer file
        ofstream cleanout;
        cleanout.open(old_word_file);
        cleanout.close();
    }
    new_filelist = new filelist(new_word_file,new_word_file);
    old_filelist = new filelist(old_word_file,old_word_file);
    new_wordlist = new wordlist (new_filelist->getRawdata()); //Set new word list to be all the fresh words
    old_wordlist = new wordlist (old_filelist->getRawdata()); //保持程序延续性
    source_filelist = new filelist(sourcefile,sourcefile); //This source file is for answer generation

}
//kernel is the core of each vocabulary revision thread
void kernel::kernel_run(void)
{
    string cmd ="default";
    string answers[4];
    srand(time(NULL));
     //generate random number to place the answer on on place in the array
    vector<string> wrongs;
    while(check_watermark())
    {
        char ans = (int)rand()%4+'A'; //Generate random number for ans
        word candidate = valve();
        //cout<<candidate.ShowWord()<<endl;
        wrongs = wrong_gen(candidate);
        int j = 0;
        //cout<<"I am Alive! "<<ans<<endl;
        answers[(int)(ans-'A')] = candidate.ShowDescription();
	//cout<<"The index of the ans: "<<(int)(ans-'A')<<endl;
        for(int i = 0;i<4;i++)
        {
            if(i!=(int)(ans-'A'))
	    {
                answers[i] = wrongs[++j];
            }

        }
	//cout<<answers[3]<<endl;
        question new_que("Question",4,WIDTH); //Creat a new question frame
        new_que.setQuestion("What is the meaning of "+candidate.ShowWord(),answers); //Set the choices
        new_que.questionPrint(); //show the question
        cout<<"Your Choice: ";
        cin>>cmd;
        cout<<'\n'<<endl;
        if(cmd == "#home")
        {
          candidate.Wrong_Handler();
          judge(candidate);
          return;
        }
        else if(cmd[0] == ans)
        {
            candidate.Right_Handler();
            message new_msg("Answer","You are Right!  ======> "+candidate.ShowExplain(),WIDTH);
            new_msg.MessagePrint();
        }
        else
        {
            candidate.Wrong_Handler();
            message new_msg("Answer","You are Wrong!  ======> "+candidate.ShowWord()+" "+candidate.ShowExplain(),WIDTH);
            new_msg.MessagePrint();
        }
        cout<<'\n'<<'\n'<<'\n'<<'\n'<<endl;
        judge(candidate); //Deal with where the candidate will end up be
    }
    message finish_msg("Congratulation!","You have finish all vocabulary learning in this set!",WIDTH);
    finish_msg.MessagePrint();
}
//This function determine which word to be pop up
word kernel::valve()
{
    static int counter = 0;
    counter++;
    //cout<<"The watermark is: "<<check_watermark()<<endl;
    switch (check_watermark())
    {
        case 1:
            if (counter%5==0)
                {
                old_filelist->remove(0);
                return old_wordlist->pop_front();
                }
            new_filelist->remove(0);
            return new_wordlist->pop_front();
        case 2:
            old_filelist->remove(0);
            return old_wordlist->pop_front();
        case 3:
            new_filelist->remove(0);
            return new_wordlist->pop_front();
    }
}

void kernel::judge(word candidate)
{
    int index;
    if(candidate.getRank() > 0)
	{
         index = old_wordlist->insert(candidate); //Insert the word to it proper position
         //cout<<"The current index is:"<<index<<endl;
         old_filelist->insert(candidate.getWord_raw(),index);
         cout<<"Old list item: "<<(*old_filelist).getSize()<<endl;
        } //Keep backupfile updated.
}


//Generate Wrong Answer vector
vector<string> kernel::wrong_gen(word candidate)
{
    vector<string> wrongs;
    vector<int> randint;
    srand(time(NULL));
    //cout<<"I am Alive!"<<endl;
    //cout<<candidate.ShowWord()<<endl;
    //cout<<"I am Alive!"<<endl;
    int target =source_filelist->search(candidate.getWord_raw());
    //cout<<"I am Alive!"<<endl;
    wrongs.push_back(" ");
    int buffer[4] = {target,0,0,0};
    for(int i=1;i<=3;i++)
    {
        for(int j=0;j<i;)
        {
          if(buffer[j]==buffer[i])
          {
            buffer[i] = rand()%(*source_filelist).getSize();
            j = 0;
          }
          else j++;
        }
        wrongs.push_back((*source_filelist)[buffer[i]][1]); //What???
        //cout<<"Current output :"<<(*source_filelist)[buffer[i]][1]<<endl;
    }
    //cout<<wrongs[1]+" "<<wrongs[2]+" "<<wrongs[3]+" "<<endl;
    return wrongs;
}

//This function can check real time condition of two lists.
int kernel::check_watermark()
{
    if(old_filelist->getSize()+new_filelist->getSize()==0)
        return 0;
    else if(new_filelist->getSize() == 0)
        return 2;
    else if(old_filelist->getSize() == 0)
        return 3;
    else
        return 1;
}
//May be buggy
kernel::~kernel()
{
    delete old_wordlist;
    old_wordlist = NULL;
    delete new_wordlist;
    new_wordlist = NULL;
    delete new_filelist;
    new_filelist = NULL;
    delete old_filelist;
    old_filelist = NULL;
    delete source_filelist;
    source_filelist = NULL;
}
//Below are code for debugging

//#define DEBUG
#ifdef DEBUG
int main()
{
  kernel test_kernel(1,"1",0);
  test_kernel.kernel_run();
}
#endif
//End of Kernel..
