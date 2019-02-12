#include <iostream>
#include <fstream>
#include <cctype>
#include <limits>
#include <iomanip>

using namespace std;


const int CHAR_SIZE = 50;

//structure for various Data Types
struct InventoryData
{
    int itemID;
    char itemDescription[CHAR_SIZE];
    int quantity;
    float wholesaleCost;
    float retailCost;
    char dateAdded[CHAR_SIZE];
};

//Function to add records to file
void addToFile()
{
    system("cls");
    InventoryData item;
    char again;

   //open the file
   fstream inventoryFile("inventory.dat", ios::binary|ios::in|ios::out|ios::app);

   //check for errors
    if(!inventoryFile)
    {
        cout << "Error Opening File";
        return;
    }
    //loop to allow multiple entries
    do
    {
        //Enter ID
        cout << "Enter the Item Information: "<<endl;
        cout << "Enter the ID number of the item: ";
        cin >> item.itemID;
        //input validation
        while(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error!"<<endl;
            cout << "Enter the ID number of the item: ";
            cin >> item.itemID;
        }

        //Enter Description
        cin.ignore();
        cout << "Enter a short description of this item: ";
        cin.getline(item.itemDescription, CHAR_SIZE);
        //Input Validation
        while(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error!"<<endl;
            cout << "Enter a short description of this item: ";
            cin.getline(item.itemDescription, CHAR_SIZE);
        }

        //Enter Quantity
        cout <<"Enter the quantity of item no. " << item.itemID << ": ";
        cin >> item.quantity;
        //Input Validation
        while(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error!"<<endl;
            cout <<"Enter the quantity of item no. " << item.itemID << ": ";
            cin >> item.quantity;
        }

        //Enter wholesale cost
        cout << "Enter the wholesale cost of item no. " << item.itemID<<": $";
        cin >>item.wholesaleCost;
        //Input Validation
        while(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error!"<<endl;
            cout << "Enter the wholesale cost of item no. " << item.itemID<<": $";
            cin >>item.wholesaleCost;
        }

        //Enter Retail Cost
        cout << "Enter the retail cost of item no. " <<item.itemID << ": $";
        cin >>item.retailCost;
        //Input Validation
        while(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error!"<<endl;
            cout << "Enter the retail cost of item no. " <<item.itemID << ": $";
            cin >>item.retailCost;
        }

        //Input Date
        cin.ignore();
        cout << "Enter the date in MM/DD/YYYY: ";
        cin.getline(item.dateAdded, CHAR_SIZE);
        //Input Validation
        while(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error!"<<endl;
            cout << "Enter the date in MM/DD/YYYY: ";
            cin.getline(item.dateAdded, CHAR_SIZE);
        }

        cout <<"\n";

        //Write structure to file using instance called item
        inventoryFile.write(reinterpret_cast<char *>(&item), sizeof(item));

        //prompt for repetition
        cout<< "Do you want to enter another item? Enter Y or N: ";
        cin >> again;
        cin.ignore();
        system("cls");

    }while(toupper(again)== 'Y');


    cout << "Inventory file updated. \n";

    //Close file
    inventoryFile.close();
}

//Function to search for a specific record in file
void searchFile()
{
    system("cls");
    InventoryData record;
    int recordSelection;
    char again;

    //open file
    fstream inventoryFile("inventory.dat", ios::binary| ios::in | ios::app);
    //check for error opening
    if(!inventoryFile)
    {
        cout<<"Error Opening File";
        return;
    }

    //set position to end of file
    inventoryFile.seekg(0L, ios::end);

    //evaluate the total number of records
    int numRecords = inventoryFile.tellg()/sizeof(record);

    cout << "The file has "<< numRecords << " records.\n\n";


    //do while loop for repetitions of search
    do
    {
        //Enter selection
        cout << "Enter the record that you would like to display: ";
        cin >>recordSelection;

        //Input Validation
        while(cin.fail()|| recordSelection > numRecords)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error!"<<endl;
            cout << "Enter the record that you would like to display: ";
            cin >>recordSelection;
        }

        //Decrement for subscript values.
        recordSelection--;

        //clear any end of file flags.
        inventoryFile.clear();
        //set file to the beginning
        inventoryFile.seekg(0L, ios::beg);

        //find specified file
        inventoryFile.seekg((sizeof(record)*recordSelection), ios::cur);
        //read file to instance of structure called record
        inventoryFile.read(reinterpret_cast<char *>(&record), sizeof(record));

        //display to user
        cout << "Record no. " <<(recordSelection + 1)<<endl;

        cout << "\nItem ID: " <<record.itemID<<endl;
        cout << "Item Description: "<<record.itemDescription<<endl;
        cout << "Item Quantity: "<<record.quantity<<endl;
        cout << fixed << showpoint;
        cout << setprecision(2);
        cout << "Item Wholesale Cost: $" <<record.wholesaleCost<<endl;
        cout << fixed << showpoint;
        cout << setprecision(2);
        cout << "Item Retail Cost: $" << record.retailCost<<endl;
        cout << "Date Added: " <<record.dateAdded<<endl;

        cout<< "\nWould you like to read another record? Select Y or N: ";
        cin >> again;
        while(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error!"<<endl;
            cout<< "\nWould you like to read another record? Select Y or N: ";
            cin >> again;
        }
        cout<<endl;
    } while(again == 'Y' || again == 'y');
    inventoryFile.close();

}

//A function to total record entries, and display total inventory file
void totalInventories()
{
    system("cls");
    InventoryData record;

    //open file
    fstream inventoryFile("inventory.dat", ios::binary| ios::out | ios::in);
    //check for errors opening
    if(!inventoryFile)
    {
        cout << "Error Opening File";
        return;
    }

    //display the total number of entries
    inventoryFile.seekg(0L, ios::end);
    int numRecords = inventoryFile.tellg()/sizeof(record);

    cout << "The file has "<< numRecords << " records.\n";

    //reset read position
    inventoryFile.clear();
    inventoryFile.seekg(0L, ios::beg);

    inventoryFile.read(reinterpret_cast<char *>(&record), sizeof(record));


    //display inventory list
    cout << "\n\n*****************Inventory List***************\n"<<endl;
    while(!inventoryFile.eof())
    {

        //Display the record
        cout << "Item ID: "<<record.itemID<<endl;
        cout << "Item Description: "<<record.itemDescription<<endl;
        cout << "Item Quantity: "<<record.quantity<<endl;
        cout << "Item Wholesale Cost: " <<record.wholesaleCost<<endl;
        cout << "Item Retail Cost: " << record.retailCost<<endl;
        cout << "Date Added: " <<record.dateAdded<<endl;
        cout <<endl;

        inventoryFile.read(reinterpret_cast<char *>(&record), sizeof(record));

    }

        cout << "End of File."<<endl;
        inventoryFile.close();


}

//A function to change a record in the file
void changeRecord()
{
    system("cls");
    int recordNumber;
    InventoryData record;

    //open file
    fstream inventoryFile("inventory.dat", ios::in|ios::out|ios::binary);
    //check for file open errors
    if(!inventoryFile)
    {
        cout << "Error Opening File";
        return;
    }

    //display total records to user
    inventoryFile.seekg(0L, ios::end);
    int numRecords = inventoryFile.tellg()/sizeof(record);

    cout << "The file has "<< numRecords << " records.\n\n";

    cout << "Which record number do you want to change? ";
    cin >> recordNumber;

    //input validation
    while(cin.fail()|| recordNumber > numRecords)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error!"<<endl;
        cout << "Enter the record that you would like to display: ";
        cin >>recordNumber;
    }

    //decrement for subscript value
    recordNumber = recordNumber - 1;

    //search for specific record
    inventoryFile.seekg(recordNumber*sizeof(record), ios::beg);
    inventoryFile.read(reinterpret_cast<char*>(&record), sizeof(record));

    //display information to user
    cout << "\nCurrent info for Record no. " << (recordNumber + 1)<< ":\n";
    cout << "\nItem ID: " <<record.itemID<<endl;
    cout << "Item Description: "<<record.itemDescription<<endl;
    cout << "Item Quantity: "<<record.quantity<<endl;
    cout << fixed << showpoint;
    cout << setprecision(2);
    cout << "Item Wholesale Cost: $" <<record.wholesaleCost<<endl;
    cout << fixed << showpoint;
    cout << setprecision(2);
    cout << "Item Retail Cost: $" << record.retailCost<<endl;
    cout << "Date Added: " <<record.dateAdded<<endl;

    //prompt new entry. see first function for specific comments on entry of record.
    cout << "\n\nEnter the new data for record no. "<< (recordNumber + 1)<< ":\n";
    cout << "\nEnter the ID number of the item: ";
    cin >> record.itemID;
    while(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error!"<<endl;
            cout << "\nEnter the ID number of the item: ";
            cin >> record.itemID;
        }
    cin.ignore();
    cout << "Enter a short description of this item: ";
    cin.getline(record.itemDescription, CHAR_SIZE);
    while(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error!"<<endl;
        cout << "Enter a short description of this item: ";
        cin.getline(record.itemDescription, CHAR_SIZE);
    }

    cout <<"Enter the quantity of item no. " << record.itemID << ": ";
    cin >> record.quantity;
    while(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error!"<<endl;
        cout <<"Enter the quantity of item no. " << record.itemID << ": ";
        cin >> record.quantity;
    }


    cout << "Enter the wholesale cost of item no. " <<record.itemID<<": $";
    cin >>record.wholesaleCost;
    while(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error!"<<endl;
        cout << "Enter the wholesale cost of item no. " <<record.itemID<<": $";
        cin >>record.wholesaleCost;
    }


    cout << "Enter the retail cost of item no. " <<record.itemID << ": $";
    cin >>record.retailCost;
    while(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error!"<<endl;
        cout << "Enter the retail cost of item no. " <<record.itemID << ": $";
        cin >>record.retailCost;
    }

    cin.ignore();
    cout << "Enter the date in MM/DD/YYYY: ";
    cin.getline(record.dateAdded, CHAR_SIZE);
    while(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error!"<<endl;
        cout << "Enter the date in MM/DD/YYYY: ";
        cin.getline(record.dateAdded, CHAR_SIZE);
    }

    cout <<"\n";

    //set to position
    inventoryFile.seekp(recordNumber * sizeof(record), ios::beg);

    //write new information.
    inventoryFile.write(reinterpret_cast<char *>(&record), sizeof(record));

    cout << "Record has been updated."<<endl;

    inventoryFile.close();

}



bool mainMenu()
{
    system("cls");

    bool ret;
    char choice;
    cout  << "*********Please select an option from below.**********\n"<<endl;
    cout  << " A. Add to inventory"<<endl
          << " B. Display record"<<endl
          << " C. Total inventories"<<endl
          << " D. Change Record"<<endl
          << " E. Quit\n\n"<<endl;

    cout  << " Choice: ";
    cin>>choice;
    choice = toupper(choice);

    switch(choice)
    {
        case 'A' :
            addToFile();
            ret = true;
            break;
        case 'B':
            searchFile();
            ret = true;
            break;
        case 'C':
            totalInventories();
            ret = true;
            break;
        case 'D':
            changeRecord();
            ret = true;
            break;
        case 'F':
            ret = false;
            break;

    }

    return ret;

}
