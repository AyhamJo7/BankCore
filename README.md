# BankCore - Modern Banking Management System

![BankCore Logo](https://img.shields.io/badge/BankCore-Banking%20Management%20System-blue)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=flat&logo=c%2B%2B&logoColor=white)
![Version](https://img.shields.io/badge/Version-1.0.0-green)

BankCore is a comprehensive banking management system built in C++ that provides a secure and efficient platform for managing bank accounts, transactions, and user roles. The system utilizes advanced data structures like Binary Search Trees (BST) and Hash Tables to ensure optimal performance and data integrity.

## 📋 Table of Contents

- [Features](#features)
- [System Architecture](#system-architecture)
- [Installation](#installation)
- [Usage](#usage)
- [User Roles](#user-roles)
- [Use Cases](#use-cases)
- [Data Structures](#data-structures)
- [Security](#security)
- [Contributing](#contributing)
- [License](#license)

## ✨ Features

- **Multi-User Role System**: Admin, Staff, and Customer interfaces with appropriate access controls
- **Account Management**: Create, view, edit, and delete bank accounts
- **Transaction Processing**: Deposit, withdraw, and transfer funds between accounts
- **Transaction History**: Track and view all account transactions
- **Secure Authentication**: Password-protected access for all users
- **Data Persistence**: All data is stored securely in files for persistence between sessions
- **User-Friendly Interface**: Clear menus and intuitive navigation

## 🏗️ System Architecture

BankCore is built using a modular architecture with the following components:

- **User Interfaces**: Separate interfaces for Admin, Staff, and Customer
- **Data Management**: BST for account storage and Hash Table for password management
- **Transaction Processing**: Secure handling of financial transactions
- **File System**: Persistent storage of account data and transaction history

## 🔧 Installation

### Prerequisites

- C++ compiler (supporting C++11 or later)
- Visual Studio (for Windows users)

### Steps

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/BankCore.git
   cd BankCore
   ```

2. Open the project:
   - **Windows**: Open `DSAproject.sln` in Visual Studio
   - **Linux/Mac**: Compile using your preferred C++ compiler

3. Build the project:
   - **Visual Studio**: Press F7 or select Build > Build Solution
   - **Command Line**: 
     ```bash
     g++ -std=c++11 DSAproject/*.cpp -o BankCore
     ```

4. Run the application:
   - **Visual Studio**: Press F5 or select Debug > Start Debugging
   - **Command Line**: 
     ```bash
     ./BankCore
     ```

## 🚀 Usage

Upon launching BankCore, you'll be presented with a main menu to select your role:

```
===================================
      BANK MANAGEMENT SYSTEM       
===================================

Please select your role:

1. Admin
2. Staff
3. Customer
4. Exit

Enter your choice (1-4):
```

Select the appropriate role and follow the on-screen instructions to navigate the system.

## 👥 User Roles

### Admin

Administrators have full control over the system and can:

- Add new bank accounts
- Delete existing accounts
- View all accounts in the system
- View account passwords (for security purposes)
- Edit account details

### Staff

Staff members can perform day-to-day banking operations:

- View transaction history for any account
- Transfer money between accounts
- Process withdrawals
- Process deposits

### Customer

Customers can access their own account information:

- View their account details (after authentication)
- View their transaction history

## 📝 Use Cases

### Use Case 1: Creating a New Account (Admin)

1. Log in as an Admin
2. Select "Add Account" from the menu
3. Enter customer details (name, address)
4. Specify account number, password, and initial balance
5. The system creates the account and stores the information

### Use Case 2: Transferring Funds (Staff)

1. Log in as Staff
2. Select "Transfer Money" from the menu
3. Enter sender's account number
4. Enter receiver's account number
5. Specify the amount to transfer
6. Confirm the transaction
7. The system updates both accounts and records the transaction

### Use Case 3: Checking Account Balance (Customer)

1. Log in as a Customer
2. Select "View Account Details" from the menu
3. Enter account number and password
4. The system displays account information including current balance

### Use Case 4: Viewing Transaction History (Customer or Staff)

1. Log in as Customer or Staff
2. Select "View Transaction History" from the menu
3. Enter account number (and password if Customer)
4. The system displays all transactions for the account

## 🧮 Data Structures

BankCore utilizes two primary data structures:

### Binary Search Tree (BST)

- Used for storing and managing account information
- Enables efficient searching, insertion, and deletion operations
- Maintains accounts in a sorted order based on account numbers

### Hash Table

- Used for storing and verifying account passwords
- Provides fast authentication
- Implements a simple hashing algorithm for password storage

## 🔒 Security

BankCore implements several security measures:

- Password-protected access for all users
- Role-based access control
- Input validation to prevent invalid data entry
- Confirmation prompts for critical operations (deletions, transfers)

## 🤝 Contributing

Contributions to BankCore are welcome! Here's how you can contribute:

1. Fork the repository
2. Create a feature branch: `git checkout -b feature-name`
3. Commit your changes: `git commit -m 'Add some feature'`
4. Push to the branch: `git push origin feature-name`
5. Submit a pull request

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

---

© 2025 BankCore. All rights reserved.
