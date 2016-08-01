// File:        a4stocksystemdriver.cpp
// Description: Interactive test driver for StockSystem class
//              Only StockSystem functions are tested. You are still responsible
//              for thoroughly testing your RedBlackTree functions
//              using your own test driver or by adding custom code to this driver.

#include <iostream>
#include <cstdlib>
#include <string>
#include <queue>


#include "redblacktree.h"
#include "stocksystem.h"

using namespace std;

// forward declarations
void PrintMenu();
void ExtraTests();

void printBlackSign(bool is_black) {
    if (is_black)
        cout << "*";
    else
        cout << " ";
}

void printNum(int val) {
    if (val < 100)
        cout << " ";
    if (val < 10)
        cout << " ";
    cout << val;
}

void printItem(Node<int>* item) {
    if (item) {
        printNum(item->data);
        printBlackSign(item->is_black);
    } else
        cout << "    ";
}

void printTreeByLevel(Node<int>* node) {
    Node<int>* r = node;
    int level = 0;
    queue<Node<int>*> q1, q2;
    q1.push(r);
    while (q1.size() || q2.size()) {
        queue<Node<int>*>* q = 0;
        queue<Node<int>*>* qq = 0;
        if (q1.size()) {
            q = &q1;
            qq = &q2;
        } else {
            q = &q2;
            qq = &q1;
        }
        cout << "L" << ++level << ": " << endl;
        while (q->size()) {
            Node<int>* item = q->front();
            q->pop();
            if (item) {
                printItem(item);
                cout << " [ ";
                printItem(item->left);
                cout << " , ";
                printItem(item->right);
                if (item->p) {
                    cout << " @ ";
                    printItem(item->p);
                    cout << " | ";
                    if (item == item->p->left) {
                        cout << "---- , ";
                        printItem(item->p->right);
                    } else {
                        printItem(item->p->left);
                        cout << " , ----";
                    }
                }
                cout << " ]" << endl;
                qq->push(item->left);
                qq->push(item->right);
            }
        }
        cout << '\n' << endl;
    }
}



// program entry point

int main() {
    ExtraTests();

    int choice = 0;
    unsigned int asku;
    string adesc;
    double aprice;
    unsigned int amount;
    string ctlg = "";

    StockSystem mystore;

    while (choice != 11) {
        PrintMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush the cin stream including newline

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
                cin >> asku;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter item description: ";
                getline(cin, adesc);
                cout << "Enter a retail price: $";
                cin >> aprice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (mystore.StockNewItem(StockItem(asku, adesc, aprice)))
                    cout << "Successfully added item to catalogue." << endl;
                else
                    cout << "Item not added to catalogue." << endl;
                break;
            case 4: // Edit item description
                cout << "Enter a numeric SKU to edit: ";
                cin >> asku;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter item description: ";
                getline(cin, adesc);
                if (mystore.EditStockItemDescription(asku, adesc))
                    cout << "Item successfully updated." << endl;
                else
                    cout << "Item not updated." << endl;
                break;
            case 5: // Edit item price
                cout << "Enter a numeric SKU to edit: ";
                cin >> asku;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter a retail price: $";
                cin >> aprice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (mystore.EditStockItemPrice(asku, aprice))
                    cout << "Item successfully updated." << endl;
                else
                    cout << "Item not updated." << endl;
                break;
            case 6: // Restock an item
                cout << "Enter a numeric SKU to purchase: ";
                cin >> asku;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter a quantity to purchase: ";
                cin >> amount;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter the per-unit purchase price: $";
                cin >> aprice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (mystore.Restock(asku, amount, aprice))
                    cout << "Item successfully restocked." << endl;
                else
                    cout << "Item not restocked." << endl;
                break;
            case 7: // Sell an item
                cout << "Enter the SKU of item to sell: ";
                cin >> asku;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter a quantity to sell: ";
                cin >> amount;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (mystore.Sell(asku, amount))
                    cout << "Transaction complete. Have a nice day." << endl;
                else
                    cout << "Item is out of stock. Sorry!" << endl;
                break;
            case 8:
                cout << "Enter the SKU for the item to remove: ";
                cin >> asku;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (mystore.GetRecords().Remove(StockItem(asku, "", 0)) == false) {
                    cout << "Sorry. Item not found!!\n";
                } else {
                    cout << "Done!!\n";
                }
                break;
            case 9:
                cout << mystore.GetRecords().Size() << endl;
                break;
            case 10:
                cout << mystore.GetRecords().Height() << endl;
                break;
            case 11: // Quit
                // no need to do anything, will cause while loop to break
                break;
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    }

    return 0;
}

template<class T>
void inOrderPrint(Node<T>* nd, Node<T>* root, string emptyPrint) {
    if (nd != NULL) {
        inOrderPrint(nd->left, root, emptyPrint);
        emptyPrint += nd->data + " || ";
        inOrderPrint(nd->right, root, emptyPrint);
    }

    if (nd == root) {
        for (int i = 0; i < emptyPrint.size(); ++i) {
            cout << emptyPrint[i];
        }
    }
}

int mainn() {
    RedBlackTree<int> myRBT;
    myRBT.Insert(-32);
    myRBT.Insert(-47);
    myRBT.Insert(-71);
    myRBT.Insert(65);
    myRBT.Insert(-51000);
    myRBT.Insert(87);
    myRBT.Insert(82);
    myRBT.Insert(939999);

    myRBT.Remove(65);
    myRBT.Remove(93);

    printTree<int>(myRBT.GetRoot(), myRBT.GetRoot(), myRBT.GetRoot(), 0);

    //printTreeByLevel(myRBT.GetRoot());

    cout << "\n\n\n\n\n";

    string a;
    inOrderPrint<int>(myRBT.GetRoot(), myRBT.GetRoot(), a);

    cout << "\n";


    cin.get();
    return 0;


}

void PrintMenu() {
    cout << "****************************************************\n"
            << "* Please select an option:                         *\n"
            << "* 1. Print balance             6. Restock an item  *\n"
            << "* 2. Print catalogue           7. Sell an item     *\n"
            << "* 3. Add a new SKU             8. Remove an item   *\n"
            << "* 4. Edit item description     9. get size         *\n"
            << "* 5. Edit item price           10. get height      *\n"
            << "*                              11. quit            *\n"
            << "****************************************************\n" << endl;
    cout << "Enter your choice: ";
}

void ExtraTests() {
    // To be implemented later!!
}