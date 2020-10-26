#include "Shopkeeper.h"

//Constructor
Shopkeeper::Shopkeeper(Player& p)
    : mPlayer(p) {

}

//adding item to the shopkeeper's inventory for buying and selling
void Shopkeeper::addToInventory(std::shared_ptr<Item> item) {
    mInventory.push_back(item);
}

//using an initializer list to add items to the shopkeeper's inventory for buying/selling
void Shopkeeper::addToInventory(std::initializer_list<shared_ptr<Item>> items) {
    for (shared_ptr<Item> i : items) {
        mInventory.push_back(i);
    }
}

//empties the shopkeeper's inventory
void Shopkeeper::clearInventory() {
    mInventory.clear();
}

//initializes the shopkeeper interface, presenting the user
//with some options, getting their selection, then executing that selection
void Shopkeeper::greet() {
    bool keepGoing;
    std::cout << "Welcome to my store, Jack!" << std::endl << "What would you like?" << std::endl;

    std::cout << "1. Buy an item" << std::endl;
    std::cout << "2. Sell an item" << std::endl;
    std::cout << "3. Leave" << std::endl;

    int choice = getSelection(1, 3);

    switch (choice) {
    case 1:
        sell();
        break;
    case 2:
        buy();
        break;
    case 3:
        cout << "Come again!" << endl;
        break;
    default:
        cout << "I'm sorry, I didn't quite catch that" << endl;
    }

}

//handles the selection input
int Shopkeeper::getSelection(int min, int max) {
    int choice;

    cin >> choice;
    //checks for valid cin 
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter correct option, or 0 to cancel" << endl;
        cin >> choice;
    }
    try {
        if (choice >= min && choice <= max) {
            return choice;
        }
        else {
            throw invalid_argument("Invalid argument for selection...");
        }
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
    }

    return 0;
}

//displays the shopkeepers inventory and the prices of the item for the player
void Shopkeeper::printInventory() {
    int itemNum = 1;
    std::cout << "-------------------------------" << std::endl;
    for (std::shared_ptr<Item> i : mInventory) {
        std::cout << itemNum++ << ". " << i->getName() << ": " << i->getPrice() << " Pumpkin Seeds" << std::endl;
    }
    std::cout << "-------------------------------" << std::endl;
}

// shopkeeper is buying from player, who is selling
void Shopkeeper::buy() {
    char keepGoing{ 'Y' };
    do {
        std::cout << "What would you like to sell?" << std::endl;
        std::cout << "Press 0 to quit." << std::endl;
        //displays player's inventory to show them what they can trade
        mPlayer.dispInv();

        int choice;
        char confirmation;
        //handles the selection
        choice = getSelection(0, mPlayer.getInventorySize());
        if (choice == 0) return;
        //returns that item
        Item i = mPlayer.getItem(choice);
        //displays the deal the player would be taking
        std::cout << i.getName() << "? I can give you " << i.getPrice() << " Pumpkin Seeds for that. Deal? (Y/N)" << std::endl;

        confirmation = checkYNInput();
        //allows the player the choice to take back their deal
        if (confirmation == 'Y' || confirmation == 'y') {
            std::cout << "Pleasure doing business with you!" << std::endl;
            mInventory.push_back(mPlayer.sellItem(choice));
            std::cout << "Can I get you anything else?" << std::endl;
        }
        else {
            std::cout << "Changed your mind? No worries. Anything else? (Y/N)" << std::endl;
        }

        keepGoing = checkYNInput();
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter correct option, or 0 to cancel" << endl;
            cin >> choice;
        }
    } while (keepGoing == 'Y');
}

//Shopkeeper is selling to player, who is buying
void Shopkeeper::sell() {
    char keepGoing{ 'Y' };
    do {
        std::cout << "What would you like to buy?" << std::endl;
        std::cout << "Press 0 to quit." << std::endl;

        printInventory();

        int choice;
        char confirmation;

        choice = getSelection(0, mInventory.size());

        if (choice == 0) return;

        shared_ptr<Item> i = getItem(choice);

        if (i->getPrice() > mPlayer.getStat("MONEY")) {
            cout << "Sorry, you don't have enough pumpkin seeds for that!" << endl;
            return;
        }

        std::cout << i->getName() << "? I can sell that to you for " << i->getPrice() << " Pumpkin Seeds. Deal? (Y/N)" << std::endl;

        confirmation = checkYNInput();

        if (confirmation == 'Y') {

            std::cout << "Pleasure doing business with you!" << std::endl;
            mPlayer.addInv(i);
            removeItem(choice);

            mPlayer.setMONEY(-i->getPrice());

            std::cout << "Can I get you anything else? (Y/N)" << std::endl;
        }
        else {
            std::cout << "Changed your mind? No worries. Anything else? (Y/N)" << std::endl;
        }

        keepGoing = checkYNInput();
    } while (keepGoing == 'Y');
}

//getter for the item in the shopkeepers inventory
std::shared_ptr<Item> Shopkeeper::getItem(int choice) {
    return mInventory[choice - 1];
}

//removes an item for the shopkeeper's inventory
std::shared_ptr<Item> Shopkeeper::removeItem(int choice) {
    std::shared_ptr<Item> itemPtr = getItem(choice);
    mInventory.erase(mInventory.begin() + (choice - 1));
    return itemPtr;
}

char Shopkeeper::checkYNInput() {
    char choice;
    cin >> choice;
    while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
        cout << "Invalid choice...Choose again: ";
        cin >> choice;
    }
    if (choice == 'y' || choice == 'Y') {
        return 'Y';
    }
    else {
        return 'N';
    }
}