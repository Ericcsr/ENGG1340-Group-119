#include "fiomanip.h"
//=================class_<file_list>_start==================
//Functionality: Read data from a file and save them inside a 2-D array
//Input: Name of the input file
//Output: Change the content of buffer file
void Filelist::readFile(string infile)
{
    buffer_list_ = new vector<vector<string>>;
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
        buffer_list_->push_back(buffer_vect);
        size_++;
    }
    list_itr_ = buffer_list_->begin();
    fin.close();
}
//Functionality: Write content of 2-D runtime array into a file with same input
//Input: name of out put file
//Output: Nothing
void Filelist::writeFile(string outfile)//,vector<vector<string>> buf_list)
{
    ofstream fout;
    string str_2_write;
    fout.open(outfile);
    if(fout.fail())
        file_error_handler(outfile);
    for(int i=0;i<size_;i++)
    {
        str_2_write = FormatHandler((*buffer_list_)[i]);
        fout<<str_2_write<<endl;
    }
    fout.close();
}
//Functionality: change the content inside the string vector into a string that has comprehansive
//seperator to be read
//Input: A string vector
//Output: A string whose element is seperated by @

string Filelist::FormatHandler(vector<string> target)
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
//Functionality: Constructor of filelist class take in name of input and output file
//Input :name of the input and output file
//Output: Nothing change the private name of input output file
Filelist::Filelist(string infile,string outfile)
{
    readFile(infile);
    writeFile(outfile);//*buffer_list); //
    ofile_ =  outfile;
    ifile_ = infile;
}
//Functionality: Get the size of the filelist for multiple use
//Input: Nothing
//Output: The size of the filelist
int Filelist::getSize(void)
{
    return size_;
}

//Functionality: Consider file as a list, this function can pop the first vector in the list
//as well as reduce the length of this list by one
//Input: Nothing
//Output: The vector of string to be poped
vector<string> Filelist::pop_end(void)
{
    if(size_>0)
        size_--;
    else
    {
        cout<<"No Vector to be pop End"<<endl;
        exit(1);
    }
    vector<string> result = (*buffer_list_)[size_];
    buffer_list_->pop_back();
    writeFile(ofile_);
    return result;
}
//Functionality: Delete the last element as well as return it
//Input: Nothing
//Output: The first element of the filelist
vector<string> Filelist::pop_front(void)
{
    if(size_>0)
        size_--;
    else
    {
        cout<<"No vector to be pop Front"<<endl;
        exit(1);
    }
    vector<string> result = (*buffer_list_)[0];
    buffer_list_->erase(buffer_list_->begin(),buffer_list_->begin()+1); //Delete the element and automatically free memo
    writeFile(ofile_);
    list_itr_ = buffer_list_->begin();
    return result;
}
//Functionality: This function put the newly add item as the first item of the filelist
//Input: The new string vector to be put as the head
//Output: Nothing increase the size of the list
void Filelist::push_head(vector<string> new_item)
{
    size_++;
    buffer_list_->insert(buffer_list_->begin(),new_item);
    writeFile(ofile_);
    list_itr_ = buffer_list_->begin();
}
//Functionality: This function add a new item at the end of filelist
//Input: The item to be add to the end
//Output: Nothing
void Filelist::append(vector<string> new_item)
{
    buffer_list_->push_back(new_item);
    size_++;
    writeFile(ofile_);
}
//Functionality: Remove an item with given index
//Input: the index of the item
//Output: Nothing
void Filelist::remove(int index)
{
    if(index>=size_)
    {
        cout<<"Index out of range"<<endl;
        exit(1);
    }
    buffer_list_->erase(buffer_list_->begin()+index,buffer_list_->begin()+index+1);
    size_--;
    list_itr_ = buffer_list_->begin();
    writeFile(ofile_);
}
//Functionality: This function can search for given vector and return its index
//Input: The target vector of string
//Output the index of the string
int Filelist::search(vector<string> target)
{
    int index = 0;
    while(list_itr_!=buffer_list_->end())
    {
        if((*list_itr_)[0]==target[0]) //Only compare first value
        {
            list_itr_ = buffer_list_->begin();// Update the position of the iterator
            return index;
        }
        list_itr_++;
        index++;
    }
    return -1; //This is default No fund value
}
//Functionality: This function can insert a target to the function given index
//Input: The index
//Output: Nothing
void Filelist::insert(vector<string> new_item,int index)
{
    if(index>size_)
    {
        cout<<"Index out of range"<<endl;
        exit(1);
    }
    buffer_list_->insert(buffer_list_->begin()+index,new_item);
    list_itr_ = buffer_list_->begin();
    size_++;
    writeFile(ofile_);
}
//Functionality: Overload the operator[] for filelist to make the list more like a list
//Input: The index
//Output: The item indicated by given index
vector<string> &Filelist::operator[](int i)
{
    return (*buffer_list_)[i];
}
//Functionality: get the raw data to init the wordlist
//Input:  Nothing
//Output: Return a decoded 2-d vector
vector<vector<string>> Filelist::getRawdata()
{
    return *buffer_list_;
}

//Functionality: give a 2-D array and init the filelost with given list 
//Input: The new 2-D vector to be init
//Output: Nothing
void Filelist::setRawdata(vector<vector<string>> updated_list)
{
    *buffer_list_ = updated_list; //Warning No reference
    writeFile(ofile_);
}

//Function: This function can be used to update, re-read ifile to outfile.
//Input==Output: Nothing
void Filelist::refresh()
{
    readFile(ifile_);
    writeFile(ofile_);
}

//This is defination of destructor
//Only when this object is created as a dynamic object can this be deleted
Filelist::~Filelist()
{
    delete buffer_list_;
    buffer_list_ = NULL; //Avoid dangling pointer
}




//=====================Class_filelist_end================================

//=======================Independent functions==========================
//Functionality: Report the file open error
//Input: The name of the error file
//Output: Exit the program
void file_error_handler(string name)
{
    cout<<"File Name: "<<name<<" Could not Open!"<<endl;
    exit(1);
}


//Functionality: read the check file to check open condition of the each file
//It can be used to tell which fill can be resumed after shut down
//Input: An array indicate the runtime condition
//Output: The check result
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
        file_condition[buffer] = 1; //value can be over written many times
    }
    testin.close();
    return 1;
}
//Functionality: Reset and map the change to the checkfile
//Input: index of command , file condition array
//Output:Nothing
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
        case 3://Clean all record
            file_condition[0] = 0;
            file_condition[1] = 0;
            file_condition[2] = 0;
            break;
	default://Refresh all check file according to current file_condition
	    if(file_condition[0]==1) testout<<0<<endl;
	    if(file_condition[1]==1) testout<<1<<endl;
	    if(file_condition[2]==1) testout<<2<<endl;
    }
    testout.close();
}

//Below are code for debug use
//#define DEBUG
//#ifdef DEBUG
//#define FILE_LIST_DEBUG
//#define INDIVIDUAL_DEBUG
/*
int main()
{
  //#ifdef FILE_LIST_DEBUG

  filelist test_list("debug.txt","debug.txt");
  vector<string> test_buffer;
  test_buffer = test_list[2];
  //test_list.insert(test_buffer,1);
  test_list.insert(test_buffer,1);
  cout<<test_buffer[0]+" "+test_buffer[1]+" "+test_buffer[2]<<endl;
  //#endif

  //#ifdef INDIVIDUAL_DEBUG
  check_file(file_condition);
  string t;
  cin>>t;
  reset_check_file(0,file_condition);
  //#endif
}*/
//#endif
