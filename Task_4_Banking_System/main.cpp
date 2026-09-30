#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <ctime>
#include <sstream>

using namespace std;

class Transaction {
private:
    string type;
    double amount;
    string description;
    string date;

public:
    Transaction(
        const string& type,
        double amount,
        const string& description
    ) {
        this->type = type;
        this->amount = amount;
        this->description = description;

        time_t now = time(nullptr);
        tm* localTime = localtime(&now);

        stringstream ss;

        ss << setfill('0')
           << setw(2) << localTime->tm_mday << "/"
           << setw(2) << localTime->tm_mon + 1 << "/"
           << localTime->tm_year + 1900;

        date = ss.str();
    }

    void display() const {
        cout << left
             << setw(15) << type
             << setw(12) << fixed << setprecision(2) << amount
             << setw(18) << date
             << description << endl;
    }
};


class Customer {
private:
    int customerId;
    string name;
    string phone;

public:
    Customer(
        int customerId,
        const string& name,
        const string& phone
    ) {
        this->customerId = customerId;
        this->name = name;
        this->phone = phone;
    }

    int getId() const {
        return customerId;
    }

    string getName() const {
        return name;
    }

    string getPhone() const {
        return phone;
    }

    void display() const {
        cout << "\nCustomer ID: " << customerId << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
    }
};


class Account {
private:
    long long accountNumber;
    int customerId;
    double balance;
    vector<Transaction> transactions;

public:
    Account(
        long long accountNumber,
        int customerId
    ) {
        this->accountNumber = accountNumber;
        this->customerId = customerId;
        balance = 0.0;
    }

    long long getAccountNumber() const {
        return accountNumber;
    }

    int getCustomerId() const {
        return customerId;
    }

    double getBalance() const {
        return balance;
    }

    bool deposit(double amount) {

        if (amount <= 0)
            return false;

        balance += amount;

        transactions.emplace_back(
            "Deposit",
            amount,
            "Money deposited"
        );

        return true;
    }

    bool withdraw(double amount) {

        if (amount <= 0 || amount > balance)
            return false;

        balance -= amount;

        transactions.emplace_back(
            "Withdrawal",
            amount,
            "Money withdrawn"
        );

        return true;
    }

    bool transferOut(double amount) {

        if (amount <= 0 || amount > balance)
            return false;

        balance -= amount;

        transactions.emplace_back(
            "Transfer Out",
            amount,
            "Fund transfer"
        );

        return true;
    }

    void transferIn(double amount) {

        balance += amount;

        transactions.emplace_back(
            "Transfer In",
            amount,
            "Fund received"
        );
    }

    void displayAccount() const {

        cout << "\n========== Account ==========\n";
        cout << "Account Number: "
             << accountNumber << endl;

        cout << "Customer ID: "
             << customerId << endl;

        cout << "Balance: Rs. "
             << fixed << setprecision(2)
             << balance << endl;

        cout << "=============================\n";
    }

    void displayTransactions() const {

        cout << "\n========== Transaction History ==========\n";

        if (transactions.empty()) {
            cout << "No transactions found.\n";
            return;
        }

        cout << left
             << setw(15) << "Type"
             << setw(12) << "Amount"
             << setw(18) << "Date"
             << "Description" << endl;

        cout << string(65, '-') << endl;

        for (const Transaction& transaction : transactions) {
            transaction.display();
        }
    }
};


class BankingSystem {
private:
    vector<Customer> customers;
    vector<Account> accounts;

    int nextCustomerId = 1001;
    long long nextAccountNumber = 10000001;

    Customer* findCustomer(int customerId) {

        for (Customer& customer : customers) {

            if (customer.getId() == customerId)
                return &customer;
        }

        return nullptr;
    }

    Account* findAccount(long long accountNumber) {

        for (Account& account : accounts) {

            if (account.getAccountNumber() == accountNumber)
                return &account;
        }

        return nullptr;
    }

    int readInt(const string& message) {

        int value;

        while (true) {

            cout << message;

            cin >> value;

            if (!cin.fail())
                return value;

            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            cout << "Invalid input. Try again.\n";
        }
    }

    double readAmount(const string& message) {

        double amount;

        while (true) {

            cout << message;

            cin >> amount;

            if (!cin.fail() && amount > 0)
                return amount;

            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            cout << "Enter a valid positive amount.\n";
        }
    }

public:

    void createCustomer() {

        string name;
        string phone;

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        cout << "\n========== Create Customer ==========\n";

        cout << "Enter name: ";
        getline(cin, name);

        if (name.empty()) {
            cout << "Name cannot be empty.\n";
            return;
        }

        cout << "Enter phone: ";
        getline(cin, phone);

        if (phone.empty()) {
            cout << "Phone cannot be empty.\n";
            return;
        }

        int id = nextCustomerId++;

        customers.emplace_back(
            id,
            name,
            phone
        );

        cout << "\nCustomer created successfully.\n";
        cout << "Customer ID: " << id << endl;
    }

    void createAccount() {

        int customerId =
            readInt("Enter Customer ID: ");

        Customer* customer =
            findCustomer(customerId);

        if (customer == nullptr) {
            cout << "Customer not found.\n";
            return;
        }

        long long accountNumber =
            nextAccountNumber++;

        accounts.emplace_back(
            accountNumber,
            customerId
        );

        cout << "\nAccount created successfully.\n";
        cout << "Account Number: "
             << accountNumber << endl;

        cout << "Account Holder: "
             << customer->getName() << endl;
    }

    void depositMoney() {

        long long accountNumber =
            readInt("Enter Account Number: ");

        Account* account =
            findAccount(accountNumber);

        if (account == nullptr) {
            cout << "Account not found.\n";
            return;
        }

        double amount =
            readAmount("Enter deposit amount: Rs. ");

        account->deposit(amount);

        cout << "Deposit successful.\n";
        cout << "New Balance: Rs. "
             << fixed << setprecision(2)
             << account->getBalance()
             << endl;
    }

    void withdrawMoney() {

        long long accountNumber =
            readInt("Enter Account Number: ");

        Account* account =
            findAccount(accountNumber);

        if (account == nullptr) {
            cout << "Account not found.\n";
            return;
        }

        double amount =
            readAmount("Enter withdrawal amount: Rs. ");

        if (!account->withdraw(amount)) {

            cout << "Withdrawal failed.\n";

            if (amount > account->getBalance()) {
                cout << "Insufficient balance.\n";
            }

            return;
        }

        cout << "Withdrawal successful.\n";
        cout << "New Balance: Rs. "
             << fixed << setprecision(2)
             << account->getBalance()
             << endl;
    }

    void transferMoney() {

        long long senderNumber =
            readInt("Enter sender account number: ");

        long long receiverNumber =
            readInt("Enter receiver account number: ");

        if (senderNumber == receiverNumber) {
            cout << "Sender and receiver accounts "
                    "must be different.\n";
            return;
        }

        Account* sender =
            findAccount(senderNumber);

        Account* receiver =
            findAccount(receiverNumber);

        if (sender == nullptr) {
            cout << "Sender account not found.\n";
            return;
        }

        if (receiver == nullptr) {
            cout << "Receiver account not found.\n";
            return;
        }

        double amount =
            readAmount("Enter transfer amount: Rs. ");

        if (!sender->transferOut(amount)) {

            cout << "Transfer failed.\n";

            if (amount > sender->getBalance()) {
                cout << "Insufficient balance.\n";
            }

            return;
        }

        receiver->transferIn(amount);

        cout << "Transfer successful.\n";
        cout << "Sender Balance: Rs. "
             << fixed << setprecision(2)
             << sender->getBalance()
             << endl;
    }

    void showAccount() {

        long long accountNumber =
            readInt("Enter Account Number: ");

        Account* account =
            findAccount(accountNumber);

        if (account == nullptr) {
            cout << "Account not found.\n";
            return;
        }

        Customer* customer =
            findCustomer(account->getCustomerId());

        account->displayAccount();

        if (customer != nullptr) {
            customer->display();
        }
    }

    void showTransactions() {

        long long accountNumber =
            readInt("Enter Account Number: ");

        Account* account =
            findAccount(accountNumber);

        if (account == nullptr) {
            cout << "Account not found.\n";
            return;
        }

        account->displayTransactions();
    }

    void run() {

        while (true) {

            cout << "\n";
            cout << "====================================\n";
            cout << "          BANKING SYSTEM\n";
            cout << "====================================\n";
            cout << "1. Create Customer\n";
            cout << "2. Create Account\n";
            cout << "3. Deposit Money\n";
            cout << "4. Withdraw Money\n";
            cout << "5. Transfer Funds\n";
            cout << "6. View Account\n";
            cout << "7. View Transactions\n";
            cout << "8. Exit\n";
            cout << "====================================\n";

            int choice =
                readInt("Enter your choice: ");

            switch (choice) {

                case 1:
                    createCustomer();
                    break;

                case 2:
                    createAccount();
                    break;

                case 3:
                    depositMoney();
                    break;

                case 4:
                    withdrawMoney();
                    break;

                case 5:
                    transferMoney();
                    break;

                case 6:
                    showAccount();
                    break;

                case 7:
                    showTransactions();
                    break;

                case 8:
                    cout << "Thank you for using the Banking System.\n";
                    return;

                default:
                    cout << "Invalid choice.\n";
            }
        }
    }
};


int main() {

    BankingSystem bank;

    bank.run();

    return 0;
}