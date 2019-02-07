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



int main()
{
char choice;
cout  << "Please select an option from below."<<endl;
cout  << "A. Add to inventory"<<endl
      << "B. Display record"<<endl
      << "C. Total inventories"<<endl
      << "E. Change Record\n\n"<<endl;

cout<<"Choice: ";
cin>>choice;

switch(choice)
{
    case 'A' :
        addToFile();
        break;
    case 'B':
       searchFile();
        break;
    case 'C':
        totalInventories();
        break;
    case 'E':
        changeRecord();
        break;

}

    return 0;
}
