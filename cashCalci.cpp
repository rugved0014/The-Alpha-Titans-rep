#include <iostream>
#include <string>

using namespace std;

// Base class
class Account {
protected:
    string ownerName;
    double balance;

public:
    Account(string name, double initialBalance) : ownerName(name), balance(initialBalance) {}

    // Virtual functions for polymorphic behavior
    virtual void deposit(double amount) {
        balance += amount;
        cout << "Deposited: " << amount << " | New Balance: " << balance << endl;
    }

    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: " << amount << " | New Balance: " << balance << endl;
        } else {
            cout << "Insufficient balance!" << endl;
        }
    }

    virtual void displayBalance() const {
        cout << "Current Balance: " << balance << endl;
    }

    virtual ~Account() {}
};

// Derived class
class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(string name, double initialBalance)
        : Account(name, initialBalance) {}

    // Overriding deposit method to add interest feature
    void deposit(double amount) override {
        
        balance += amount;
        cout << "Deposited: " << amount << "\n New Balance: " << balance << endl;
    }

    // Optional: Override other methods if needed for specific behavior

    ~SavingsAccount() override {}
};

int main() {
    // Use base class pointer to demonstrate polymorphism
    // Account* myAccount = new SavingsAccount("John Doe", 1000); // 2% interest
    string name;
    cout<<"Please enter your name: \n";
    cin>>name;
    int iniBal;
    cout<<"Enter your Current Balance:\n";
    cin>>iniBal;

    Account* myAccount=new SavingsAccount(name,iniBal);
    cout<<"What do you want to choose ?\n 1.Deposit\n 2.Withdraw\n 3.Check Balance\n";
    int choice;
    cin>>choice;
    if(choice==1){
        cout<<"Please Enter the amount:\n";
        int dep;
        cin>>dep;
    myAccount->deposit(dep); 
    myAccount->displayBalance();
    }
    else if(choice==2){
        cout<<"Please Enter the amount:\n";
        int withdr;
        cin>>withdr;
        myAccount->withdraw(withdr);
        myAccount->displayBalance();
    }
    else{
    myAccount->displayBalance();
    }
    // delete myAccount; 
    return 0;
}
