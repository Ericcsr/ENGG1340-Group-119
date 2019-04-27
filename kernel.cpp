#include "kernel.h"
//Kernel is can be consider as a individual thread
//It can save data of and condition i run time as well as resume data
//If program once crashed
//Function: Initialize the kernel
//Input: bag choose parameter name of menu and new or old condition FLAG
//Output Nothing
Kernel::Kernel(int vocabulary_bag,string menu_name,bool new_old)
{
    switch (vocabulary_bag)
    {
        case 1:
            //sourcefile = "business.txt";
            sourcefile_ = "business.txt";//This line is for debugging
            break;
        case 2:
            sourcefile_ = "physics.txt";
            break;
        case 3:
            sourcefile_ = "sports.txt";
            break;
        default:
            cout<<"vocabulary bag out of range"<<endl;
    }
    new_word_file_ = menu_name+"new_word.txt";
    old_word_file_ = menu_name+"old_word.txt";
    if (!new_old) //1 is old 0 is new
    {
        Filelist kernel_list(sourcefile_,new_word_file_); //Create read source file to new_word_buffer file
        ofstream cleanout;
        cleanout.open(old_word_file_);
        cleanout.close();
    }
    new_filelist_ = new Filelist(new_word_file_,new_word_file_);
    old_filelist_ = new Filelist(old_word_file_,old_word_file_);
    new_wordlist_ = new Wordlist (new_filelist_->getRawdata()); //Set new word list to be all the fresh words
    old_wordlist_ = new Wordlist (old_filelist_->getRawdata()); //保持程序延续性
    source_filelist_ = new Filelist(sourcefile_,sourcefile_); //This source file is for answer generation

}
//Function : Run the kernel with graphical interface
//Input: Nothing
//Output: Nothing
void Kernel::kernel_run(void)
{
    string cmd ="default";
    string answers[4];
    srand(time(NULL));
     //generate random number to place the answer on on place in the array
    vector<string> wrongs;
    while(check_watermark())
    {
        char ans = (int)rand()%4+'A'; //Generate random number for ans
        Word candidate = valve();
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
        Question new_que("Question",4,WIDTH); //Creat a new question frame
        new_que.setQuestion("What is the meaning of "+candidate.ShowWord(),answers); //Set the choices
   FLAG:new_que.questionPrint(); //show the question
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
            Message new_msg("Answer","You are Right!  Explanation: "+candidate.ShowExplain(),WIDTH);
            new_msg.MessagePrint();
        }
        else if(cmd.length()==1 && cmd[0]-'A'>=0&& cmd[0]-'A'<4)
        {
            candidate.Wrong_Handler();
            Message new_msg("Answer","You are Wrong!  Explanation: "+candidate.ShowExplain(),WIDTH);
            new_msg.MessagePrint();
        }
        else
        {
            Message new_msg("Notice","Please type in valid answer!",WIDTH);
            new_msg.MessagePrint();
            cout<<'\n'<<'\n'<<'\n'<<'\n'<<endl;
            goto FLAG;
        }
        cout<<'\n'<<'\n'<<'\n'<<'\n'<<endl;
        judge(candidate); //Deal with where the candidate will end up be
    }
    Message finish_msg("Congratulation!","You have finish all vocabulary learning in this set!",WIDTH);
    finish_msg.MessagePrint();
}
//This function determine which word to be pop up every 5 new word an old word
//Input: Nothing
//Output the word object to pop up
Word Kernel::valve()
{
    static int counter = 0;
    counter++;
    //cout<<"The watermark is: "<<check_watermark()<<endl;
    switch (check_watermark())
    {
        case 1:
            if (counter%5==0)
                {
                old_filelist_->remove(0);
                return old_wordlist_->pop_front();
                }
            new_filelist_->remove(0);
            return new_wordlist_->pop_front();
        case 2:
            old_filelist_->remove(0);
            return old_wordlist_->pop_front();
        case 3:
            new_filelist_->remove(0);
            return new_wordlist_->pop_front();
    }
}
//Function: This Function determines the direction of the candidate by checking index
//Input: The candidate to check
//Output: Nothing
void Kernel::judge(Word candidate)
{
    int index;
    if(candidate.getRank() > 0)
	{
         index = old_wordlist_->insert(candidate); //Insert the word to it proper position
         //cout<<"The current index is:"<<index<<endl;
         old_filelist_->insert(candidate.getWord_raw(),index);
         //cout<<"Old list item: "<<(*old_filelist).getSize()<<endl;
        } //Keep backupfile updated.
}


//Generate Wrong Answer vector
//Output: a 3 member string vector saving wrong answers
//Input: The right candidate
vector<string> Kernel::wrong_gen(Word candidate)
{
    vector<string> wrongs;
    vector<int> randint;
    srand(time(NULL));
    //cout<<"I am Alive!"<<endl;
    //cout<<candidate.ShowWord()<<endl;
    //cout<<"I am Alive!"<<endl;
    int target =source_filelist_->search(candidate.getWord_raw());
    //cout<<"I am Alive!"<<endl;
    wrongs.push_back(" ");
    int buffer[4] = {target,0,0,0};
    for(int i=1;i<=3;i++)
    {
        for(int j=0;j<i;)
        {
          if(buffer[j]==buffer[i])
          {
            buffer[i] = rand()%(*source_filelist_).getSize();
            j = 0;
          }
          else j++;
        }
        wrongs.push_back((*source_filelist_)[buffer[i]][1]); //What???
        //cout<<"Current output :"<<(*source_filelist)[buffer[i]][1]<<endl;
    }
    //cout<<wrongs[1]+" "<<wrongs[2]+" "<<wrongs[3]+" "<<endl;
    return wrongs;
}

//This function can check real time condition of two lists.
//INput: nothing
//Output: A int indicate the condition of two word list set
int Kernel::check_watermark()
{
    if(old_filelist_->getSize()+new_filelist_->getSize()==0)
        return 0;
    else if(new_filelist_->getSize() == 0)
        return 2;
    else if(old_filelist_->getSize() == 0)
        return 3;
    else
        return 1;
}
//Destroy the Kernel objet and free the memory when avaliable
//Input==Output: Nothing
Kernel::~Kernel()
{
    delete old_wordlist_;
    old_wordlist_ = NULL;
    delete new_wordlist_;
    new_wordlist_ = NULL;
    delete new_filelist_;
    new_filelist_ = NULL;
    delete old_filelist_;
    old_filelist_ = NULL;
    delete source_filelist_;
    source_filelist_ = NULL;
}
//Below are code for debugging

//#define DEBUG
#ifdef DEBUG
int main()
{
  Kernel test_kernel(1,"1",0);
  test_kernel.kernel_run();
}
#endif
//End of Kernel..
