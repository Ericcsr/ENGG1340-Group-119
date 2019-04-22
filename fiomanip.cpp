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
        for(long long int cursor = str_buffer.find(@);cursor!=string::npos;cursor = str_buffer.find(@))
        {
            buffer_vect.push_back(str_buffer.substr(0,cursor);
            str_buffer.erase(0,cursor+1);
        }
        buffer_list->push_back(buffer_vect);
        size++;
    }
    list_itr = buffer_list->begin();
    fin.close();
}

void filelist::writeFile(string outfile,vector<vector<string>> buf_list)
{
    ofstream fout;
    string str_2_write;
    fout.open(outfile);
    if(fout.fail())
        file_error_handler(outfile);
    for(int i=0;i<size;i++)
    {
        str_2_write = FormatHandler(buf_list[i])
        fout<<str_2_write<<endl;
    }
    fout.close();
}

string filelist::FormatHandler(vector<string> target)
{
    vector<string>::iterator itr = target.begin();
    string str_result;
    while((itr++)!=target.end())
    {
        str_result+=*itr+'@';
    }
    return str_result;
}

filelist::filelist(string infile,string outfile)
{
    readFile(infile);
    writeFile(outfile,*buffer_list);
    ofile =  outfile;
}

//This function return the last item of the 2-D vector
//As well as destory it
vector filelist::pop_end(void)
{
    if(size>0)
        size--;
    else
    {
        cout<<"No Vector to be pop"<<endl;
        exit(1);
    }
    vector<string> result = *buffer_list[size];
    buffer_list->pop_back();
    writeFile(ofile,*buffer_list);
    return result;
}

//This function return the first item of the 2-D vector
//As well as destory it
vector filelist::pop_front(void)
{
    if(size>0)
        size--;
    else
    {
        cout<<"No vector to be pop"<<endl;
        exit(1);
    }
    vector<string> result = *buffer_list[0];
    buffer_list->erase(erase.begin(),erase.begin()+1); //Delete the element and automatically free memo
    writeFile(ofile,*buffer_list);
    list_itr = buffer_list->begin();
    return result;
}
//This function add a new object at the very beginning
//and increase the size of the vector
void filelist::push_head(vector<string> new_item)
{
    size++;
    buffer_list->insert(buffer_list->begin(),new_item);
    writeFile(ofile,*buffer_list);
    list_itr = buffer_list->begin();
}

void filelist::append(vector<string> new_item)
{
    buffer_list->push_back(new_item);
    size++;
    writeFile(ofile,*buffer_list);
}
//This function can remove a item of given index inside the file list
void filelist::remove(int index)
{
    if(index>=size)
    {
        cout<<"Index out of range"<<endl;
        exit(1);
    }
    buffer_list->erase(buffer_list->begin()+index-1,buffer_list->begin()+index);
    size--;
    if(index==0)
        list_itr = buffer_list->begin();
    writeFile(ofile,*buffer_list);
}
//This function can search for given vector and return its index;
int filelist::search(vector<string> target)
{
    int index = 0;
    while(list_itr!=buffer_list->end())
    {
        if(*list_itr==target)
        {
            list_itr = buffer_list.begin();// Update the position of the iterator
            return index;
        }
        list_itr++; 
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
    if(index==0)
    {
        list_itr = buffer_list->begin();
    }
    size++;
}
//This [] operator reload allow user to access vector members as usual
//Warning Potential bug may exist
vector filelist::&operator[](int i)
{
    return *buffer_list[i];
}
//This is defination of destructor 
//Only when this object is created as a dynamic object can this be deleted
vector filelist::~filelist()
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

bool isfile(string filename)
{
    ifstream testin;
    testin.open(filename)
    if(testin.fail())
        return 0;
    else
        return 1;
}

