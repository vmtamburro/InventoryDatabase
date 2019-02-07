#include <iostream>
#include <fstream>

using namespace std;

struct InventoryData
{
    int itemID;
    string itemDescription;
    int quantity;
    float wholesaleCost;
    float retailCost;
    string dateAdded;
};

void addToFile()
{
    InventoryData item;
    char again;

   fstream inventoryFile("inventory.dat", ios::binary|ios::in|ios::out|ios::app);

    if(!inventoryFile)
    {
        cout << "Error Opening File";
        return;
    }
    do
    {
        cout << "Enter the Item Information: "<<endl;
        cout << "Enter the ID number of the item: ";
        cin >> item.itemID;

        cin.ignore();
        cout << "Enter a short description of this item: ";
        getline(cin, item.itemDescription);

        cout <<"Enter the quantity of item no. " << item.itemID << ": ";
        cin >> item.quantity;

        cout << "Enter the wholesale cost of item no. " << item.itemID<<": $";
        cin >>item.wholesaleCost;

        cout << "Enter the retail cost of item no. " <<item.itemID << ": $";
        cin >>item.retailCost;

        cin.ignore();
        cout << "Enter the date in MM/DD/YYYY: ";
        getline(cin, item.dateAdded);
        cout <<"\n";


        inventoryFile.write(reinterpret_cast<char *>(&item), sizeof(item));

        cout<< "Do you want to enter another item? Enter Y or N: ";
        cin >> again;
        cin.ignore();

    }while(again == 'Y'|| again == 'y');


    cout << "Item added to inventory file. \n";
    inventoryFile.close();


    return;

}

void searchFile()
{
    InventoryData record;
    int recordSelection;
    char again;

    fstream inventoryFile("inventory.dat", ios::binary| ios::in | ios::app);

    if(!inventoryFile)
    {
        cout<<"Error Opening File";
        return;
    }
    inventoryFile.seekg(0L, ios::end);

    int numRecords = inventoryFile.tellg()/sizeof(record);

    cout << "The file has "<< numRecords << " records.\n";



    do
    {
        cout << "Enter the record that you would like to display: ";
        cin >>recordSelection;

        recordSelection--;

        inventoryFile.clear();
        inventoryFile.seekg(0L, ios::beg);

        inventoryFile.seekg((sizeof(record)*recordSelection), ios::cur);

        inventoryFile.read(reinterpret_cast<char *>(&record), sizeof(record));

        cout << "Record no. " <<(recordSelection + 1)<<endl;

        cout << "\nItem ID: " <<record.itemID<<endl;
        cout << "Item Description: "<<record.itemDescription<<endl;
        cout << "Item Quantity: "<<record.quantity<<endl;
        cout << "Item Wholesale Cost: " <<record.wholesaleCost<<endl;
        cout << "Item Retail Cost: " << record.retailCost<<endl;
        cout << "Date Added: " <<record.dateAdded<<endl;

        cout<< "\nWould you like to read another record? Select Y or N: ";
        cin >> again;
        cout<<endl;
    } while(again == 'Y' || again == 'y');

    return;

}

void totalInventories()
{
    InventoryData record;

    fstream inventoryFile("inventory.dat", ios::binary| ios::out | ios::in);

    inventoryFile.seekg(0L, ios::end);
    int numRecords = inventoryFile.tellg()/sizeof(record);

    cout << "The file has "<< numRecords << " records.\n";

    return;

}

void changeRecord()
{
    int recordNumber;
    InventoryData record;

    fstream inventoryFile("inventory.dat", ios::in|ios::out|ios::binary);

    cout << "Which record number do you want to change? ";
    cin >> recordNumber;

    recordNumber = recordNumber - 1;

    inventoryFile.seekg(recordNumber*sizeof(record), ios::beg);
    inventoryFile.read(reinterpret_cast<char*>(&record), sizeof(record));


    cout << "\nCurrent info for Record no. " << (recordNumber + 1)<< ":\n";
    cout << "\nItem ID: " <<record.itemID<<endl;
    cout << "Item Description: "<<record.itemDescription<<endl;
    cout << "Item Quantity: "<<record.quantity<<endl;
    cout << "Item Wholesale Cost: " <<record.wholesaleCost<<endl;
    cout << "Item Retail Cost: " << record.retailCost<<endl;
    cout << "Date Added: " <<record.dateAdded<<endl;


    cout << "\n\nEnter the new data for record no. "<< (recordNumber + 1)<< ":\n";
    cout << "\nEnter the ID number of the item: ";
    cin >> record.itemID;

    cin.ignore();
    cout << "Enter a short description of this item: ";
    getline(cin, record.itemDescription);

    cout <<"Enter the quantity of item no. " << record.itemID << ": ";
    cin >> record.quantity;

    cout << "Enter the wholesale cost of item no. " <<record.itemID<<": $";
    cin >>record.wholesaleCost;

    cout << "Enter the retail cost of item no. " <<record.itemID << ": $";
    cin >>record.retailCost;

    cin.ignore();
    cout << "Enter the date in MM/DD/YYYY: ";
    getline(cin, record.dateAdded);
    cout <<"\n";

    inventoryFile.seekp(recordNumber * sizeof(record), ios::beg);

    inventoryFile.write(reinterpret_cast<char *>(&record), sizeof(record));

    inventoryFile.close();
    return;
}


