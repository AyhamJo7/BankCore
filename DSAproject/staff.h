/**
 * @file staff.h
 * @brief Staff functionality for the Bank Management System
 * 
 * This file contains the staff interface and functionality for the Bank Management System.
 * Staff can view transaction history, transfer money between accounts, withdraw money,
 * and deposit money.
 */

#pragma once
#include "BST_Tree.h"
#include "Hashtable.h"
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <vector>

/**
 * @brief Clear the input buffer and handle invalid input
 */
void clearStaffInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * @brief Display the staff menu header
 */
void displayStaffHeader()
{
    std::cout << "\n";
    std::cout << "===================================\n";
    std::cout << "           STAFF INTERFACE         \n";
    std::cout << "===================================\n\n";
}

/**
 * @brief Display the staff menu options
 */
void displayStaffMenu()
{
    std::cout << "Please select an option:\n\n";
    std::cout << "1. View Transaction History\n";
    std::cout << "2. Transfer Money\n";
    std::cout << "3. Withdraw Money\n";
    std::cout << "4. Deposit Money\n";
    std::cout << "5. Return to Main Menu\n\n";
    std::cout << "Enter your choice (1-5): ";
}

/**
 * @brief View transaction history for an account
 * @param t BST_Tree object to search for the account
 */
void viewTransactionHistory()
{
    int accountNumber;
    
    std::cout << "\n--- Transaction History ---\n\n";
    
    std::cout << "Enter Account Number: ";
    while (!(std::cin >> accountNumber)) {
        std::cout << "Invalid input. Please enter a number: ";
        clearStaffInputBuffer();
    }
    
    std::cout << "\nTransaction History for Account " << accountNumber << ":\n\n";
    
    std::ifstream read("transaction.txt");
    if (!read) {
        std::cout << "Error: Could not open transaction file.\n";
        return;
    }
    
    bool found = false;
    int acc, amount;
    
    while (read >> acc) {
        read >> amount;
        
        if (acc == accountNumber) {
            found = true;
            if (amount > 0) {
                std::cout << "Deposit: +" << amount << "\n";
            } else {
                std::cout << "Withdrawal: " << amount << "\n";
            }
        }
    }
    
    read.close();
    
    if (!found) {
        std::cout << "No transactions found for this account.\n";
    }
}

/**
 * @brief Transfer money between accounts
 * @param t BST_Tree object to perform the transfer
 */
void transferMoney(BST_Tree& t)
{
    int senderAccount, receiverAccount, amount;
    
    std::cout << "\n--- Transfer Money ---\n\n";
    
    std::cout << "Enter Sender Account Number: ";
    while (!(std::cin >> senderAccount)) {
        std::cout << "Invalid input. Please enter a number: ";
        clearStaffInputBuffer();
    }
    
    // Check if sender account exists
    t.load_Server();
    BST_Node* sender = t.search(t.Root, senderAccount);
    if (sender == nullptr) {
        std::cout << "\nError: Sender account number " << senderAccount << " does not exist!\n";
        return;
    }
    
    std::cout << "Enter Receiver Account Number: ";
    while (!(std::cin >> receiverAccount)) {
        std::cout << "Invalid input. Please enter a number: ";
        clearStaffInputBuffer();
    }
    
    // Check if receiver account exists
    BST_Node* receiver = t.search(t.Root, receiverAccount);
    if (receiver == nullptr) {
        std::cout << "\nError: Receiver account number " << receiverAccount << " does not exist!\n";
        return;
    }
    
    std::cout << "Enter Amount to Transfer: ";
    while (!(std::cin >> amount) || amount <= 0) {
        std::cout << "Invalid input. Please enter a positive number: ";
        clearStaffInputBuffer();
    }
    
    // Check if sender has sufficient balance
    if (sender->balance < amount) {
        std::cout << "\nError: Insufficient balance in sender account!\n";
        std::cout << "Current Balance: " << sender->balance << "\n";
        return;
    }
    
    // Confirm transfer
    char confirm;
    std::cout << "\nTransfer " << amount << " from account " << senderAccount << " to account " << receiverAccount << "? (y/n): ";
    std::cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        t.transfer(senderAccount, amount, receiverAccount);
        std::cout << "\nTransfer completed successfully!\n";
        std::cout << "New Balance for Account " << senderAccount << ": " << sender->balance << "\n";
        std::cout << "New Balance for Account " << receiverAccount << ": " << receiver->balance << "\n";
    } else {
        std::cout << "\nTransfer cancelled.\n";
    }
}

/**
 * @brief Withdraw money from an account
 * @param t BST_Tree object to perform the withdrawal
 */
void withdrawMoney(BST_Tree& t)
{
    int accountNumber, amount;
    
    std::cout << "\n--- Withdraw Money ---\n\n";
    
    std::cout << "Enter Account Number: ";
    while (!(std::cin >> accountNumber)) {
        std::cout << "Invalid input. Please enter a number: ";
        clearStaffInputBuffer();
    }
    
    // Check if account exists
    t.load_Server();
    BST_Node* account = t.search(t.Root, accountNumber);
    if (account == nullptr) {
        std::cout << "\nError: Account number " << accountNumber << " does not exist!\n";
        return;
    }
    
    std::cout << "Current Balance: " << account->balance << "\n";
    
    std::cout << "Enter Amount to Withdraw: ";
    while (!(std::cin >> amount) || amount <= 0) {
        std::cout << "Invalid input. Please enter a positive number: ";
        clearStaffInputBuffer();
    }
    
    // Check if account has sufficient balance
    if (account->balance < amount) {
        std::cout << "\nError: Insufficient balance!\n";
        return;
    }
    
    // Confirm withdrawal
    char confirm;
    std::cout << "\nWithdraw " << amount << " from account " << accountNumber << "? (y/n): ";
    std::cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        t.withdraw(accountNumber, amount);
        std::cout << "\nWithdrawal completed successfully!\n";
        std::cout << "New Balance: " << account->balance - amount << "\n";
    } else {
        std::cout << "\nWithdrawal cancelled.\n";
    }
}

/**
 * @brief Deposit money into an account
 * @param t BST_Tree object to perform the deposit
 */
void depositMoney(BST_Tree& t)
{
    int accountNumber, amount;
    
    std::cout << "\n--- Deposit Money ---\n\n";
    
    std::cout << "Enter Account Number: ";
    while (!(std::cin >> accountNumber)) {
        std::cout << "Invalid input. Please enter a number: ";
        clearStaffInputBuffer();
    }
    
    // Check if account exists
    t.load_Server();
    BST_Node* account = t.search(t.Root, accountNumber);
    if (account == nullptr) {
        std::cout << "\nError: Account number " << accountNumber << " does not exist!\n";
        return;
    }
    
    std::cout << "Current Balance: " << account->balance << "\n";
    
    std::cout << "Enter Amount to Deposit: ";
    while (!(std::cin >> amount) || amount <= 0) {
        std::cout << "Invalid input. Please enter a positive number: ";
        clearStaffInputBuffer();
    }
    
    // Confirm deposit
    char confirm;
    std::cout << "\nDeposit " << amount << " into account " << accountNumber << "? (y/n): ";
    std::cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        t.deposit(accountNumber, amount);
        std::cout << "\nDeposit completed successfully!\n";
        std::cout << "New Balance: " << account->balance + amount << "\n";
    } else {
        std::cout << "\nDeposit cancelled.\n";
    }
}

/**
 * @brief Staff interface function
 */
void staff()
{
    BST_Tree t;
    Hashtable h;
    int choice = 0;
    
    while (choice != 5)
    {
        displayStaffHeader();
        displayStaffMenu();
        
        // Get user choice
        if (!(std::cin >> choice))
        {
            std::cout << "\nInvalid input. Please enter a number between 1 and 5.\n";
            clearStaffInputBuffer();
            continue;
        }
        
        // Process user choice
        switch (choice)
        {
            case 1:
                viewTransactionHistory();
                break;
            case 2:
                transferMoney(t);
                break;
            case 3:
                withdrawMoney(t);
                break;
            case 4:
                depositMoney(t);
                break;
            case 5:
                std::cout << "\nReturning to main menu...\n";
                break;
            default:
                std::cout << "\nInvalid choice. Please enter a number between 1 and 5.\n";
                break;
        }
        
        // Pause before showing the menu again (except when exiting)
        if (choice != 5)
        {
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }
}
