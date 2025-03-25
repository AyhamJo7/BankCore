/**
 * @file admin.h
 * @brief Admin functionality for the Bank Management System
 * 
 * This file contains the admin interface and functionality for the Bank Management System.
 * Admins can add, delete, view, and edit accounts, as well as view account passwords.
 */

#pragma once
#include "BST_Tree.h"
#include "Hashtable.h"
#include <iostream>
#include <string>
#include <limits>

/**
 * @brief Clear the input buffer and handle invalid input
 */
void clearAdminInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * @brief Display the admin menu header
 */
void displayAdminHeader()
{
    std::cout << "\n";
    std::cout << "===================================\n";
    std::cout << "           ADMIN INTERFACE         \n";
    std::cout << "===================================\n\n";
}

/**
 * @brief Display the admin menu options
 */
void displayAdminMenu()
{
    std::cout << "Please select an option:\n\n";
    std::cout << "1. Add Account\n";
    std::cout << "2. Delete Account\n";
    std::cout << "3. View All Accounts\n";
    std::cout << "4. View Account Passwords\n";
    std::cout << "5. Edit Account\n";
    std::cout << "6. Return to Main Menu\n\n";
    std::cout << "Enter your choice (1-6): ";
}

/**
 * @brief Add a new account to the system
 * @param t BST_Tree object to add the account to
 */
void addAccount(BST_Tree& t)
{
    std::string name, address;
    int accountNumber, password, balance;
    
    std::cout << "\n--- Add New Account ---\n\n";
    
    std::cout << "Enter Name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    
    std::cout << "Enter Address: ";
    std::getline(std::cin, address);
    
    std::cout << "Enter Account Number: ";
    while (!(std::cin >> accountNumber)) {
        std::cout << "Invalid input. Please enter a number: ";
        clearAdminInputBuffer();
    }
    
    // Check if account already exists
    t.load_Server();
    if (t.search(t.Root, accountNumber) != nullptr) {
        std::cout << "\nError: Account number " << accountNumber << " already exists!\n";
        return;
    }
    
    std::cout << "Enter Password (numeric): ";
    while (!(std::cin >> password)) {
        std::cout << "Invalid input. Please enter a number: ";
        clearAdminInputBuffer();
    }
    
    std::cout << "Enter Initial Balance: ";
    while (!(std::cin >> balance) || balance < 0) {
        std::cout << "Invalid input. Please enter a non-negative number: ";
        clearAdminInputBuffer();
    }
    
    t.add_Account(name, address, accountNumber, password, balance);
    std::cout << "\nAccount created successfully!\n";
}

/**
 * @brief Delete an account from the system
 * @param t BST_Tree object to delete the account from
 * @param h Hashtable object to delete the password from
 */
void deleteAccount(BST_Tree& t, Hashtable& h)
{
    int accountNumber;
    
    std::cout << "\n--- Delete Account ---\n\n";
    
    std::cout << "Enter Account Number: ";
    while (!(std::cin >> accountNumber)) {
        std::cout << "Invalid input. Please enter a number: ";
        clearAdminInputBuffer();
    }
    
    // Check if account exists
    t.load_Server();
    if (t.search(t.Root, accountNumber) == nullptr) {
        std::cout << "\nError: Account number " << accountNumber << " does not exist!\n";
        return;
    }
    
    // Confirm deletion
    char confirm;
    std::cout << "\nAre you sure you want to delete account " << accountNumber << "? (y/n): ";
    std::cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        t.Root = t.delete_Account(t.Root, accountNumber);
        h.delete_password(accountNumber);
        t.update_server(t.Root);
        std::cout << "\nAccount deleted successfully!\n";
    } else {
        std::cout << "\nDeletion cancelled.\n";
    }
}

/**
 * @brief Edit an account in the system
 * @param t BST_Tree object to edit the account in
 * @param h Hashtable object to update the password in
 */
void editAccount(BST_Tree& t, Hashtable& h)
{
    int accountNumber;
    
    std::cout << "\n--- Edit Account ---\n\n";
    
    std::cout << "Enter Account Number: ";
    while (!(std::cin >> accountNumber)) {
        std::cout << "Invalid input. Please enter a number: ";
        clearAdminInputBuffer();
    }
    
    // Check if account exists
    t.load_Server();
    BST_Node* account = t.search(t.Root, accountNumber);
    if (account == nullptr) {
        std::cout << "\nError: Account number " << accountNumber << " does not exist!\n";
        return;
    }
    
    // Display current account details
    std::cout << "\nCurrent Account Details:\n";
    std::cout << "Name: " << account->name << "\n";
    std::cout << "Address: " << account->adress << "\n";
    std::cout << "Account Number: " << account->account_number << "\n";
    std::cout << "Password: " << account->password << "\n";
    std::cout << "Balance: " << account->balance << "\n\n";
    
    // Edit menu
    int choice = 0;
    std::cout << "What would you like to edit?\n";
    std::cout << "1. Name\n";
    std::cout << "2. Address\n";
    std::cout << "3. Password\n";
    std::cout << "4. Cancel\n";
    std::cout << "Enter your choice (1-4): ";
    
    while (!(std::cin >> choice) || choice < 1 || choice > 4) {
        std::cout << "Invalid input. Please enter a number between 1 and 4: ";
        clearAdminInputBuffer();
    }
    
    std::cin.ignore();
    
    switch (choice) {
        case 1: {
            std::string newName;
            std::cout << "Enter new name: ";
            std::getline(std::cin, newName);
            account->name = newName;
            break;
        }
        case 2: {
            std::string newAddress;
            std::cout << "Enter new address: ";
            std::getline(std::cin, newAddress);
            account->adress = newAddress;
            break;
        }
        case 3: {
            int newPassword;
            std::cout << "Enter new password (numeric): ";
            while (!(std::cin >> newPassword)) {
                std::cout << "Invalid input. Please enter a number: ";
                clearAdminInputBuffer();
            }
            account->password = newPassword;
            h.delete_password(accountNumber);
            h.add(accountNumber, newPassword);
            break;
        }
        case 4:
            std::cout << "\nEdit cancelled.\n";
            return;
    }
    
    t.update_server(t.Root);
    std::cout << "\nAccount updated successfully!\n";
}

/**
 * @brief Admin interface function
 */
void admin()
{
    BST_Tree t;
    Hashtable h;
    int choice = 0;
    
    while (choice != 6)
    {
        displayAdminHeader();
        displayAdminMenu();
        
        // Get user choice
        if (!(std::cin >> choice))
        {
            std::cout << "\nInvalid input. Please enter a number between 1 and 6.\n";
            clearAdminInputBuffer();
            continue;
        }
        
        // Process user choice
        switch (choice)
        {
            case 1:
                addAccount(t);
                break;
            case 2:
                deleteAccount(t, h);
                break;
            case 3:
                std::cout << "\n--- All Accounts ---\n\n";
                t.load_Server();
                t.printoinfo(t.Root);
                break;
            case 4:
                std::cout << "\n--- Account Passwords ---\n\n";
                h.displayPasswords();
                break;
            case 5:
                editAccount(t, h);
                break;
            case 6:
                std::cout << "\nReturning to main menu...\n";
                break;
            default:
                std::cout << "\nInvalid choice. Please enter a number between 1 and 6.\n";
                break;
        }
        
        // Pause before showing the menu again (except when exiting)
        if (choice != 6)
        {
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }
}
