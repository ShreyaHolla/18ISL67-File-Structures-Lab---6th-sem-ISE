/*Write a program to read and write student objects with Variable - Length records using any suitable record structure. Implement pack ( ), unpack ( ), modify ( ) and search ( ) methods.*/

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class student{
    
public:
    string USN;
    string name;
    string branch;
    string sem;
    string buffer;
    
    void read();
    void pack();
    void write();
    void unpack();
    int search(string);
    int delete_from_file(string);
    void modify(string);
    
};

void student::read()
{
    cout<<"\nUSN:"; cin>>USN;
    cout<<"\nName:";cin>>name;
    cout<<"\nBranch:";cin>>branch;
    cout<<"\nSemester:";cin>>sem;
}

void student::pack()
{
    buffer+=USN+'|'+name+'|'+branch+'|'+ sem+'$'+'\n';
}

void student::write()
{
    fstream file;
    file.open("3.txt");
    file<<buffer;
    file.close();
}

void student::unpack()
{
    int i=0;
    
    USN.erase();
    while(buffer[i]!='|')
        USN+=buffer[i++];
    
    name.erase();
    i++;
    while(buffer[i]!='|')
        name+=buffer[i++];
    
    branch.erase();
    i++;
    while(buffer[i]!='|')
        branch+=buffer[i++];
    
    sem.erase();
    i++;
    while(buffer[i]!='|')
        sem+=buffer[i++];
    
}

int student::search(string key)
{
    ifstream file;
    int flag=0,pos=0;
    
    file.open("3.txt");
    while(!file.eof())
    {
        buffer.erase();
        getline(file,buffer);
        unpack();
        
        if(key == USN)
        {
            cout<<"\nFound the Key.";
            cout<<"\nThe record is:"<<buffer;
            pos = file.tellg();
            flag=1;
            return pos;
        }
        
    }
    file.close();
    if(!flag)
    {
        cout<<"\nFile not found.";
       
    }
     return pos;
}
void student::modify(string key)
{
    int choice;
    
    if(delete_from_file(key))
    {
        cout<<"\n What do you want to modify?";
        cout<<"\n 1. USN  2.Name   3.Branch   4.Sem"<<endl;
        cin>>choice;
        
        switch(choice)
        {
            case 1:
                cout<<"\nUSN:";
                cin>>USN;
                break;
                
            case 2:
                cout<<"\nName:";
                cin>>name;
                break;
                
            case 3:
                cout<<"\nBranch:";
                cin>>branch;
                break;
                
            case 4:
                cout<<"\nSemester:";
                cin>>sem;
                break;
                
            default:
                cout<<"\nWrong Choice:";
                break;
                
        }
        buffer.erase();
        pack();
        write();
    }
}

int delete_from_file(string key)
{
    fstream file;
    char del_mark='*';
    char t;
    int pos,flag=0;
    
    pos = search(key);
    
    if(pos)
    {
        file.open("3.txt");
        pos=-2;// skip the $ character and \n character
        t=file.get();
        while(t!='$' && pos!=0)
        {
            pos--;
            file.seekp(pos);
            t=file.get();
        }
        if(pos!=0)
        {
            file.seekp(pos+2);
            
        }
        else{
            file.seekp(pos);
        }
        file.put(del_mark);
        flag=1;
    }
    file.close();
    if(!flag)
    {
        return 0;
        
    }
    else
    {
        return 1;
    }
    
}
 
    
    
    int main()
{
        int count,choice,i;
        
        student s1;
        string key;
        
        while(true)
        {
            cout<<"\n***********  MAIN MENU  ***************\n1)Add\n2)Delete\n3)Modify\n4)Search\n5)Exit\nEnter your choice:";
            cin>>choice;
            
            switch(choice)
            {
                case 1:
                    cout<<"\nEnter the no of records to insert:";
                    cin>>count;
                    
                    for(int j=0;j<count;j++)
                    {
                        cout<<"Record "<<j+1<<":\n";
                        s1.read();
                        s1.pack();
                    }
                    s1.write();
                    break;
                    
                case 2:
                    cout<<"\nEnter USN of the record to be deleted:";
                    cin>>key;
                    i=s1.delete_from_file(key);
                    break;
                    
                case 3:
                    cout<<"\nEnter the USN of the record to be modified:";
                    cin>>key;
                    s1.modify(key);
                    break;
                    
                case 4:
                    cout<<"\nEnter the USN of the record to be searched:";
                    cin>>key;
                    s1.search(key);
                    break;
                    
                default:
                    cout<<"\n*********** See you next time **************";
                    return 0;
                    
            }
        }
        
        return 0;
        
}

