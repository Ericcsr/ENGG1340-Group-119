#include "kernel.h"
//Open and read related files
//需要一个检查是不是第一次打开的函数。
kernel::kernel(int vocabulary_bag,string menu_name,int new_old)
{
    switch vocabulary_bag
    {
        case 1:
            sourcefile = "business.txt";
            break;
        case 2:
            sourcefile = "physices.txt";
            break;
        case 3:
            sourcefile = "computerscience.txt";
            break;
        default:
            cout<<"vocabulary bag out of range"<<endl;
    }
    new_word_file = menu_name+"new_word.txt";
    old_word_file = menu_name+"old_word.txt";
    if (!new_old) //1 is old 0 is new
        filelist kernel_list(sourcefile,new_word_file); //Create read source file to new_word_buffer file
    new_filelist = new filelist(new_word_file,new_word_file);
    old_filelist = new filelist(old_word_file,old_word_file);
    new_wordlist = new wordlist (new_words->getRawdata()); //Set new word list to be all the fresh words
    old_wordlist = new wordlist (old_words->getRawdata()); //保持程序延续性
    source_filelist = new wordlist (sourcefile,sourcefile); //This source file is for answer generation
}
//kernel is the core of each vocabulary revision thread
kernel::kernel_run(void)
{
    string cmd ="default";
    string answers[4];
    srand(time);
    char ans = (int)rand()%4+'A'; //generate random number to place the answer on on place in the array
    vector<string>::iterator wrongs;
    while(check_watermark())
    {
        word candidate = valve();
        wrongs = wrong_gen().begin();
        answers[ans] = candidate.ShowDescription();
        for(int i = 0;i<4;i++)
        {
            if(i!=(int)ans)
                answers[i] = *(wrongs++);
        }
        question new_que("Question",4,WIDTH); //Creat a new question frame
        new_que.setQuestion(answers); //Set the choices
        new_que.questionPrint(); //show the question
        cout<<"Your Choice: ";
        cin>>cmd;
        if(cmd = "#home")
            break;
        else if(cmd[1] = ans)
        {
            candidate.Right_Handler();
            message new_msg("Answer","You are Right!",WIDTH);
            new_msg.MessagePrint();
        }
        else
        {
            candidate.Wrong_Handler();
            message new_msg("Answer","You are Wrong!"+candidate.ShowWord()+" "+candidate.ShowDescription(),WIDTH);
            new_msg.MessagePrint();
        }
        judge(candidate); //Deal with where the candidate will end up be
    }
}
//This function determine which word to be pop up
word kernel::valve()
{
    static int counter = 0;
    counter++;
    switch check_watermark()
    {
        case 1:
            if counter%5
                {
                new_filelist->remove(0);
                return old_wordlist->pop_front();
                }
            old_filelist->remove(0);
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
        index = old_wordlist->insert(candidate); //Insert the word to it proper position
    old_filelist->insert(candidate.getWord_raw(),index); //Keep backupfile updated.
}


//Generate Wrong Answer vector
vector<string> kernel::wrong_gen(word candidate)
{
    vector<string> wrongs;
    vector<int> randint;
    srand(time);
    int target = *source_filelist.search(candidate.ShowDescription())
    for(int buffer,i=0,buffer1=0;i<3;)
    {
        buffer = rand()%(*source_filelist).size();
        if(buffer!=target && buffer1!=buffer)
        {
            wrongs.push_back(*source_filelist[buffer][i])
            buffer1 = buffer;
            i++;
        }
    }
}

//This function can check real time condition of two lists.
int kernel::check_watermark()
{
    if(old_filelist->size()+new_filelist.size()==0)
        return 0;
    else if(new_filelist->size() = 0)
        return 2;
    else if(old_filelist->size() = 0)
        return 3;
    else 
        return 1;
}

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

//End of Kernel..