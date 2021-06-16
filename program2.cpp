/* Write a program to read and write student objects with fixed-length records and the fields delimited by “|”. Implement pack ( ), unpack ( ), modify ( ) and search ( ) methods.*/

#include <iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

class student
{
    public: string USN;
            string Name;
            string Branch;
            string Semester;
            string buffer;
    
    void read_data();
    void pack();
    void write_to_file();
    void unpack();
    int search(string);
    int delete_from_file(string);
    void modify(string);
    
    
    
};

void student::read_data()
{
    cout<<"\nUSN:"; cin>>USN;
    cout<<"\nName:"; cin>>Name;
    cout<<"\nBranch:"; cin>>Branch;
    cout<<"\nSemester:";cin>>Semester;
}

void student::pack()
{
    string temp;
    temp.erase();
    temp+=USN+'|'+Name+'|'+Branch+'|'+Semester;
    
    for(;temp.size()<100;)
        temp+='$';
    
    buffer+=temp+'\n';
    
}

void student::write_to_file()
{
    fstream file;
    file.open("2.txt");
    file<<buffer;
    file.close();
}

void student::unpack()
{
    int i=0;
    
    USN.erase();
    while(buffer[i]!='|')
        USN+=buffer[i++];
    
    Name.erase();
    i++;
    while(buffer[i]!='|')
        Name+=buffer[i++];
    
    Branch.erase();
    i++;
    while(buffer[i]!='|')
        Branch+=buffer[i++];
    
    Semester.erase();
    i++;
    while(buffer[i]!='$')
        Semester+=buffer[i++];
}

int student::search( string no)
{
    ifstream file;
    int pos=0;
    file.open("2.txt");
    
    while(!file.eof())
    {
        buffer.erase();
        getline(file,buffer);
        unpack();
        
        if(no == USN)
        {
            cout<<"USN is present.\n The record is :"<<buffer;
            pos=file.tellg();
            return pos;
        }
    }
    file.close();
    cout<<"USN not found\n";
    return pos;
}

int student::delete_from_file(string no)
{
    fstream file;
    char del_mark='*';
    int pos,flag=0;
    
    pos=search(no);
    
    if (pos)
    {
        file.open("2.txt");
        pos=-101;
        file.seekp(pos);
        file.put(del_mark);
        flag=1;
    }
    file.close();
    if(!flag)
        return 0;
    else
        return 1;
}

void student:: modify( string no)
{
    int choice;
    if(delete_from_file(no))
    {
        cout<<"\nWhat do you want to modify?\n1)USN\n2)Name\nBranch\n4)Semester\nEnter your choice:";
        cin>>choice;
        
        switch(choice)
        {
            case 1:
                cout<<"\nUSN:";
                cin>>USN;
                break;
                
            case 2:
                cout<<"\nName:";
                cin>>Name;
                break;
                
            case 3:
                cout<<"\nBranch:";
                cin>>Branch;
                break;
                
            case 4:
                cout<<"\nSemester:";
                cin>>Semester;
                break;
                
            default:cout<<"\nWrong Choice:";
                
            
        }
        buffer.erase();
        pack();
        write_to_file();
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
                    s1.read_data();
                    s1.pack();
                }
                s1.write_to_file();
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

