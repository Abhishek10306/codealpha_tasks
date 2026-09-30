# Banking System

A console-based Banking System developed using C++ and Object-Oriented Programming as part of the CodeAlpha C++ Programming Internship.

## Project Overview

This project simulates basic banking operations using classes and objects.

The system allows customers to create accounts, deposit money, withdraw money, transfer funds and view transaction history.

A modern HTML, CSS and JavaScript interface is also included as a frontend demonstration.

## Features

* Customer creation
* Account creation
* Deposit money
* Withdraw money
* Transfer funds
* Balance checking
* Transaction history
* Account information display
* Input validation
* Insufficient balance checking
* Object-Oriented Programming

## Classes

### Customer

Stores customer information:

* Customer ID
* Name
* Phone number

### Account

Stores:

* Account number
* Customer ID
* Balance
* Transaction history

Provides:

* Deposit
* Withdrawal
* Transfer

### Transaction

Stores:

* Transaction type
* Amount
* Date
* Description

### BankingSystem

Manages:

* Customers
* Accounts
* Account searching
* Customer creation
* Account creation
* Banking operations

## Class Relationship

```text
BankingSystem
      |
      +---- Customer
      |
      +---- Account
               |
               +---- Transaction
```

## Banking Operations

### Deposit

```text
New Balance = Current Balance + Deposit Amount
```

### Withdrawal

```text
New Balance = Current Balance - Withdrawal Amount
```

A withdrawal is rejected when the requested amount is greater than the available balance.

### Transfer

```text
Sender Balance   = Sender Balance - Amount
Receiver Balance = Receiver Balance + Amount
```

## Technologies Used

* C++
* Object-Oriented Programming
* HTML
* CSS
* JavaScript

## Files

```text
Task_4_Banking_System/
│
├── main.cpp
├── index.html
└── README.md
```

## How to Run C++

Compile:

```bash
g++ -std=c++17 main.cpp -o banking
```

Run on Linux/macOS:

```bash
./banking
```

On Windows:

```bash
banking.exe
```

## How to Run Web Version

Open:

```text
index.html
```

in a modern web browser.

## Testing

The project handles:

* Customer creation
* Account creation
* Positive deposits
* Positive withdrawals
* Insufficient balance
* Fund transfers
* Same-account transfer prevention
* Invalid account numbers
* Invalid menu input
* Empty customer information
* Transaction history

## Note

This is an educational banking simulation and does not connect to a real bank or financial institution.

It does not process real money or real financial transactions.

## Internship

CodeAlpha C++ Programming Internship

## Author

Abhishek Kumar
