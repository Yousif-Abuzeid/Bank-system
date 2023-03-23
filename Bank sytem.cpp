#include <iostream>
#include<cctype>
#include<cstdlib>
#include<string.h>
using namespace std;
class ATM { //class declaration
private :
    char Name[100];
    char CardNum[20];
    float Amount;
public :
    ATM (){Amount=0;
        CardNum[30]={'\0'};
    }



    bool search1(char a[]){   //function searches for card number

    if(!strcmp(CardNum,a))
        return true;
    else
        return false;

    }

    void Create_new_acc();
    void Deposit();
    void withdrawal();
    void Transfer(int);
    void print_acc_data(){
    cout<<"Name: "<<Name<<endl;
    cout<<"Card Number: "<<CardNum<<endl;
    cout<<"Amount: "<<Amount<<endl;

    }
};
ATM Accounts[100];               //creation 100 objects

int index (char card[] ,ATM acc[]){        //function returns index of card number
    int i=0;
for( i=0; i<100; i++){
    if(acc[i].search1(card)){
    return i;
    }
}
return -1;
}


bool ValidName(char namee[]){        // check if the name is valid
int i=0;
bool check = true ;
 while(namee[i]!='\0')
   {
      if(!(isalpha(namee[i])) && namee[i]!=' ')      //only consists of characters
        check = false;
        i++;
   }
return check;}

bool ValidCard(char card[]){                  //check if the card number is valid
int i=0;
bool check = true ;
int count=0;
for(int i=0; card[i]; i++){
    if(isdigit(card[i]))
        count++;
    else if(!isdigit(card[i])|| card[i]!='\0')
    {
        cout<<"Error you can't enter a letter or a symbol"<<endl; //The card number with no any symbol
        check=false; return check;
    }}
    if(count<10){
        cout<<"Error you entered less than 10 numbers"<<endl; //less than 10 num
        check=false; return check;
    }
    if(count>10){
        cout<<"Error you entered more than 10 numbers"<<endl;  //more than 10 num
        check=false; return check;
    }

count=1;
    for(int i=0;i<9;i++)                              //check for weak number
    {
        if (card[i]==card[i+1]) count++; else count = 1;             //the card number cant have the same 4 following number,for example
                                                                     //for example 1826666547,0000126498,5555555555
        if (count==4) {check=false; cout<<"Your number is weak,Please Try another one"<<endl; return check;}
    }

       for(i=0;i<100;i++)
       {
           bool find_num;
           find_num=Accounts[i].search1(card);                 //the created card number cant be existed before
           if(find_num){cout<<"The account number already exists,Please Try another number"<<endl;
           check=false; return check;}
       }

    return check;}




void ATM::Create_new_acc()
{
char namee[100];                                 //creation of account
char card[30];
cout<<"Enter The Account Name: ";
bool flag=true;
while(flag){
cin.getline(namee,100);
if(ValidName(namee)){         //check if it valid name
flag =false;
break;

}
else cout<<"Enter A Valid Name: ";

}int i;
for(i=0; namee[i]; i++)
    Name[i]=namee[i];
Name[i]='\0';
cout<<"Enter The Account Number (10 numbers):";
flag =true;
while (flag){
    cin.getline(card,30);
    if(ValidCard(card)){                   //check if it valid number
        flag =false;
        break;
    }else
    cout<<"Enter A Valid Number(10 numbers): ";
}
for( i=0; card[i]; i++){

    CardNum[i]=card[i];
}
CardNum[i]='\0';
print_acc_data();
}

void ATM::Deposit(){                           //deposit function
float DepAmount;
start:
cout<<"Please enter the amount to be deposited: ";
cin>>DepAmount;
if (!cin){
    cin.clear();
    cin.ignore();
    cout<<"Error you can't deposit a letter"<<endl;   //if the user entered a character
    goto start;
}
if(DepAmount>0){
Amount+=1.01*DepAmount;
cin.ignore();
print_acc_data();

}else
cout<<"Error you can't deposit a negative number"<<endl;
}

void ATM::withdrawal(){                       // withdrawal function
float WithdrawnAmount;
bool Option=false;
start:
cout<<"Please enter the amount to be withdrwan: ";
cin>>WithdrawnAmount;
if (!cin){
    cin.clear();
    cin.ignore();
    cout<<"Error you can't deposit a letter"<<endl;     //if the user entered a character
    goto start;}
while(!Option){

if(WithdrawnAmount>0){
if(Amount<1.03*WithdrawnAmount)
    {cout<<"Insufficient funds "<<endl<<"Your balance is : "<<Amount<<endl;  //print the balance of the account
    cout<<"Do you want to Return to main?"<<endl<<"Yes:1"<<endl<<"No:0"<<endl;  //an option to return to the main or try to enter another amount
    cin>>Option;
    if(!Option){cout<<"Try again,Please enter the amount to be withdrwan"<<endl; cin>>WithdrawnAmount;}
    }


else{
    Amount-=1.03*WithdrawnAmount;
print_acc_data();
return;

}}
else
    {cout<<"Error you cant withdraw a negative number"<<endl<<"Do you want to Return to main?"<<endl<<"Yes:1"<<endl<<"No:0"<<endl;
     cin>>Option; if(!Option) {cout<<"Try again with a positive number"<<endl;  cin>>WithdrawnAmount;}                                                                 }
}}

void ATM::Transfer(int i){                                      // transfer function
    bool Option=false;
    float TraAmount;
    start:
    cout<<"Enter the amount to be transfered: ";
    cin>>TraAmount;
    if (!cin){
    cin.clear();
    cin.ignore();
    cout<<"ERROR YOU CAN'T TRANSFER A LETTER"<<endl;      //if the user entered a character
    goto start;
}
    while(!Option){
    if(TraAmount>0){
        if(Amount<1.03*TraAmount){
            cout<<"Insufficient funds "<<endl<<"Your balance is : "<<Amount<<endl;  //print the balance of the account
            cout<<"Do you want to return to main?"<<endl<<"Yes:1"<<endl<<"No:0"<<endl;  //an option to return to the main or try to enter another amount
            cin>>Option; if(!Option){cout<<"Try again,Please enter the amount to be withdrwan"<<endl; cin>>TraAmount; }
}
        else {
            Amount-=1.03*TraAmount;
            Accounts[i].Amount+=0.97*TraAmount;
            cout<<"Sending Account :"<<endl;
            print_acc_data();                        //print the sending account
            cout<<"Receiving Account :"<<endl;
            Accounts[i].print_acc_data();            //print the receiving account
            return;
        }

    }                                                                                          //an option to return to the main or try to enter another amount
    else{cout<<"You can't enter a negative number"<<endl<<"Do you want to return to main?"<<endl<<"Yes:1"<<endl<<"No:0"<<endl; //if user has..
    cin>>Option; if(!Option){cout<<"Try again with a positive number"<<endl; cin>>TraAmount; }}                    //..entered a negative number


}}


int main()
{
    int i=0;
    int WhichIndex;                    //an index of an account
    int WhichIndex2;                   //an index of a receiver account
    bool flag =true;
    bool test ;
    int NumAcc=0;                     //a counter to count number of existed accounts
    while (flag){
    char Account[30];
    char Account2[30];
    char Card[30]={'\0'};
    int operation;
    cout<<"1----Create new account"<<endl;
    cout<<"2----Deposit"<<endl;
    cout<<"3----Transfer to another account"<<endl;
    cout<<"4----Withdrawal"<<endl;
    cout<<"5----Exit"<<endl;
    cout<<"Please enter the number of operation: ";
    cin>>operation;
    if(operation<1 || operation>5){
        cout<<"Please enter a number from 1 to 5"<<endl;
    }

    if(!cin){
        cin.clear();
       cin.ignore();
    }
    switch(operation){
        case 1: // account creation
            cin.ignore();
            Accounts[NumAcc].Create_new_acc();
            NumAcc++;

            break;
        case 2: // deposit
            if(NumAcc<1){
                cout<<"There is no accounts to deposit"<<endl;
                cout<<"Please create an account first"<<endl;
                break;

            }
           cout<<"Please enter the card number: ";
           cin.ignore();
           cin.getline(Account,30);
          test = false;
           while(!test){
            WhichIndex=index(Account,Accounts);
           if(WhichIndex==-1)                            //User has Entered a false number
           {
               cout<<"Account does't exist"<<endl<<"Please Try another Account"<<endl;

           cin.getline(Account,30);

           }
           else test=true; }
            Accounts[WhichIndex].Deposit();
            break;

        case 3: // transfer
            if(NumAcc<2){
                cout<<"Not enough accounts to transfer"<<endl;
                break;}
            cout<<"please enter the number of the sending account(10 numbers):";
            cin.ignore();
            cin.getline(Account,30);

            test=false;
           while (!test){
           WhichIndex=index(Account,Accounts);
           if(WhichIndex==-1){                                //searching if the sending account is existed or not
            cout<<"Sending Account does't exist"<<endl<<"Please Try again"<<endl;
            cin.getline(Account,30);
            }
           else test=true;
           }
            cout<<"please enter the number of the receiving account(10 numbers):";  //searching if the receiving account is existed or not

            cin.getline(Account2,30);
            test=false;
            while(!test)
              {   WhichIndex2=index(Account2,Accounts);
                  if(WhichIndex2==-1){
               cout<<"Receiving Account does't exist"<<endl<<"Please Try again!"<<endl;
               cin.getline(Account2,30);
              }
           else test=true;}
            Accounts[WhichIndex].Transfer(WhichIndex2);
        break;



        case 4: //withdrawal
            if(NumAcc<1){
                cout<<"There is no accounts to withdraw"<<endl;
                cout<<"Please create an account first"<<endl;
                break;}
           cout<<"Please enter the card number: ";
           cin.ignore();
           cin.getline(Account,30);
          test=false;
          while(!test){
           WhichIndex=index(Account,Accounts);
           if(WhichIndex==-1)                               //User has Entered a false number
              {cout<<"Account does't exist"<<endl<<"Please Try another Account"<<endl;
              cin.getline(Account,30);
              }
           else test = true;}
            Accounts[WhichIndex].withdrawal();
            break;

        case 5 : // exit
            flag = false ;




    }



} return 0 ;}