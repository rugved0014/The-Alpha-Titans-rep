#include <iostream>
#include <string>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

// Function prototypes
bool loadAccountsFromJson(const string& filename, json& j);

class User {
private:
    string username;
    string password;
public:
    void setUsername(const string& uname) {
        username = uname;
    }

    void setPassword(const string& pwd) {
        password = pwd;
    }

    string getUsername() const {
        return username;
    }

    string getPassword() const {
        return password;
    }
};

class WelcomePage {
public:
    void display() {
        cout << "+--------------------------------------+\n";
        cout << "|                                      |\n";
        cout << "|     Welcome to Integrated POS        |\n";
        cout << "|              Calculator              |\n";
        cout << "|                                      |\n";
        cout << "+--------------------------------------+\n";

        cout << "Are you a new user?                 \n";
        cout << "1. Yes (Sign Up)                    \n";
        cout << "2. No (Login)                       \n";
    }

    int getUserChoice() {
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        return choice;
    }
};

class SignUpPage {
public:
    User signUp() {
        User newUser;
        string uname, pwd;
        json j;
        string filename = "users.json";

        cout << "Enter username: ";
        cin >> uname;
        cout << "Enter password: ";
        cin >> pwd;

        if (!loadUsersFromJson(filename, j)) {
            cout << "Error loading users, creating new file.\n";
            j = {{"users", json::array()}};
        }

        j["users"].push_back({{"username", uname}, {"password", pwd}});
        saveUsersToJson(filename, j);

        newUser.setUsername(uname);
        newUser.setPassword(pwd);
        return newUser;
    }

    bool loadUsersFromJson(const string& filename, json& j) {
        ifstream inFile(filename);
        if (!inFile) {
            return false;
        }
        inFile >> j;
        inFile.close();
        return true;
    }

    void saveUsersToJson(const string& filename, const json& j) {
        ofstream outFile(filename);
        outFile << j.dump(4);
        outFile.close();
    }
};

class LoginPage {
public:
    User login() {
        User existingUser;
        string uname, pwd;
        json j;
        string filename = "users.json";

        cout << "Enter username: ";
        cin >> uname;
        cout << "Enter password: ";
        cin >> pwd;

        if (!loadUsersFromJson(filename, j)) {
            cout << "Error loading users.\n";
            return existingUser;
        }

        for (const auto& user : j["users"]) {
            if (user["username"] == uname && user["password"] == pwd) {
                existingUser.setUsername(uname);
                existingUser.setPassword(pwd);
                return existingUser;
            }
        }

        cout << "Invalid username or password.\n";
        return existingUser;
    }

    bool loadUsersFromJson(const string& filename, json& j) {
        ifstream inFile(filename);
        if (!inFile) {
            return false;
        }
        inFile >> j;
        inFile.close();
        return true;
    }
};

// Base class
class Account {
protected:
    string ownerName;
    double balance;

public:
    Account(string name, double initialBalance) : ownerName(name), balance(initialBalance) {}

    void updateAccountBalance(const string& username, double newBalance) {
        string filename = "accounts.json";
        json accountsJson;

        // Load current accounts
        if (!loadAccountsFromJson(filename, accountsJson)) {
            cout << "Failed to load accounts for updating balance." << endl;
            return;
        }

        // Update the specific user's balance
        for (auto& account : accountsJson["accounts"]) {
            if (account["username"] == username) {
                account["balance"] = newBalance;
                break;
            }
        }

        // Save the updated accounts back to the file
        ofstream outFile(filename);
        outFile << accountsJson.dump(4);
        outFile.close();
    }

    virtual void deposit(double amount) {
        balance += amount;
        cout << "Deposited: " << amount << " | New Balance: " << balance << endl;
        updateAccountBalance(ownerName, balance);
    }

    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: " << amount << " | New Balance: " << balance << endl;
            updateAccountBalance(ownerName, balance);
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
public:
    SavingsAccount(string name, double initialBalance)
        : Account(name, initialBalance) {}

    void deposit(double amount) override {
        balance += amount;
        cout << "Deposited: " << amount << "\n New Balance: " << balance << endl;
    }
};

// Function to load accounts from a JSON file
bool loadAccountsFromJson(const string& filename, json& j) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Failed to open the file: " << filename << endl;
        return false;
    }
    inFile >> j;
    inFile.close();
    return true;
}

// Main function
int main() {
    WelcomePage welcomePage;
    SignUpPage signUpPage;
    LoginPage loginPage;
    User currentUser;

    welcomePage.display();
    int choice = welcomePage.getUserChoice();

    if (choice == 1) {
        currentUser = signUpPage.signUp();
    } else if (choice == 2) {
        currentUser = loginPage.login();
    } else {
        cout << "Invalid option selected." << endl;
        return 1;
    }

    if (currentUser.getUsername().empty()) {
        cout << "Login/Sign-Up failed. Exiting..." << endl;
        return 1;
    }

    // Proceed with account operations
    string filename = "accounts.json"; // Ensure this path is correct
    json accountsJson;

    if (!loadAccountsFromJson(filename, accountsJson)) {
        return 1; // Exit if file cannot be opened
    }

    // Assuming we're working with the first account for demonstration
    string name = accountsJson["accounts"][0]["ownerName"];
    double iniBal = accountsJson["accounts"][0]["balance"];

    Account* myAccount = new SavingsAccount(name, iniBal);

    cout << "What do you want to choose?\n1.Deposit\n2.Withdraw\n3.Check Balance\n";
    cin >> choice;
    int modeNum;
    cout<<"Enter the Mode:\n1.Cash\n2.Online\n3.Borrow";
    cin>>modeNum;
    switch (choice) {
    case 1:
        double depositAmount;
        cout << "Enter deposit amount: ";
        cin >> depositAmount;
        myAccount->deposit(depositAmount);
        break;
    case 2:
        double withdrawalAmount;
        cout << "Enter withdrawal amount: ";
        cin >> withdrawalAmount;
        myAccount->withdraw(withdrawalAmount);
        break;
    case 3:
        myAccount->displayBalance();
        break;
    default:
        cout << "Invalid choice" << endl;
        break;
    }

    delete myAccount;

    return 0;
}
