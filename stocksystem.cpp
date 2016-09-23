// File:        stocksystem.cpp
// Date:        2016-02-28
// Description: implementation of a StockSystem class 

#include <math.h>
#include <sstream>

#include "stockitem.h"
#include "stocksystem.h"
#include "redblacktree.h"


//************************************
// Method:    StockSystem.
// FullName:  StockSystem::StockSystem.
// Access:    public.   
// Qualifier: : balance(100000.00) (initializing the balance to $1,000,000.00).
// Desc:      Default constructor.
//************************************
StockSystem::StockSystem() : balance(100000.00) {
}



//************************************
// Method:    GetBalance.
// FullName:  StockSystem::GetBalance.
// Access:    public.
// Returns:   double.
// Desc:      Returns the current balance.
//************************************
double StockSystem::GetBalance() {
    return balance;
}



//************************************
// Method:    StockNewItem.
// FullName:  StockSystem::StockNewItem.
// Access:    public.
// Returns:   bool (to make sure that the insertion is done correctly - 
//            it the will return false if an item with the 
//            specified SKU is already in the tree).
// Parameter: StockItem item (the new item to inserted in the
//            catalog).
// Desc:      Adding a new item to the catalog.
//************************************
bool StockSystem::StockNewItem(StockItem item) {
    StockItem temp(item.GetSKU(), item.GetDescription(), item.GetPrice());
    temp.SetStock(0); // Explicitly set the stock to 0, even though it is going to be 0 by default.
    return records.Insert(temp); // Return true only when no item with similar SKU is in the tree already.
}



//************************************
// Method:    EditStockItemDescription.
// FullName:  StockSystem::EditStockItemDescription.
// Access:    public.
// Returns:   bool (to make sure that the editing is done correctly - 
//            it will return false if no item is there with the specified sku).
// Desc:      Edit the description of an item
//            in th tree, and the search will be
//            done using the SKU of that item.
// Parameter: unsigned int itemsku (the item's SKU).
// Parameter: string desc (the description to be changed to in the item).
//************************************
bool StockSystem::EditStockItemDescription(unsigned int itemsku, string desc) {
    StockItem temp(itemsku, "", 0); // Since Stockitem have the < and > operators defined for the SKU of that stock item,
    //   I can make a new Stockitem with the supplied SKU, without caring about what to
    //   put in the description or price (so I put them as an empty string and 0, respectively).
    StockItem* searchData = records.Retrieve(temp);
    if (searchData == NULL) { // If nothing was found, return false.
        return false;
    }
    searchData->SetDescription(desc);
    return true;
}



//************************************
// Method:    EditStockItemPrice.
// FullName:  StockSystem::EditStockItemPrice.
// Access:    public.
// Returns:   bool (to make sure that the editing is done correctly - 
//            it will return false if no item is there with the specified sku).
// Desc:      Edit the price of an item
//            in th tree, and the search will be
//            done using the SKU of that item.
// Parameter: unsigned int itemsku (the item's SKU).
// Parameter: double retailprice (the price to be changed to in the item).
//************************************
bool StockSystem::EditStockItemPrice(unsigned int itemsku, double retailprice) {
    StockItem temp(itemsku, "", 0);
    StockItem* searchData = records.Retrieve(temp);
    if (searchData == NULL) {
        return false;
    }
    searchData->SetPrice(retailprice);
    return true;
}




//************************************
// Method:    Restock.
// FullName:  StockSystem::Restock.
// Access:    public.
// Returns:   bool (to make sure that restocking is done correctly - 
//            it will return false if no item is in the tree with 
//            the passed in SKU, or the balance is not enough).
// Desc:      Purchase a quantity of an item with its unit price
//            if space is available (max 1000), or purchase only
//            the quantity that fits the space available.
// Parameter: unsigned int itemsku (the SKU of the item for to be restocked).
// Parameter: unsigned int quantity (the quantity to purchase).
// Parameter: double unitprice (the price of the item to be purchased).
//************************************
bool StockSystem::Restock(unsigned int itemsku, unsigned int quantity, double unitprice) {

    StockItem* searchData = records.Retrieve(StockItem(itemsku, "", 0));

    if (searchData == NULL) {
        return false;
    }


    // Save the price and the stock for easy access when needed.
    double tempPrice = searchData->GetPrice();
    unsigned int tempStock = searchData->GetStock();


    unsigned int emptySpace = 1000 - tempStock; // Find the space left in the storage so if the
    //  quantity needed is greater than the space available,
    //  then we'll go by the space available only.


    double tempBalanace = balance; // Save the current balance so if not enough balance is available (i.e. after purchase, balance will be < 0 (negative))
    //   then we do not make the purchase, and return false.


    // Find if the quantity need is more or less than the space left in the storage.
    if (quantity < emptySpace) {
        tempBalanace -= quantity * unitprice;
        tempStock += quantity;
    } else {
        tempBalanace -= emptySpace * unitprice;
        tempStock = 1000;
    }

    // Not enough balance.
    if (tempBalanace < 0) {
        return false;
    }

    // If enough, then we make the purchase by modifying the balance (it will be less than the original) and the stock of the item
    //   retrieved.
    balance = tempBalanace;
    searchData->SetStock(tempStock);

    return true;
}



//************************************
// Method:    Sell.
// FullName:  StockSystem::Sell.
// Access:    public.
// Returns:   bool (to make sure that selling is done correctly - it
//            will return false only if no item was found with the passed
//            in SKU).
// Desc:      Sell a quantity of an item, if that quantity is available or otherwise 
//            with what is available, with the item's original price in the catalog.
// Parameter: unsigned int itemsku (the item's SKU).
// Parameter: unsigned int quantity (the quantity of an item to sell).
//************************************
bool StockSystem::Sell(unsigned int itemsku, unsigned int quantity) {
    StockItem* searchData = records.Retrieve(StockItem(itemsku, "", 0));


    if (searchData == NULL) return false;

    double tempPrice = searchData->GetPrice();
    unsigned int tempStock = searchData->GetStock(); // Here, instead of finding the space left to max (1000), we just need the stock left before going out
    //   of stock (i.e. stock == 0). Therefore, we just need the current stock and the original price of the item.

    double tempBalanace = balance; // This might not be needed since the balance will not be negative.


    // Check for the possibility of getting into the out-of-stock situation. If stock is not enough, then we sell only what is available.
    if (quantity < tempStock) {
        tempBalanace += quantity * tempPrice;
        tempStock -= quantity;
    } else {
        tempBalanace += tempStock * tempPrice;
        tempStock = 0;
    }

    // Modify the stock and the balance.
    searchData->SetStock(tempStock);
    balance = tempBalanace;

    return true;
}









