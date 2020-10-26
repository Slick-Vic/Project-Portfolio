#include "Gameplay.h"

Gameplay::Gameplay(shared_ptr<Player> PLAYER)
    : player(PLAYER)
{
    //introduction to the story and the game
    cout << "Welcome to Halloweentown, Jack Skellington!" << endl << endl;
    cout << "Unsurprisingly, with Halloween upcoming, Ooogie Boogie and his minions have begun causing mayhem!  Please help us defeat him!" << endl << endl;
    cout << "In order to defeat Oogie Boogie, you must first train to defeat his minions: Lock, Shock, and Barrel.  To become strong enough, you must first build up your strength by training against lesser enemies." << endl << endl;
    cout << "No one in town seems to know where Lock, Shock, and Barrel are hidden, but there are rumors of a witch hidden deep in Easter Forest that may know where to look..." << endl << endl;

    mp = new Map();

    gameplayLoop();
}

//loop for the game
void Gameplay::gameplayLoop() {
    int seconds = 0;
    int minutes = 0;
    int hours = 0;
    auto t1 = high_resolution_clock::now();

    Shopkeeper s(*player);
    s.addToInventory({ make_shared<Potion>("Potion", 30, 10), make_shared<Potion>("Hyper Potion", 50, 100), make_shared<Boost>("Attack Boost", 10, 500, "ATK"), make_shared<Boost>("Defense Boost ", 10, 500, "DEF"), make_shared<Boost>("HP Boost", 10, 500, "MAXHP") });
    //before the miniboss has been beat there is one loop
    while (!beatLock && !end) {
        cout << endl << endl;
        menu(s);
        cout << endl;
    }
    if (!end) {
        //after the miniboss has been beaten there is another loop
        cout << "Oh no! While you were fighting with Lock, Shock, and Barrel," <<
            "Oogie Boogie kidnapped Sally! Go save her!" << endl;
        s.clearInventory();
        s.addToInventory({ make_shared<Potion>("Hyper Potion", 50, 100), make_shared<Potion>("Hyper Potion", 50, 100), make_shared<Boost>("Mega Attack Boost", 20, 1000, "ATK"), make_shared<Boost>("Mega Defense Boost ", 20, 1000, "DEF"), make_shared<Boost>("Mega HP Boost", 20, 1000, "MAXHP") });
        while (!beatOB && !end) {
            cout << endl << endl;
            menu(s);
        }
        if (!end) {
            cout << "Oogie Boogie says \"I can't believe you defeated me ...\" and he returns Sally to you" << endl;

            cout << "Sally says \"You're my hero, Jack!~~~\"" << endl;

            cout << "And Zero gives you a lick on the face!" << endl;

            cout << "All the villagers in Halloweentown cheer as you return with Sally and they all begin to look forward to the Halloween plans!" << endl << endl;

            cout << "Your final stats: " << endl;
            cout << *player << endl;

            string choice;
            cout << "Continue Playing? (Y/N): ";
            checkYNInput(choice);

            while (choice == "Y") {
                menu(s);
            }
        }

        auto t2 = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(t2 - t1).count();
        auto secondsDuration = duration / 1'000'000;
        auto minutesDuration = secondsDuration / 60;
        secondsDuration = secondsDuration % minutesDuration;
        duration /= 60'000'000;
        cout << "Time spent playing: ";
        cout << minutesDuration << " minutes and "
            << secondsDuration << " seconds!" << endl;
    }
}


//menu and gameplay before the miniboss is beaten
void Gameplay::menu(Shopkeeper& s) {
    cout << "You are currently level " << this->player->getStat("LVL") << endl;
    if (!beatOB) {
        if (beatLock) {
            cout << "Oogie Boogie is level 15" << endl;
            cout << "1. Go searching in the Thanksgiving Forest!" << endl;
            cout << "2. Go to the Shopkeeper" << endl;
            cout << "3. Fight Oogie Boogie" << endl;
        }
        else {
            cout << "Lock, Shock, and Barrel are level 5." << endl;
            cout << "What would you like to do?" << endl;
            cout << "1. Go searching in the Easter Forest!" << endl;
            cout << "2. Go to the Shopkeeper" << endl;
            cout << "3. Fight Lock, Shock and Barrel" << endl;
        }

        cout << "4. View/Use your items" << endl;
        cout << "5. View your stats" << endl;
        cout << "6. Pet Zero" << endl;
        cout << "7. Go on a date with Sally" << endl;
        cout << "8. Exit game" << endl;
    }
    else {
        mp->reset();

        cout << "1. Go searching in the Thanksgiving Forest!" << endl;
        cout << "2. Go searching in the Easter Forest!" << endl;
        cout << "3. Go to the Shopkeeper" << endl;
        cout << "4. View/Use your items" << endl;
        cout << "5. View your stats" << endl;
        cout << "6. Pet Zero" << endl;
        cout << "7. Go on a date with Sally" << endl;
        cout << "8. Exit game" << endl;
    }

    string input;
    cin >> input;
    //checks the user input

    while (input > "8" || input < "1") {
        cerr << "Invalid Response. Try again: ";
        cin >> input;
    }

    int choice = stoi(input);

    if (beatOB) {
        if (choice == 2) {
            choice = 1;
        }
        else if (choice == 3) {
            choice = 2;
        }
        else if (choice == 2) {
            choice = 1;
        }
    }

    switch (choice) {
    case 1: {
        //allows the player to search the forest for different things
        searchForest();
        break;
    }
    case 2: {
        // visit shopkeeper
        s.greet();
        break;
    }
    case 3: {
        int exp, level;

        //initialize Boss fight
        if (!beatLock) {
            if (mp->witchFound())
            {
                exp = player->getStat("EXP");
                level = player->getStat("LVL");
                initializeFight(1);

                if (exp < player->getStat("EXP") || level < player->getStat("LVL"))
                {
                    beatLock = true;
                    mp->reset();
                }
            }
            else {
                cout << "You don't know where Lock, Shock, and Barrel are! Maybe the witch hidden in Easter Forest can help you find them..." << endl;
            }
        }
        else {
            //initialize fight with BIG boss
            cout << "Initializing fight with oogie boogie" << endl;
            exp = player->getStat("EXP");
            level = player->getStat("LVL");
            initializeFight(2);
            if (exp < player->getStat("EXP") || level < player->getStat("LVL")) {
                beatOB = true;
            }
        }
        break;
    }
    case 4: {
        //displays the inventory and allows the player to use an item if they want
        player->useItem();
        cout << endl;
        break;
    }
    case 5:
        //prints out player stats
        cout << *player << endl;
        cout << endl;
        break;
    case 7:
        goOnDate();
        cout << endl;
        break;
    case 6:
        printZero();
        cout << endl;
        break;
    case 8:
        end = true;
        cout << "Exiting game menu...\n";
        return;
    default:
        cout << "Please enter a valid option" << endl;
    }
}


//searching the forest before the miniboss --> different monsters and chances of things occuring 
void Gameplay::searchForest() {
    string direction;
    string choice = "Y";

    do {
        cout << *mp << endl;
        cout << "Enter the direction would you like to head in (left/right/up/down): ";
        cin >> direction;

        mp->movePos(direction[0]);

        if (mp->encounter()) {

            if (mp->witchFound() && !witchEvent) {
                witchEncounter();
                return;
            }
            auto dn = high_resolution_clock::now().time_since_epoch();

            int chance = 1 + rand() % 100;

            //find treasure or healer encounter
            if (chance % 5 == 0) {
                //chance to find treasure
                if (chance % 10 == 0) {
                    printChest();
                    cout << "You stumble upon a treasure chest...do you open it?(Y/N)" << endl;
                    checkYNInput(choice);
                    if (choice == "Y") {
                        //open a treasure chest
                        cout << "You open the chest and find...." << endl;

                        int itemFound = rand() % 3;
                        //chance of finding a regular potion
                        if (itemFound == 0) {
                            shared_ptr<Potion> potion = make_shared<Potion>("Potion", 30, 10);
                            cout << "a potion!" << endl;
                            player->addInv(potion);
                            //chance of finding some pumpkin seeds
                        }
                        else if (itemFound == 1) {
                            int numPumpkinSeeds = rand() % 100 + 20;
                            cout << numPumpkinSeeds << " pumpkin seeds!" << endl;
                            player->getStat("MONEY") += numPumpkinSeeds;
                            //small chance of finding a super nice hyper potion
                        }
                        else {
                            cout << "a hyper potion!" << endl;
                            shared_ptr<Potion> hyperPotion = make_shared<Potion>("Hyper Potion", 30, 10);
                            player->addInv(hyperPotion);
                        }
                    }
                    else {
                        cout << "You leave the treasure chest behind...never knowing what was in it..." << endl;
                    }
                }

                //chance of healer encounter
                else {
                    healerEncounter();
                }
            }
            //Chance to find nothing
            else if (chance % 6 == 0) {
                cout << "You find nothing in your search..." << endl;
            }
            //chance to find a mimic
            else if (chance % 8 == 0) {
                printChest();
                cout << "You stumble upon a treasure chest...do you open it?(Y/N)" << endl;
                checkYNInput(choice);
                if (choice == "Y") {
                    cout << "Oh no! This treasure chest was a mimic!!" << endl;
                    initializeFight(9);
                }
                else if (choice == "N") {
                    cout << "You leave the treasure chest behind...never knowing what was in it..." << endl;
                }
            }
            //random battle
            else {
                int random = rand() % 3;

                //Mid-tier Monsters spawn after 1st Boss battle
                if (beatLock) {
                    random += 6;
                    if (beatOB) {
                        random = rand() % 10;
                    }
                }
                //Weak-tier Monsters
                else {
                    random += 3;
                }
                initializeFight(random);
            }

            cout << "Would you like to continue exploring? (Y/N)" << endl;
            checkYNInput(choice);
        }
        else {
            if (mp->getMap()[mp->getPos('x') + 10 * mp->getPos('y')] == 'T') {
                choice = "N";
            }
        }
    } while (choice == "Y");

    //Go back home on the map...
    mp->home();
}

//prints out the chest
void Gameplay::printChest() {
    cout << R"(                     .,,****,,,***,.                                            
                   ,//*,.,*/(((((/((((/,.                                       
                ,*(*,.,/((((((((//////////((/*,.                                
              .*/*,.*(#((////////(((((////////(((//*,.                          
             ,*(,,,/((/((((((/////////((((((/////*,,,,,*//,.                    
            .//,,*((((((///////(((((////////*,...,/(((((((####(/*.              
           .*/*,*/#(((((((((((/////((((((/,...*/(((((###%%%%%%%%%%#(,           
            ,/*,/(#((((((////((((((////*,..,/(((((##%%%%%##%%%%##%%%%(.         
             ,***/####(*.,*/(((((((((/*,.,/((/((#%%%#%%%%##%%%###%%%%%#*        
              .**/((((//***/##((((((/,,,*(#(((##%%%##%%%%##%%%%%%%%%%%%/.       
                ,*/(#(((////(#####(/,,,*((((##%%%%%%#%%%%%%%%%%%%%%%%#/.        
                 ,/((((####((((((((/*,*(##(##%%%%%%%%%%%%%%%%%%####%#*          
                  .*(#(((((((#((((((/,*/####%%%%%%%%%#########%%%%%#,           
                   ,/(((((##((((((#((***(((##%########%%%%%%%%%%%%(,            
                     .,/###((((###(((/**((###%%%%%%%%%%%%%%%%%%%%/,             
                         .,*/(##(((##(/*/(###%%%%%%%%%%%%%%%%#%#/.              
                              .*/((((#/**(###%%%%%%%%%%%#%%%%%#/....            
                                   ,/##(*/((##%%####%%%%%#(/*,....              
                                      .,*/(##%%%%#((/*,,..                      
                                           .,**,,..                             
                                                                )" << endl;

}

//checks the user input if it is yes or no in certain situations
void Gameplay::checkYNInput(string& choice) {
    cin >> choice;
    transform(choice.begin(), choice.end(),
        choice.begin(), ::toupper);

    while (choice != "Y" && choice != "N") {
        cout << "Invalid choice...Choose again: ";
        cin >> choice;
        transform(choice.begin(), choice.end(),
            choice.begin(), ::toupper);
    }
}

//displays the healer encounter and allows the player to make a choice of whether or not to get assisted
void Gameplay::healerEncounter() {
    cout << "You find a strange woman mixing a potion..." << endl;
    cout << "She offers you assistance in your journey, will you take it?(Y/N)" << endl;
    string choice;
    checkYNInput(choice);
    if (choice == "Y") {
        cout << "She offers you a potion and you take it.  You feel much better!" << endl;
        player->resetHP();
    }
    else {
        cout << "You walk away from the sketchy woman..." << endl;
    }
}

//takes in the monster choice and initializes the battle
void Gameplay::initializeFight(int monsterLevel) {
    shared_ptr<Monster> monster = make_shared<Monster>(monsterLevel);
    BattleView bvMonster(player, monster);
    bvMonster.startBattle();

}

//Like all good RPGs - this is the dating mini-game
void Gameplay::goOnDate() {
    if (beatOB || !beatLock) {
        cout << "You decide to take Sally to the fair!" << endl;
        if (player->getStat("MONEY") < 20) {
            cout << "You don't really have the pumpkin seeds to be taking her out on a date..." << endl;
            cout << "You cannot do much on your date, so you just walk around with her" << endl;
            cout << "She has an okay time" << endl;
            return;
        }
        cout << "You decide to show off your luck at the Guessing Game!" << endl;
        cout << "You approach the Carnival worker..." << endl;
        cout << "They say: " << endl;
        cout << "Welcome, welcome! Come test your luck at the guessing game for the low, low price of 20 pumpkin seeds!  The rules are simple, I will choose a number between one and five, all you have to do is guess correctly! " << endl << endl;

        cout << "Would you like to play? (Y/N)" << endl;
        string choice;
        checkYNInput(choice);
        if (choice == "Y") {
            cout << "I'm glad you've decided to play!  Thank you for the 20 pumpkin seeds!" << endl << endl;
            player->getStat("MONEY") -= 20;
            cout << "I'm thinking of a number between one and five...what is it?" << endl;
            int randomNumber = rand() % 5 + 1;

            int guess;
            cin >> guess;
            if (guess == randomNumber) {
                cout << "Correct!  You win 100 pumpkin seeds!" << endl;
                player->getStat("MONEY") += 100;
                cout << "Sally is VERY impressed with your guessing skills and has thoroughly enjoyed your date!" << endl;
            }
            else {
                cout << "Heh heh heh, sorry, buddy, unlucky guess...the number I was thinking of was " << randomNumber << endl;
                cout << "Sally is pretty unimpressed with your \"guessing skills\" ... better luck next time!" << endl;
            }
        }
        else {
            cout << "You and Sally go on a few rides and have a good time...You think she would have been more impressed had you won the guessing game..." << endl;
        }
    }
    else {
        cout << "Cannot go on a date with Sally. You must save her first!" << endl;
    }

}

void Gameplay::witchEncounter() {
    cout << "After searching through the forest for quite some time, you stumble upon a small hut." << endl;
    cout << "You recall this may be the hut that the villagers in Halloweentown were discussing." << endl;
    cout << "You knock on the door...a witch answers..." << endl;
    cout << "I've been expecting you...I've heard that Oogie Boogie is back and has been causing trouble.  I have heard that Lock, Shock, and Barrel have been hiding in a cave right outside of Halloweentown.  You may be able to find them there. I think I have an item that may assist you in your journey" << endl << endl;
    cout << "The witch hands you some armor...Looks like this may provide you additional protection!" << endl;
    cout << "You go home witht he armor in hand..." << endl;

    player->addInv(make_shared<Armor>("Spooky Armor", 40, 50));

    witchEvent = !witchEvent;
}


//We now pass the can you pet the dog test
void Gameplay::printZero() {
    cout << R"(@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@    %@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&
@@@@.   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&
@@@@@@(@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@
@@@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  %@@@@@@@@@@@@@@@@@@@@
@@@@@@@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@         .@@@@@@@#  @@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@@@@@    ((               #@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@   &@@@@@@@@@@@@@@@@@@@@  &@@@@@@@@@@        .@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@            @@@@@@   @@@@@@@@@@(.  *@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%
@@@@@@@@@@@@@              @@@&  ,@@             @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%
@@@@@@@@@@@@@@@@*        @@@@@@*   %@@@@@@,     (@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@%            *@@@@@@@@@   .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%
@@@@@@@@@@@@@@@@@@@@@@& @@@@@@/ @@@@@@@@@&   @@@@@@@*       @@@@@@@@@@@@@@@@@@@%
@@@@@@@@@@@@@@@@@@@@.@@@@@   *&*@@@@@@@@@   /@@@@     .@@@@.@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@ @@@.  ,@@  %@   ,@@@@@@         %@@@@@@@@@@@@@@@@@@*     *@@@&
@@@@@@@@@@@# %/   #@@@@@@@@@   (      ,@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ##.       @&
@@@@@@@@@@@@@@@@@@@@@@@@@@@     /.        /@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@     #@
@@@@@@@@@@@@@@@@@@@@@@@@@@@     @ @           /@@@@@@@@@@@@@@@@@@@@@@@@@@      @
@@@@@@@@@@@@@@@@@@@@@@@@@@@      %  @              @@@@@@@@@@@@@@@@@@@@       ,@
@@@@@@@@@@@@@@@@@@@@@@@@@@&      (    @                    (@@@@@@@@,         @@
@@@@@@@@@@@@@@@@@@@@@@@@@@&       @                 @           ,            @@&
@@@@@@@@@@@@@@@@@@@@@@@@@@@       @                    @@            @@@(  &@@@&
@@@@@@@@@@@@@@@@@@@@@@@@@@@       @               %                  .@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@      @                *      @@@@@       @@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@&       .               *    @@@@@@@@/    @@@@@@@@@&
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*    @@@@@@                &@@@@@@@@@@@@@@@@@@@@@@&
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,  /@@@@@@@@@             @@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ *@@@@@@@@@@@@          @@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.@@@@@@@@@@@@@@@@(#@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@)" << endl;

    cout << "You pet Zero making them very happy!" << endl;
}

Gameplay::~Gameplay() {
    delete mp;
    mp = nullptr;
}