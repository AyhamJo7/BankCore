
/**
 * @file main.cpp
 * @brief Main entry point for the Bank Management System
 * 
 * This file contains the main function that initializes the system
 * and provides the main menu for user role selection.
 */

#include "Hashtable.h"
#include "BST_Tree.h"
#include "admin.h"
#include "staff.h"
#include "customer.h"
#include <iostream>
#include <string>
#include <limits>

/**
 * @brief Initialize the system by loading data from files
 */
void initializeSystem()
{
    Hashtable H;
    BST_Tree T;
    H.starthash();
    T.load_Server();
}

/**
 * @brief Clear the input buffer and handle invalid input
 */
void clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * @brief Display the main menu header
 */
void displayHeader()
{
    std::cout << "\n";
    std::cout << "===================================\n";
    std::cout << "      BANK MANAGEMENT SYSTEM       \n";
    std::cout << "===================================\n\n";
}

/**
 * @brief Display the main menu options
 */
void displayMenu()
{
    std::cout << "Please select your role:\n\n";
    std::cout << "1. Admin\n";
    std::cout << "2. Staff\n";
    std::cout << "3. Customer\n";
    std::cout << "4. Exit\n\n";
    std::cout << "Enter your choice (1-4): ";
}

/**
 * @brief Main function
 * @return Exit status code
 */
int main()
{
    // Initialize the system
    initializeSystem();
    
    int choice = 0;
    
    while (choice != 4)
    {
        // Display header and menu
        displayHeader();
        displayMenu();
        
        // Get user choice
        if (!(std::cin >> choice))
        {
            std::cout << "\nInvalid input. Please enter a number between 1 and 4.\n";
            clearInputBuffer();
            continue;
        }
        
        // Process user choice
        switch (choice)
        {
            case 1:
                admin();
                break;
            case 2:
                staff();
                break;
            case 3:
                customer();
                break;
            case 4:
                std::cout << "\nThank you for using the Bank Management System. Goodbye!\n";
                break;
            default:
                std::cout << "\nInvalid choice. Please enter a number between 1 and 4.\n";
                break;
        }
        
        // Clear the input buffer
        clearInputBuffer();
        
        // Pause before showing the menu again (except when exiting)
        if (choice != 4)
        {
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
        }
    }
    
    return 0;
}
