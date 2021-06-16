/* Write a program to read series of names, one per line, from standard input and write these names spelled in reverse order to the standard output using I/O redirection and pipes. Repeat the exercise using an input file specified by the user instead of the standard input and using an output file specified by the user instead of the standard output. */

#include <iostream>
using namespace std;
#include <fstream>
#include <string>

int main()
{
    int n,i,j;
    string name,rev,temp;
    
    ofstream f1,f2;
    //f1 stores orginal name
    //f2 stores reversed name
    
    cout<<"\nEnter the no of names you want to enter:";
    cin>>n;
    
    f1.open("Normalname.txt");
    f2.open("reversedname.txt");
    
    for(i=0;i<n;i++)
    {
        cout<<"\nEnter name "<<i+1<<":";
        cin>>name;
        f1<<name<<endl;
        int k=name.length();
        
        rev.erase();
        for(j = k ; j>=0 ; j--)
        {
            temp.erase();
            rev=rev+temp+name[j];
        }
        cout<<"\nThe reserved name is:\n";
        cout<<rev<<endl;
        f2<<rev<<endl;
        
    }
    f1.close();
    f2.close();
    
}

