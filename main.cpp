#define _CRTDBG_MAP_ALLOC
#include <string.h>
#include "time.h"

#include <iostream>
#include <cstdlib>
#include <string>

#include "stocksystem.h"

using namespace std;

void PrintMenu();


int main() {
    int choice = 0;
    string inputchoice;
    int asku;
    string inputasku;
    string adesc;
    double aprice;
    string inputaprice;
    int amount;
    string inputamt;
    string ctlg = "";

    StockSystem mystore;

    while (choice != 8) {
        PrintMenu();
        // get the menu choice from standard input
        getline(cin, inputchoice);
        choice = atoi(inputchoice.c_str());

        switch (choice) {
            case 1: // Print balance
                cout << "Funds: $" << mystore.GetBalance() << endl << endl;
                break;
            case 2: // Print catalogue
                ctlg = mystore.GetCatalogue();
                cout << ctlg << endl;
                break;
            case 3: // Add SKU
                cout << "Enter a numeric SKU (will be converted to 5 digits): ";
                getline(cin, inputasku);
                asku = atoi(inputasku.c_str());
                cout << "Enter item description: ";
                getline(cin, adesc);
                cout << "Enter a retail price: $";
                getline(cin, inputaprice);
                aprice = atof(inputaprice.c_str());
                if (mystore.StockNewItem(StockItem(asku, adesc, aprice)))
                    cout << "Successfully added item to catalogue." << endl;
                else
                    cout << "Item not added to catalogue." << endl;
                break;
            case 4: // Edit item description
                cout << "Enter a numeric SKU to edit: ";
                getline(cin, inputasku);
                asku = atoi(inputasku.c_str());
                cout << "Enter item description: ";
                getline(cin, adesc);
                if (mystore.EditStockItemDescription(asku, adesc))
                    cout << "Item successfully updated." << endl;
                else
                    cout << "Item not updated." << endl;
                break;
            case 5: // Edit item price
                cout << "Enter a numeric SKU to edit: ";
                getline(cin, inputasku);
                asku = atoi(inputasku.c_str());
                cout << "Enter a retail price: $";
                getline(cin, inputaprice);
                aprice = atof(inputaprice.c_str());
                if (mystore.EditStockItemPrice(asku, aprice))
                    cout << "Item successfully updated." << endl;
                else
                    cout << "Item not updated." << endl;
                break;
            case 6: // Restock an item
                cout << "Enter a numeric SKU to purchase: ";
                getline(cin, inputasku);
                asku = atoi(inputasku.c_str());
                cout << "Enter a quantity to purchase: ";
                getline(cin, inputamt);
                amount = atoi(inputamt.c_str());
                cout << "Enter the per-unit purchase price: $";
                getline(cin, inputaprice);
                aprice = atof(inputaprice.c_str());
                if (mystore.Restock(asku, amount, aprice))
                    cout << "Item successfully restocked." << endl;
                else
                    cout << "Item not restocked." << endl;
                break;
            case 7: // Sell an item
                cout << "Enter the SKU of item to sell: ";
                getline(cin, inputasku);
                asku = atoi(inputasku.c_str());
                cout << "Enter a quantity to sell: ";
                getline(cin, inputamt);
                amount = atoi(inputamt.c_str());
                if (mystore.Sell(asku, amount))
                    cout << "Transaction complete. Have a nice day." << endl;
                else
                    cout << "Item is out of stock. Sorry!" << endl;
                break;
            case 8: // Quit
                // no need to do anything, will cause while loop to break
                break;
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    }
    return 0;
}

void PrintMenu() {
    cout << "****************************************************\n"
            << "* Please select an option:                         *\n"
            << "* 1. Print balance             6. Restock an item  *\n"
            << "* 2. Print catalogue           7. Sell an item     *\n"
            << "* 3. Add a new SKU                                 *\n"
            << "* 4. Edit item description                         *\n"
            << "* 5. Edit item price           8. Quit             *\n"
            << "****************************************************\n" << endl;
    cout << "Enter your choice: ";
}