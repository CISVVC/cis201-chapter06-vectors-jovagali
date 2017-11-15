//File Name: main.cpp
//Developer: Jovanny Galindo
//Email: galindofloresj@student.vvc.edu
//Description: This program has a user input thei withdrawals and deposits in a bank account and outputs the bank statements.

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class Transaction
{
public:
   Transaction();
   void read();
   int get_day();
   double get_amount();
   void print() const;
private:
   int day;
   double amount;
   std::string description;
};

Transaction::Transaction()
{
  day = 0;
  amount = 0.0;
}

void Transaction::read()
{
  std::cout << "Enter the day:";
  std::cin >> day;
  std::cout << "Enter the amount:";
  std::cin >> amount;
  std::cout << "Enter the description:";
  std::cin.ignore();
  std::getline(std::cin,description);
}

int Transaction::get_day()
{
  return day;
}

double Transaction::get_amount()
{
  return amount;
}

void Transaction::print() const
{
  std::cout << "day: " << day << std::endl;
  std::cout << "amount: " << amount << std::endl;
  std::cout << "description: " << description << std::endl;
}

const int MAX_DAY = 30;

class Statement
{
public:
   Statement();
   void read();
   void compute_balances();
   void print();
   double get_average_daily_balance();
   double get_minimum_daily_balance();
private:
   std::vector<Transaction> transactions;
   std::vector<double> daily_balances;
};

Statement::Statement()
{
}

void Statement::read()
{
  bool more = true;
  while(more)
  {
    Transaction new_tran;
    new_tran.read();
    
    std::cout << "More input? (y/n)";
    std::string answer;
    std::getline(std::cin, answer);
    if(answer != "y")
       more = false;
    else
    {
      transactions.push_back(new_tran);
    }
  }
  compute_balances();
}

void Statement::compute_balances()
{
  int day;
  int i = 0;
  double balance = 0.0;
  for(day = 1; day <= MAX_DAY; day++)
  {
    while(i < transactions.size() && transactions[i].get_day() == day)
    {
      balance = balance + transactions[i].get_amount();
      i++;
    }
    daily_balances.push_back(balance);
  } 
}

void Statement::print() 
{
  int i = 0;
  std::cout << std::endl << "Statement" << std::endl;
  for(int day = 1; day <= MAX_DAY; day++)
  {
    if(i < transactions.size() && transactions[i].get_day() == day)
    {
      transactions[i].print();
      i++;
      std::cout << "Day: " << std::setw(2) << day << " Amount: " << daily_balances[i - 1]<< std::endl << std::endl;
    }
    else
    {
      day = 31;
    }
  }
  
  const double interest = 0.005;
  std::cout << "Minimun daily balance interest: " << get_minimum_daily_balance() * interest << std:: endl;
  std::cout << "Average daily balance interest: " << get_average_daily_balance() * interest << std::endl;
}

double Statement::get_average_daily_balance()
{
  int day;
  double bals_sum = 0.0;
  for(day = 0; day < daily_balances.size(); day++)
  {
    bals_sum = bals_sum + daily_balances[day];
  }
  return bals_sum/MAX_DAY;
}

double Statement::get_minimum_daily_balance()
{
  int day;
  double min_bal = daily_balances[0];
  for(day = 1; day < daily_balances.size(); day++)
  {
    if(daily_balances[day] < min_bal)
    {
      min_bal = daily_balances[day];
    }
  }
  return min_bal;
}

int main()
{
  Statement stat;
  stat.read();
  stat.print();

   return 0;
}
