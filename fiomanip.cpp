#include "fiomanip.h"
//=================class_<file_list>_start==================
void filelist::readFile(string infile)
{
    buffer_list = new vector<vector<string>>;
    ifstream fin;
    string str_buffer;
    fin.open(infile);
    if(fin.fail())
        file_error_handler(infile);
    while(getline(fin,str_buffer))
    {
        vector<string> buffer_vect;
        for(long long int cursor = str_buffer.find('@');cursor!=string::npos;cursor = str_buffer.find('@'))
        {
            buffer_vect.push_back(str_buffer.substr(0,cursor));
            str_buffer.erase(0,cursor+1);
        }
        buffer_list->push_back(buffer_vect);
        size++;
    }
    list_itr = buffer_list->begin();
    fin.close();
}

void filelist::writeFile(string outfile)//,vector<vector<string>> buf_list)
{
    ofstream fout;
    string str_2_write;
    fout.open(outfile);
    if(fout.fail())
        file_error_handler(outfile);
    for(int i=0;i<size;i++)
    {
        str_2_write = FormatHandler((*buffer_list)[i]);
        fout<<str_2_write<<endl;
    }
    fout.close();
}

string filelist::FormatHandler(vector<string> target)
{
    vector<string>::iterator itr = target.begin();
    string str_result;
    while((itr)!=target.end())
    {
        str_result+=(*itr)+'@';
        itr++;
    }
    return str_result;
}

filelist::filelist(string infile,string outfile)
{
    readFile(infile);
    writeFile(outfile);//*buffer_list); //
    ofile =  outfile;
    ifile = infile;
}

int filelist::getSize(void)
{
    return size;
}

//This function return the last item of the 2-D vector
//As well as destory it
vector<string> filelist::pop_end(void)
{
    if(size>0)
        size--;
    else
    {
        cout<<"No Vector to be pop End"<<endl;
        exit(1);
    }
    vector<string> result = (*buffer_list)[size];
    buffer_list->pop_back();
    writeFile(ofile);
    return result;
}

//This function return the first item of the 2-D vector
//As well as destory it
vector<string> filelist::pop_front(void)
{
    if(size>0)
        size--;
    else
    {
        cout<<"No vector to be pop Front"<<endl;
        exit(1);
    }
    vector<string> result = (*buffer_list)[0];
    buffer_list->erase(buffer_list->begin(),buffer_list->begin()+1); //Delete the element and automatically free memo
    writeFile(ofile);
    list_itr = buffer_list->begin();
    return result;
}
//This function add a new object at the very beginning
//and increase the size of the vector
void filelist::push_head(vector<string> new_item)
{
    size++;
    buffer_list->insert(buffer_list->begin(),new_item);
    writeFile(ofile);
    list_itr = buffer_list->begin();
}

void filelist::append(vector<string> new_item)
{
    buffer_list->push_back(new_item);
    size++;
    writeFile(ofile);
}
//This function can remove a item of given index inside the file list
void filelist::remove(int index)
{
    if(index>=size)
    {
        cout<<"Index out of range"<<endl;
        exit(1);
    }
    buffer_list->erase(buffer_list->begin()+index,buffer_list->begin()+index+1);
    size--;
    list_itr = buffer_list->begin();
    writeFile(ofile);
}
//This function can search for given vector and return its index;
int filelist::search(vector<string> target)
{
    int index = 0;
    while(list_itr!=buffer_list->end())
    {
        if((*list_itr)[0]==target[0]) //Only compare first value
        {
            list_itr = buffer_list->begin();// Update the position of the iterator
            return index;
        }
        list_itr++;
        index++;
    }
    return -1; //This is default No fund value
}
//This function can insert a target to the function
void filelist::insert(vector<string> new_item,int index)
{
    if(index>=size)
    {
        cout<<"Index out of range"<<endl;
        exit(1);
    }
    buffer_list->insert(buffer_list->begin()+index,new_item);
    list_itr = buffer_list->begin();
    size++;
    writeFile(ofile);
}
//This [] operator reload allow user to access vector members as usual
//Warning Potential bug may exist
vector<string> &filelist::operator[](int i)
{
    return (*buffer_list)[i];
}
//This might be only valid function it might use
//Return a decoded 2-d vector
vector<vector<string>> filelist::getRawdata()
{
    return *buffer_list;
}

void filelist::setRawdata(vector<vector<string>> updated_list)
{
    *buffer_list = updated_list; //Warning No reference
    writeFile(ofile);
}

//This function can be used to update, re-read ifile to outfile
void filelist::refresh()
{
    readFile(ifile);
    writeFile(ofile);
}

//This is defination of destructor
//Only when this object is created as a dynamic object can this be deleted
filelist::~filelist()
{
    delete buffer_list;
    buffer_list = NULL; //Avoid dangling pointer
}




//=====================Class_filelist_end================================

//=======================Independent functions==========================

void file_error_handler(string name)
{
    cout<<"File Name: "<<name<<"Could not Open!"<<endl;
    exit(1);
}


//Using another file to record the condition of current files
//It can change file condition sent to it as well as check the existance of the file
int check_file(int file_condition[])
{
    ifstream testin;
    testin.open("check.txt");
    int buffer;
    if(testin.fail())
    {
        cout<<"Cannot open check file!"<<endl;
        return 0;
    }
    while(testin>>buffer)
    {
        file_condition[buffer-1] = 1; //value can be over written many times
    }
    testin.close();
    return 1;
}

void reset_check_file(int index,int file_condition[]) // 3 reoresent all files
{
    ofstream testout;
    testout.open("check.txt");//By default
    switch (index)
    {
        case 0:
            if(file_condition[1]==1) testout<<1<<endl; //Reset the second word list
            if(file_condition[2]==1) testout<<2<<endl; //Reset the third word list
            file_condition[0] = 0;
            break;
        case 1:
            if(file_condition[0]==1) testout<<0<<endl; //Reset the second word list
            if(file_condition[2]==1) testout<<2<<endl; //Reset the third word list
            file_condition[1] = 0;
            break;
        case 2:
            if(file_condition[1]==1) testout<<1<<endl; //Reset the second word list
            if(file_condition[0]==1) testout<<0<<endl; //Reset the third word list
            file_condition[2] = 0;
            break;
        case 3:
            file_condition[0] = 0;
            file_condition[1] = 0;
            file_condition[2] = 0;
            break;
    }
    testout.close();
}

//Below are code for debug use
#define DEBUG
#ifdef DEBUG
//#define FILE_LIST_DEBUG
//#define INDIVIDUAL_DEBUG
#define FILE_LIST_DEBUG
int main()
{
  #ifdef FILE_LIST_DEBUG

  filelist test_list("debug.txt","debug_1.txt");
  vector<string> test_buffer;
  test_buffer = test_list[2];
  //test_list.insert(test_buffer,1);
  test_list.insert(test_buffer,0);
  //test_list.refresh();
  cout<<test_list[0][0]+"   "+test_list[0][1]+"   "+test_list[0][2]<<endl;
  test_list.push_head(test_buffer);
  test_list.append(test_buffer);
  cout<<test_list.getSize()<<endl;
  #endif

  #ifdef INDIVIDUAL_DEBUG
  check_file(file_condition);
  string t;
  cin>>t;
  reset_check_file(0,file_condition);
  #endif
}
#endif
