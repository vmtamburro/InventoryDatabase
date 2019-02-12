/***************************************************
Write a program that uses a structure to store the
following inventory data in a text file:
    Item ID(unique number)
    Item Description(short text)
    Quantity on Hand
    Wholesale Cost
    Retail Cost
    Date Added to Inventory(day/month/year)

The program should have a menu that allows the user
to perform the following tasks:
    Total Records in the file
    add any new records to the file (added to the end of file)
    Display any record in the file
    Change any record in the file
****************************************************/

#include <iostream>
#include <fstream>
#include "prototype.h"


using namespace std;


bool mainMenu();

int main()
{
    bool ret = true;
    while(ret == true)
    {
        ret = mainMenu();

        if (ret == true)
            system("pause");
    }
    return 0;
}
