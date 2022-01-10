#include <iostream>
#include "trade.h"
#include "trade.cpp"
using namespace std;

int main(){
    char ch;
	int num;
	intro();
	do {
		system("cls");
		cout << "\n\n\tMAIN MENU";
		cout << "\n\n\t01. NEW ACCOUNT";
		cout << "\n\t02. DEPOSIT AMOUNT";
		cout << "\n\t03. WITHDRAW AMOUNT";
		cout << "\n\t04. ACCOUNT ENQUIRY";
		cout << "\n\t05. CLOSE AN ACCOUNT";
		cout << "\n\t06. ALL STOCKS LIST";
		cout << "\n\t07. BUY STOCK";
		cout << "\n\t08. SELL STOCK";
		cout << "\n\t09. EXIT";
		cout << "\n\tSelect Your Option (1-9) ";
		cin >> ch;
		system("cls"); // Clear output screen
		switch(ch){
		case '1':
			writeAccount();
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; 
			cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The account No. : "; 
			cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tEnter The account No. : "; 
			cin>>num;
			displayAccDetails(num);
			break;
		case '5':
			cout<<"\n\n\tEnter The account No. : "; 
			cin>>num;
			deleteAccount(num);
			break;
		case '6':
			displayStocks();
			break;
		case '7':
			cout<<"\n\n\tEnter The account No. : "; 
			cin>>num;
			buyOrSellStock(num, 1);
			break;
		case '8':
			cout<<"\n\n\tEnter The account No. : "; 
			cin>>num;
			buyOrSellStock(num, 2);
			break;
		case '9':
			cout<<"\n\n\tTrading System o go riyō itadaki arigatōgozaimasu";
			break;
		default :
		 	cout<<"Please select an option from 1-9 only";
		}
		cin.ignore();
		cin.get();
	} while(ch!='9');
	return 0;
}
