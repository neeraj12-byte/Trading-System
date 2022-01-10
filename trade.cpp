#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "trade.h"
#include<fstream>
#include<cctype>
using namespace std;

string Stock::getName() const{
    return name;
}

float Stock::getPrice() const{
    return price;
}

void Account::createAccount(){
    cout<<"\nEnter The account No. :";
	cin >> acno;
	cout<<"\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name,100);
	cout<<"\nEnter The Initial amount(>=500) : ";
	cin>>funds;
	cout<<"\n\n\nAccount Created..";
}

void Account::showAccount() const{
	cout << "\nAccount Holder Name : " << name;
	cout << "\nBalance funds : " << funds;
    cout << "\nStocks owned : \n";
    for(int i=0; i<stocks.size(); i++)
        cout << stocks[i].second<<" owned of "<<(stocks[i].first).getName() << endl;
}
	
void Account::dep(int x){
	funds+=x;
}
	
void Account::draw(int x){
	funds-=x;
}

void Account::buy(string s, float n){
    pair<string, float> st;
    st.first = s;
    st.second = n;
    for(int i=0; i<stocks.size(); i++){
        if((stocks[i].first).getName() == s){
            stocks[i].second+=n;
            return ;
        }
    }
    stocks.push_back(st);
}
void Account::sell(string s, float n){
    pair<string, float> stock;
    stock.first = s;
    stock.second = n;
    for(int i=0; i<stocks.size(); i++){
        if((stocks[i].first).getName() == s){
            stocks[i].second-=n;
            if(stocks[i].second <= 0){
                stocks.erase(stocks.begin()+i);
                cout<<"You sold all your holdings of this stock";
            }
            return ;
        }
    }
    cout << "\nYou do not own this stock";
}

int Account::getAcno() const{
	return acno;
}

int Account::getFunds() const{
	return funds;
}

void writeAccount(){
	Account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.createAccount();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(Account));
	outFile.close();
}

void displayAccDetails(int n){
	Account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile){
		cout<<"File could not be opened !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE AND STOCK DETAILS\n";

    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Account))){
		if(ac.getAcno()==n){
			ac.showAccount();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}

void deleteAccount(int n){
	Account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile){
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Account))){
		if(ac.getAcno()!=n){
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(Account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}

void deposit_withdraw(int n, int option){
	int amt;
	bool found=false;
	Account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File){
		cout<<"File could not be opened !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false){
		File.read(reinterpret_cast<char *> (&ac), sizeof(Account));
		if(ac.getAcno()==n){
			ac.showAccount();
			if(option==1){
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\nEnter The amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2){
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\nEnter The amount to be withdrawn";
				cin>>amt;
                if(ac.getFunds()<amt)
                    cout<<"\nInsufficient Funds. Gomen";
				else
                    ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(Account));
			cout<<"\n\n\t Record Updated";
			found=true;
	    }
    }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

void buyOrSellStock(int n, int option){
	bool found=false;
	Account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File){
		cout<<"File could not be opened !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false){
		File.read(reinterpret_cast<char *> (&ac), sizeof(Account));
		if(ac.getAcno()==n){
            cout<<"\nEnter the stock to be bought/sold";
            string sName;        
            cin >> sName;
			Stock st;
	        fstream StockFile;
            StockFile.open("stocks.dat", ios::binary|ios::in|ios::out);
            while(!StockFile.eof()){
                File.read(reinterpret_cast<char *> (&st), sizeof(Stock));
                if(st.getName()==sName){
                    if(option==1){
                        cout<<"\nEnter the amount of stocks to buy";
                    	int amt;
                        cin >> amt;
                        if(ac.getFunds()<amt)
                            cout<<"\nInsufficient Funds. Gomen";
			            float sQuant;
                        sQuant = (float)amt/st.getPrice();
                        ac.buy(sName, sQuant);
                    }
                    else{
                        cout<<"\nEnter the number of stocks to sell";
                        float no;
                        cin >> no;
                        ac.sell(sName, no);
                    }
                }
            }
            StockFile.close();
        }
		int pos=(-1)*static_cast<int>(sizeof(ac));
		File.seekp(pos,ios::cur);
		File.write(reinterpret_cast<char *> (&ac), sizeof(Account));
		cout<<"\n\n\t Record Updated";
		found=true;
    }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

void displayStocks(){
    Stock st;
	bool flag=false;
	ifstream inFile;
	inFile.open("stocks.dat",ios::binary);
	if(!inFile){
		cout<<"File could not be opened !! Press any Key...";
		return;
	}
	cout<<"\nALL STOCK DETAILS\n";
    while(inFile.read(reinterpret_cast<char *> (&st), sizeof(Stock))){
		cout<< st.getName()<<"\tRs. "<<st.getPrice()<<endl;
	}
	inFile.close();
}

void intro(){
    cout<<"\n\n\n\tIRASSHAIMASE!";
	cout<<"\n\n\t  TRADING SYSTEM";
	cout<<"\n\n\nMADE BY : Aashish\n\n";
	cin.get();
}
