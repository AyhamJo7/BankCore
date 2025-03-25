/**
 * @file customer.h
 * @brief Customer functionality for the Bank Management System
 * 
 * This file contains the customer interface and functionality for the Bank Management System.
 * Customers can view their account details and transaction history.
 */

#pragma once
#include "BST_Tree.h"
#include "Hashtable.h"
#include <iostream>
#include <string>
#include <limits>
#include <fstream>

/**
 * @brief Clear the input buffer and handle invalid input
 */
void clearCustomerInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * @brief Display the customer menu header
 */
void displayCustomerHeader()
{
    std::cout << "\n";
    std::cout << "===================================\n";
    std::cout << "         CUSTOMER INTERFACE        \n";
    std::cout << "===================================\n\n";
}

/**
 * @brief Display the customer menu options
 */
void displayCustomerMenu()
{
    std::cout << "Please select an option:\n\n";
    std::cout << "1. View Account Details\n";
    std::cout << "2. View Transaction History\n";
    std::cout << "3. Return to Main Menu\n\n";
    std::cout << "Enter your choice (1-3): ";
}

/**
 * @brief View account details for a customer
 * @param t BST_Tree object to search for the account
 * @param h Hashtable object to verify the password
 */
void viewAccountDetails(BST_Tree& t, Hashtable& h)
{
    int accountNumber, password;
    
    std::cout << "\n--- View Account Details ---\n\n";
    
    std::cout << "Enter Account Number: ";
    while (!(std::cin >> accountNumber)) {
        std::cout << "Invalid input. Please enter a number: ";
        clearCustomerInputBuffer();
    }
    
    std::cout << "Enter Password: ";
    while (!(std::cin >> password)) {
        std::cout << "Invalid input. Please enter a number: ";
        clearCustomerInputBuffer();
    }
    
    // Verify account and password
    if (!h.match(accountNumber, password)) {
        std::cout << "\nError: Invalid account number or password!\n";
        return;
    }
    
    // Get account details
    t.load_Server();
    BST_Node* account = t.search(t.Root, accountNumber);
    
    if (account == nullptr) {
        std::cout << "\nError: Account not found!\n";
        return;
    }
    
    // Display account details
    std::cout << "\n--- Account Details ---\n\n";
    std::cout << "Name: " << account->name << "\n";
    std::cout << "Address: " << account->adress << "\n";
    std::cout << "Account Number: " << account->account_number << "\n";
    std::cout << "Balance: " << account->balance << "\n";
}

/**
 * @brief View transaction history for a customer
 * @param t BST_Tree object to search for the account
 * @param h Hashtable object to verify the password
 */
void viewCustomerTransactionHistory(BST_Tree& t, Hashtable& h)
{
    int accountNumber, password;
    
    std::cout << "\n--- Transaction History ---\n\n";
    
    std::cout << "Enter Account Number: ";
    while (!(std::cin >> accountNumber)) {
        std::cout << "Invalid input. Please enter a number: ";
        clearCustomerInputBuffer();
    }
    
    std::cout << "Enter Password: ";
    while (!(std::cin >> password)) {
        std::cout << "Invalid input. Please enter a number: ";
        clearCustomerInputBuffer();
    }
    
    // Verify account and password
    if (!h.match(accountNumber, password)) {
        std::cout << "\nError: Invalid account number or password!\n";
        return;
    }
    
    // Get account details
    t.load_Server();
    BST_Node* account = t.search(t.Root, accountNumber);
    
    if (account == nullptr) {
        std::cout << "\nError: Account not found!\n";
        return;
    }
    
    // Display transaction history
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
 * @brief Customer interface function
 */
void customer()
{
    BST_Tree t;
    Hashtable h;
    int choice = 0;
    
    while (choice != 3)
    {
        displayCustomerHeader();
        displayCustomerMenu();
        
        // Get user choice
        if (!(std::cin >> choice))
        {
            std::cout << "\nInvalid input. Please enter a number between 1 and 3.\n";
            clearCustomerInputBuffer();
            continue;
        }
        
        // Process user choice
        switch (choice)
        {
            case 1:
                viewAccountDetails(t, h);
                break;
            case 2:
                viewCustomerTransactionHistory(t, h);
                break;
            case 3:
                std::cout << "\nReturning to main menu...\n";
                break;
            default:
                std::cout << "\nInvalid choice. Please enter a number between 1 and 3.\n";
                break;
        }
        
        // Pause before showing the menu again (except when exiting)
        if (choice != 3)
        {
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }
}
