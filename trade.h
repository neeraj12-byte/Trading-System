#ifndef TRADE_H_
#define TRADE_H_

#include <string>
#include <vector>
#include <utility>
using namespace std;

class Stock{
private:
    float price;
    char name[4];

public:
    string getName() const;
    float getPrice() const;
};

class Account{
private:
    int acno;
    char name[100];
	vector<pair<Stock, float> > stocks;
	int funds;

public:
    void createAccount();
	void showAccount() const;
	void dep(int);
	void draw(int);
    void buy(string, float);
    void sell(string, float);
	int getAcno() const;
    int getFunds() const;
};

void writeAccount();
void displayAccDetails(int);
void deleteAccount(int);
void deposit_withdraw(int, int);
void buyOrSellStock(int, int);
void displayStocks();
void intro();

#endif
