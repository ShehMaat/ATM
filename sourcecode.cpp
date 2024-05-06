#include<fstream>
#include<ctype.h>
#include<stdio.h>
#include<iostream>
#include<iomanip>
using namespace std;


//*class used in project//*


class account
{
    int acno;
    char name[50];
    int deposit;
    char type;
    public:
    void create_account();
    void show_account();
    void modify();
    void dep(int);
    void draw(int);
    void report();
    int retacno();
    int retadeposit();
    char rettype();
};
void account::create_account()
{
    cout<<"\nEnter the account no. :";
    cin>>acno;
    cout<<"\n\nEnter the Name of the account Holder : ";
    cin>>name;
    cout<<"\nEnter type of account (c/s) : ";
    cin>>type;
    type=toupper(type);
    cout<<"\nEnter the initial amount (>=500 for saving and >=1000 for current) : ";
    cin>>deposit;
    cout<<"\n\n\nAccount Created..";
}
void account::show_account()
{
    cout<<"\nAccount No. : "<<acno;
    cout<<"\nAccount Holder Name : ";
    cout<<name;
    cout<<"\nType of Account : "<<type;
    cout<<"\nBalance amount ; "<<deposit;
}
 
 void account::modify()
 {
    cout<<"\nThe account No."<<acno;
    cout<<"\n\nEnter The Name of the acount Holder : ";
    cin>>name;
    cout<<"\nEnter Type of the account Holder : ";
    cin>>type;
    type=toupper(type);
    cout<<"\nEnter the amount : ";
    cin>>deposit;
 }

 void account::dep(int x)
 {
    deposit+=x;
 }

 void account::draw(int x)
 {
    deposit-=x;
 }
 void account::report()
 {
    cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
 }
 int account::retacno()
 {
    return acno;
 }
 int account::retadeposit()
 {
    return deposit;
 }

 char account::rettype()
 {
    return type;
 }


 //*function declaration//*


 void write_account();
 void display_sp(int);
 void modify_account(int);
 void delete_account(int);
 void display_all();
 void deposit_withdraw(int,int);
 void intro();


 //*The main function of program//*


 int main()
 {
    char ch;
    int num;
    intro();
    do
    {
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t01. NEW ACCOUNT";
        cout<<"\n\n\t02. DEPOSIT AMOUNT";
        cout<<"\n\n\t03. WITHDRAW AMOUNT";
        cout<<"\n\n\t04. BALANCE ENQUIRY";
        cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";\
        cout<<"\n\n\t06. CLOSE AN ACCOUNT";
        cout<<"\n\n\t07. MODIFY AN ACCOUNT";
        cout<<"\n\n\t08. EXIT";
        cout<<"\n\n\tSelect Your Option(1-8)";
        cin>>ch;
        switch(ch)
        {
            case '1':
            write_account();
            break;
            case '2':
            cout<<"\n\n\tEnter The account No. : ";
            cin>>num;
            deposit_withdraw(num,1);
            break;
            case '3':
            cout<<"\n\n\tEnter the account No. : ";cin>>num;
            deposit_withdraw(num,2);
            break;
            case '4':
            cout<<"\n\n\tEnter The account No. : ";cin>>num;
            display_sp(num);
            break;
            case '5':
            display_all();
            break;
            case '6':
            cout<<"\n\n\tEnter The Account No. : ";cin>>num;
            delete_account(num);
            break;
            case '7':
            cout<<"\n\n\tEnter The account No. : ";cin>>num;
            modify_account(num);
            break;
            case '8':
            cout<<"\n\n\tThanks for using bank management system";
            break;
            default :cout<<"\a";
        }
    } while (ch!='8');
    return 0;
 }


 //*function to write in file


 void write_account()
    {
        account ac;
        ofstream outfile;
        outfile.open("account.dat",ios::binary|ios::app);
        ac.create_account();
        outfile.write((char*) &ac, sizeof(account));
        outfile.close();
    }

//* function to read specific record from file


void display_sp(int n)
{
    account ac;
    int flag=0;
    ifstream infile;
    infile.open("account.dat",ios::binary);
    if(!infile)
    {
        cout<<"file could note be open !! Press any key...";
        return;
    }
    cout<<"\nBALANCE DETAILS\n";
    while(infile.read((char*) &ac, sizeof(account)))
    {
        if(ac.retacno()==n)
        {
            ac.show_account();
            flag=1;
        }
    }
    infile.close();
    if(flag==0)
    cout<<"\n\nAccount number does not exist";
}


//*function to modify record file
void modify_account(int n)
{
    int found=0;
    account ac;
    fstream file;
    file.open("account.dat",ios::binary|ios::in|ios::out);
    if(!file)
    {
        cout<<"File could not be open !! Press any key...";
        return;
    }
    while(file.read((char *) &ac, sizeof(account)) && found==n)
    {
        if (ac.retacno()==n)
        {
            ac.show_account();
            cout<<"\n\nEnter The New Details of account"<<endl;
            ac.modify();
            int pos=(-1)*sizeof(account);
            file.seekp(pos,ios::cur);
            file.write((char*) &ac, sizeof(account));
            cout<<"\n\n\t Record Updated";
            found=-1;
        }
    }
    file.close();
    if(found==0)
    cout<<"\n\n Record Not Found ";
}


//*function to delete record of file 


void delete_account(int n)
{
    account ac;
    ifstream infile;
    ofstream outfile;
    infile.open("account.dat",ios::binary);
    if(!infile)
    {
        cout<<"FIle could not be open !! Press any key...";
    return;
    }
    outfile.open("Temp.dat",ios::binary);
    infile.seekg(0,ios::beg);
    while(infile.read((char*) &ac,sizeof(account)))
    {
        if(ac.retacno()!=n)
        {
            outfile.write((char*) &ac, sizeof(account));
        }
    }
    infile.close();
    outfile.close();
    remove("account.dat");
    rename("Temp.dat","account.dat");
    cout<<"\n\n\tRecord Deleted..";
}

//*function to display all accounts deposit list

void display_all()
{
    account ac;
    ifstream infile;
    infile.open("account.dat",ios::binary);
    if(!infile)
    {
        cout<<"file could not be open !! Press any key..";
        return;
    }
    cout<<"\n\n\tACCOUNT HOLDER LIST\n\n";
    cout<<"===========================================\n";
    cout<<"A/c no.      NAME        Type Balance\n";
    cout<<"===========================================\n";
    while(infile.read((char*) &ac, sizeof(account)))
    {
        ac.report();
    }
    infile.close();
}


//*function to deposit and withdraw amounts 


void deposit_withdraw(int n,int option)
{
    int amt;
    int found=0;
    account ac;
    fstream file;
    file.open("account.dat",ios::binary|ios::in|ios::out);
    if(!file)
    {
        cout<<"File could not be open !! Press any key...";
        return;
    }
    while(file.read((char*) &ac, sizeof(account)) && found==0)
    {
        if(ac.retacno()==n)
        {
            cout<<"\n\n\tTO DEPOSIT AMOUNT";
            cout<<"\n\nEnter The amount to be deposited";
            cin>>amt;
            ac.dep(amt);
        }
        if(option==2)
        {
            cout<<"\n\n\tTO WITHDRAW AMOUNT";
            cout<<"\n\nEnter The amount to be withdraw";
            cin>>amt;
            int bal=ac.retadeposit()-amt;
            if((bal<500 && ac.rettype()=='S')||(bal<1000 && ac.rettype()=='C'))
            {
            cout<<"Insufficient balance";
            }
            else
            {
                ac.draw(amt);
            }
            int pos=(-1)*sizeof(ac);
            file.seekp(pos,ios::cur);
            file.write((char *) &ac, sizeof(account));
            cout<<"\n\n\tRecord Updated";
            found=1;
        }
    }
    file.close();
    if(found==0)
    cout<<"\n\nRecord Not Found";
}


//* INTRODUCTON FUNCTION


void intro()
{
    cout<<"\n\n\t BANK";
    cout<<"\n\n\t MANAGEMENT";
    cout<<"\n\n\t SYSTEM";
    cout<<"\n\n\tMADE BY: PULKIT JAIN";
}
// End of Project