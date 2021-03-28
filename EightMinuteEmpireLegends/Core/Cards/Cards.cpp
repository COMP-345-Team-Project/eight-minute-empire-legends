#pragma once
#include "../pch.h"

#include "Cards.h"

Card::Card(string nameValue, int newArmyValue, int moveArmyValue, int buildCityValue, int destroyArmyValue,
    string firstActionValue, string secondActionValue, bool andActionValue, int extraMoveValue,
    int extraArmyValue, bool flyingValue, int elixerValue, int extraCoinValue, string specialAbilityValue) {
    name = nameValue;
    newArmy = newArmyValue;
    moveArmy = moveArmyValue;
    buildCity = buildCityValue;
    destroyArmy = destroyArmyValue;
    firstAction = firstActionValue; //Order must be dictated as the action must be taken sequencially
    secondAction = secondActionValue;
    andAction = andActionValue;
    extraMove = extraMoveValue;
    extraArmy = extraArmyValue;
    flying = flyingValue;
    elixer = elixerValue;
    extraCoin = extraCoinValue;
    specialAbility = specialAbilityValue;
}

Card::Card() {
    name = "";
    newArmy = 0;
    moveArmy = 0;
    buildCity = 0;
    destroyArmy = 0;
    firstAction = "";
    secondAction = "";
    andAction = false;
    extraMove = 0;
    extraArmy = 0;
    flying = false;
    elixer = 0;
    extraCoin = 0;
    specialAbility = "";

}

Card::~Card() {}

Card::Card(const Card& card) {
    this->name = card.name;
    this->newArmy = card.newArmy;
    this->moveArmy = card.moveArmy;
    this->buildCity = card.buildCity;
    this->destroyArmy = card.destroyArmy;
    this->firstAction = card.firstAction;
    this->secondAction = card.secondAction;
    this->andAction = card.andAction;
    this->extraMove = card.extraMove;
    this->extraArmy = card.extraArmy;
    this->flying = card.flying;
    this->elixer = card.elixer;
    this->extraCoin = card.extraCoin;
    this->specialAbility = card.specialAbility;
}

Card& Card::operator =(const Card& card) {
    this->name = card.name;
    this->newArmy = card.newArmy;
    this->moveArmy = card.moveArmy;
    this->buildCity = card.buildCity;
    this->destroyArmy = card.destroyArmy;
    this->firstAction = card.firstAction;
    this->secondAction = card.secondAction;
    this->andAction = card.andAction;
    this->extraMove = card.extraMove;
    this->extraArmy = card.extraArmy;
    this->flying = card.flying;
    this->elixer = card.elixer;
    this->extraCoin = card.extraCoin;
    this->specialAbility = card.specialAbility;

    return *this;
}

//Print out card's attributes
void Card::print() {
    //Card's Action
    cout << name << " (Action: ";
    printHelper(firstAction);

    //Some cards have 2 actions, either AND or OR
    if (secondAction != "") {
        if (andAction == true) {
            cout << "AND ";
        }
        else {
            cout << "OR ";
        }

        printHelper(secondAction);
    }
    cout << ") ";

    //Card's Ability
    if (extraMove != 0 || extraArmy != 0 || flying == true || elixer != 0 || extraCoin != 0) {
        cout << "(Ability: ";

        if (extraMove != 0) {
            cout << "Extra Move (" << extraMove << ") ";
        }
        if (extraArmy != 0) {
            cout << "Extra Army (" << extraArmy << ") ";
        }
        if (flying == true) {
            cout << "Flying ";
        }
        if (elixer != 0) {
            cout << "Elixer (" << elixer << ") ";
        }
        if (extraCoin != 0) {
            cout << "Extra Coin (" << extraCoin << ") ";
        }
        cout << ") ";
    }

    //Card's Special Ability
    if (specialAbility != "") {
        cout << "(Special Ability: " << specialAbility << ") ";
    }

    cout << "\n";

};

//Utility function for printing car's action string
void Card::printHelper(string str) {
    if (str == "newArmy") {
        cout << "New Army (" << newArmy << ") ";
    }
    else if (str == "moveArmy") {
        cout << "Move Army (" << moveArmy << ") ";
    }
    else if (str == "buildCity") {
        cout << "Build City (" << buildCity << ") ";
    }
    else {
        cout << "Destroy Army (" << destroyArmy << ") ";
    }
};

//Getter
string Card::getName() {
    return name;
}
int Card::getNewArmy() {
    return newArmy;
}
int Card::getMoveArmy() {
    return moveArmy;
}
int Card::getBuildCity() {
    return buildCity;
}
int Card::getDestroyArmy() {
    return destroyArmy;
}
string Card::getFirstAction() {
    return firstAction;
}
string Card::getSecondAction() {
    return secondAction;
}
bool Card::getAndAction() {
    return andAction;
}
int Card::getExtraMove() {
    return extraMove;
}
int Card::getExtraArmy() {
    return extraArmy;
}
bool Card::getFlying() {
    return flying;
}
int Card::getElixer() {
    return elixer;
}
int Card::getExtraCoin() {
    return extraCoin;
}
string Card::getSpecialAbility() {
    return specialAbility;
}


//Deck Implementation

Deck::Deck() {

}

Deck::~Deck() {}

Deck::Deck(int numPlayer) {

    //Card cardSample("Sample", 0, 0, 0, 0, "", "", false, 0, 0, false, 0, 0, "");

    Card* card1 = new Card("Ancient Phoenix", 0, 5, 0, 0, "moveArmy", "", false, 0, 0, true, 0, 0, "");
    Card* card2 = new Card("Ancient Sage", 0, 3, 0, 0, "moveArmy", "", false, 0, 0, false, 0, 0, "1VPperAncient");
    Card* card3 = new Card("Ancient Tree Spirit", 4, 0, 0, 0, "newArmy", "", false, 0, 0, false, 3, 0, "");
    Card* card4 = new Card("Ancient Woods", 1, 0, 1, 0, "buildCity", "newArmy", true, 0, 1, false, 0, 0, "");
    Card* card5 = new Card("Cursed Banshee", 0, 6, 0, 0, "moveArmy", "", false, 0, 0, false, 2, 0, "");
    Card* card6 = new Card("Cursed Gargoyles", 0, 5, 0, 0, "moveArmy", "", false, 0, 0, true, 0, 0, "");
    Card* card7 = new Card("Cursed King", 3, 4, 0, 0, "newArmy", "moveArmy", false, 0, 0, false, 1, 0, "");
    Card* card8 = new Card("Cursed Mausoleum", 0, 0, 1, 0, "buildCity", "", false, 1, 0, false, 0, 0, "");
    Card* card9 = new Card("Cursed Tower", 0, 0, 1, 0, "buildCity", "", false, 0, 0, false, 0, 0, "1VPperFlying");
    Card* card10 = new Card("Dire Dragon", 3, 0, 0, 1, "newArmy", "destroyArmy", true, 0, 0, true, 0, 0, "");
    Card* card11 = new Card("Dire Eye", 4, 0, 0, 0, "newArmy", "", false, 0, 0, true, 0, 0, "");
    Card* card12 = new Card("Dire Giant", 3, 0, 0, 1, "newArmy", "destroyArmy", true, 0, 0, false, 0, 0, "immuneToAttack");
    Card* card13 = new Card("Dire Goblin", 0, 5, 0, 0, "moveArmy", "", false, 0, 0, false, 1, 0, "");
    Card* card14 = new Card("Dire Ogre", 0, 2, 0, 0, "moveArmy", "", false, 0, 0, false, 0, 0, "1VPper3Coins");
    Card* card15 = new Card("Forest Elf", 3, 2, 0, 0, "newArmy", "moveArmy", false, 0, 1, false, 0, 0, "");
    Card* card16 = new Card("Forest Gnome", 0, 2, 0, 0, "moveArmy", "", false, 0, 0, false, 3, 0, "");
    Card* card17 = new Card("Forest Pixie", 0, 4, 0, 0, "moveArmy", "", false, 0, 1, false, 0, 0, "");
    Card* card18 = new Card("Forest Tree Town", 0, 0, 1, 0, "buildCity", "", false, 1, 0, false, 0, 0, "");
    Card* card19 = new Card("Graveyard", 2, 0, 0, 0, "newArmy", "", false, 0, 0, false, 0, 0, "1VPperCursedCard");
    Card* card20 = new Card("Lake", 2, 3, 0, 0, "newArmy", "moveArmy", false, 0, 0, false, 0, 0, "1VPperForestCard");
    Card* card21 = new Card("Night Hydra", 0, 5, 0, 1, "moveArmy", "destroyArmy", true, 0, 1, false, 0, 0, "");
    Card* card22 = new Card("Night Village", 0, 0, 1, 0, "buildCity", "", false, 0, 1, false, 0, 0, "");
    Card* card23 = new Card("Night Wizard", 3, 0, 0, 1, "newArmy", "destroyArmy", true, 0, 0, false, 0, 0, "1VPperNightCard");
    Card* card24 = new Card("Noble Hills", 3, 0, 0, 0, "newArmy", "", false, 0, 0, false, 0, 0, "3NobleCards=4VP");
    Card* card25 = new Card("Noble Knight", 4, 0, 0, 1, "newArmy", "destroyArmy", true, 1, 0, false, 0, 0, "");
    Card* card26 = new Card("Noble Unicorn", 1, 4, 0, 0, "moveArmy", "newArmy", true, 1, 0, false, 0, 0, "");
    Card* card27 = new Card("Stronghold", 0, 0, 1, 0, "buildCity", "", false, 0, 0, false, 0, 0, "1VPperDireCard");
    addCard(card1);
    addCard(card2);
    addCard(card3);
    addCard(card4);
    addCard(card5);
    addCard(card6);
    addCard(card7);
    addCard(card8);
    addCard(card9);
    addCard(card10);
    addCard(card11);
    addCard(card12);
    addCard(card13);
    addCard(card14);
    addCard(card15);
    addCard(card16);
    addCard(card17);
    addCard(card18);
    addCard(card19);
    addCard(card20);
    addCard(card21);
    addCard(card22);
    addCard(card23);
    addCard(card24);
    addCard(card25);
    addCard(card26);
    addCard(card27);

    //For more than 2 players
    if (numPlayer >= 3) {
        Card* card28 = new Card("Arcane Manticore", 4, 0, 0, 1, "newArmy", "destroyArmy", true, 1, 0, false, 0, 0, "");
        Card* card29 = new Card("Arcane Sphinx", 3, 4, 0, 0, "newArmy", "moveArmy", false, 0, 0, true, 0, 0, "");
        Card* card30 = new Card("Arcane Temple", 0, 3, 0, 0, "moveArmy", "", false, 0, 0, false, 0, 0, "1VPperArcaneCard");
        Card* card31 = new Card("Mountain Dwarf", 2, 0, 0, 1, "newArmy", "destroyArmy", true, 0, 0, false, 0, 0, "3VPfor2MountainCards");
        Card* card32 = new Card("Mountain Treasury", 0, 3, 0, 0, "moveArmy", "", false, 0, 0, false, 1, 2, "");
        addCard(card28);
        addCard(card29);
        addCard(card30);
        addCard(card31);
        addCard(card32);
    }

    if (numPlayer == 4) {
        Card* card33 = new Card("Castle", 3, 0, 1, 0, "newArmy", "buildCity", false, 0, 0, false, 1, 0, "");
        Card* card34 = new Card("Castle 2", 0, 3, 1, 0, "moveArmy", "buildCity", true, 0, 0, false, 1, 0, "");
        addCard(card33);
        addCard(card34);
    }

    //Shuffle the cards
    shuffle();
}

Deck::Deck(const Deck& deck) {
    this->deck = deck.deck;
}

Deck& Deck::operator =(const Deck& deck) {
    this->deck = deck.deck;

    return *this;
}

//Add cards into the deck
void Deck::addCard(Card* newCard) {
    deck.push_back(newCard);
}

//Changing the index position of the cards in the deck using random number
void Deck::shuffle() {
    auto rd = std::random_device{};
    auto rng = std::default_random_engine{ rd() };
    std::shuffle(deck.begin(), deck.end(), rng);
}

//Debug function to reveals all cards in deck
void Deck::reveal() {
    cout << "!! This is a debug utility to reveals all cards in deck, cards will be drawn from the back !!" << endl;
    cout << "Current deck size: " << deck.size() << endl;
    for (unsigned i = 0; i < deck.size(); i++) {
        cout << (i + 1) << ". ";
        (*deck[i]).print();
    }
    cout << "\n";
}

//Draw card from deck
Card* Deck::draw() {

    if (deck.size() > 0) {
        Card* tempCard = deck.back();
        cout << "The card drawn from deck is: " << tempCard->getName() << endl;
        deck.pop_back();
        return tempCard;
    }
    else { //If the deck is empty, the card being returned will be named "EMPTY"
        //We should change this to null
        //Card tempEmpty("EMPTY", 0, 0, 0, 0, "newArmy", "", false, 0, 0, false, 0, 0, "");
        return NULL;
    }

}

//Getter
int Deck::getSize() {
    return deck.size();
}

// CardSpace Implementation

// CardSpace is hardcoded to draw 6 cards from deck upon initialization
CardSpace::CardSpace(Deck& mainDeck) {

    std::cout << "Card Space initializing... Six cards will be drawn from the deck" << endl;
    addCard(mainDeck.draw());
    addCard(mainDeck.draw());
    addCard(mainDeck.draw());
    addCard(mainDeck.draw());
    addCard(mainDeck.draw());
    addCard(mainDeck.draw());
    std::cout << "Card Space initialized" << endl;
}

CardSpace::~CardSpace() {}

CardSpace::CardSpace(const CardSpace& cardSpace) {
    this->cardSpace = cardSpace.cardSpace;
}

CardSpace& CardSpace::operator =(const CardSpace& cardSpace) {
    this->cardSpace = cardSpace.cardSpace;

    return *this;
}

//Add new cards into the card space
void CardSpace::addCard(Card* newCard) {
    cardSpace.push_back(newCard);
}

//Print out all cards in CardSpace associated with their current cost for exchange
void CardSpace::showCardSpace() {
    cout << "\n---Cards currently in Card Space--- \n";

    for (unsigned i = 0; i < cardSpace.size(); i++) {
        cout << "(Cost " << costCalc(i) << " coins) " << (i + 1) << ". ";
        (*cardSpace[i]).print();
    }
}

//Utility function for calculating cost of exchange dynamically besed on their current index position
int CardSpace::costCalc(int index) {
    if (index == 0) {
        return 0;
    }
    else if (index == 1 or index == 2) {
        return 1;
    }
    else if (index == 3 or index == 4) {
        return 2;
    }
    else {
        return 3;
    }

}

//Exchange function to allow player to buy cards from hand using coins
//showCardSpace function included for demonstration
Card* CardSpace::exchange(Deck& mainDeck, bool demo = false) {
    int cardInput; //Position from user input
    int cardChoice; //Index position from cardSpace vector
    Card* cardChosen = NULL;

    if (cardSpace.size() > 0) {
        showCardSpace();
        cout << "Choose which card you'd like to exchange (1-6): " << endl;
		
		
		//Handle demo scenario where no user interaction is required
		if (demo == false) {
			
			cin >> cardInput;

			if (cardInput > 0 && cardInput < (cardSpace.size() + 1)) {
				cardChoice = cardInput - 1;
			}
			else {
				cout << "!invalid selection! Default to first free card. \n"; //Exception handler
				cardChoice = 0;
			}
		}
		else{
			
			cout << "!Demo Mode! Default to first free card. \n";
			cardChoice = 0;
		}
		
		//Access the chosen card from the cardSpace
        cardChosen = cardSpace[cardChoice];

        cout << "The card you've selected to exchange is " << cardChosen->getName() << endl;

        //Remove the card chosen from CardSpace and move all cards after it to the left by 1 position
        for (int i = cardChoice; i < (cardSpace.size() - 1); i++) {
            cardSpace[i] = cardSpace[i + 1];
        }
        //Remove the last now supposed to be emptry slot
        cardSpace.pop_back();

        //Draw new card to place into the rightmost position
        Card* cardAdded = mainDeck.draw();

        //Handle when the deck is empty
        if (cardAdded == NULL) {
            cout << "No more new cards from deck" << endl;
        }
        else {
            addCard(cardAdded);
        }

        cout << "Here is the cards in Hand after the exchange" << endl;
        showCardSpace();

        return cardChosen;
    }

    //Return card named "EMPTY" when card space is empty
    else {
        Card tempEmpty("EMPTY", 0, 0, 0, 0, "newArmy", "", false, 0, 0, false, 0, 0, "");
        return NULL;
    }


}

Card* CardSpace::sell(Deck& mainDeck, int cardInput) {
    //Access the chosen card from the cardSpace
    Card* cardChosen;
    cardChosen = cardSpace[cardInput - 1];

    cout << "The card you've selected to buy is " << cardChosen->getName() << endl;

    //Remove the card chosen from Card Space and move all cards after it to the left by 1 position
    for (int i = (cardInput - 1); i < (cardSpace.size() - 1); i++) {
        cardSpace[i] = cardSpace[i + 1];
    }
    //Remove the last now supposed to be emptry slot
    cardSpace.pop_back();

    //Draw new card to place into the rightmost position
    Card* cardAdded = mainDeck.draw();

    //Handle when the deck is empty
    if (cardAdded->getName() == "EMPTY") {
        cout << "No more new cards from deck" << endl;
    }
    else {
        addCard(cardAdded);
    }

    return cardChosen;
}

//Getter
int CardSpace::getSize() {
    return cardSpace.size();
}

vector<Card*> CardSpace::getCards() {
    return cardSpace;
}


