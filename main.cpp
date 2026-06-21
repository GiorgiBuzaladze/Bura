#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <stdexcept>


enum Suit {
	Hearts = 1, Diamonds, Clubs, Spades
};
std::ostream& operator<<(std::ostream& out, const Suit s){
	switch(s){
		case Suit::Hearts: out << "♥"; break;
		case Suit::Diamonds: out << "♦"; break;
		case Suit::Clubs: out << "♣"; break;
		case Suit::Spades: out << "♠"; break;
	}
	return out;
}
enum Rank{
	Six = 1, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace
};
std::ostream& operator<<(std::ostream& out, const Rank r){
	switch(r){
		case Rank::Six: out << "6"; break;
		case Rank::Seven: out << "7"; break;
		case Rank::Eight: out << "8"; break;
		case Rank::Nine: out << "9"; break;
		case Rank::Ten: out << "10"; break;
		case Rank::Jack: out << "J"; break;
		case Rank::Queen: out << "Q"; break;
		case Rank::King: out << "K"; break;
		case Rank::Ace: out << "A"; break;
	}
	return out;
}
struct Card{
	Suit s;
	Rank r;
	bool dealt = false;
	int value;
	
	
	Card(Suit suit, Rank rank) : s(suit), r(rank){
		switch(rank){
		case Rank::Jack: value = 2; break;
		case Rank::Queen: value = 3; break;
		case Rank::King: value = 4; break;
		case Rank::Ten: value = 10; break;
		case Rank::Ace: value = 11; break;
		default: value = 0; break;
		}
	}
	
	
	friend std::ostream& operator<<(std::ostream& out, const Card &c){
		out << c.s << c.r << " ";
		return out;
	}
	bool operator==(const Card& other) const {
		return s == other.s && r == other.r;
	}
	bool operator>(const Card &other) const {
		return s == other.s && r > other.r;
	}
};
typedef std::vector<Card> Deck;
void generateDeck(Deck &initialDeck, int &dealt);
void dealCards(Deck &orderedDeck, Deck &playerHand, int &dealt, int dealCount = 5);
Card generateTrumpCard(Deck &initialDeck, int &dealt);

class Player{
	private:
		Deck currentDeck;
		int currentScore;
		int generalScore;
		int d;
		Deck oDeck;
	public:
	Player(Deck &orderedDeck, int &dealt) : oDeck(orderedDeck), d(dealt){
		dealCards(oDeck, currentDeck, d, 5);
		currentScore = 0;
		generalScore = 0;
		std::cout << "Dealt Deck: " << std::endl;
		for(const auto& card : currentDeck){
			std::cout << card;
		}
	}
	bool selected = false;
	Deck selectedCards;
	void selectCards(){
		int n;
		std::cout << "\nHow many cards to select: ";
		std::cin >> n;
		std::cout << "Which cards to play: ";
		int input;
		for(int i = 0; i < n; i++){
			std::cin >> input;
			selectedCards.push_back(currentDeck[input - 1]);
		}
		selected = true;
		if(std::any_of(selectedCards.begin(), selectedCards.end(),
		[this](const Card &other) 
		{return other.s != selectedCards[0].s;}
		)){
			std::cout << "Selected Cards must have the same Suit!" << std::endl;
			selectedCards.clear();
			selected = false;
			return;
		}
	}
	void playCard(){
		if(selected){
			std::cout << "Played Cards: " << std::endl;
			for(const auto& card : selectedCards){
				std::cout << card;
				currentDeck.erase(std::find(currentDeck.begin(), currentDeck.end(), card));
			}
		}
		else{
			std::cout << "No cards have been selected!" << std::endl;
		}
	}	
	void addCards(){
		try{
			dealCards(oDeck, currentDeck, d, (5 - currentDeck.size()));
			std::cout << "\nCards Added! Current Deck: " << std::endl;
			for(const auto& card : currentDeck){
				std::cout << card << " ";
			}
		}
		catch(std::invalid_argument &error){
			std::cout << error.what() << std::endl;
		}
	}
	
};
//class GameManagementSystem{
//	private:
//		Player playerOne;
//		Player playerTwo;
//}



int main(){
	SetConsoleOutputCP(CP_UTF8);
	
	
	
	int dealt = 0;
	
	Deck initialDeck;
	generateDeck(initialDeck, dealt);
	
	Card trumpCard = generateTrumpCard(initialDeck, dealt);
	std::cout << "Trump Card: " << trumpCard << std::endl;;
	
	Player playerOne(initialDeck, dealt);
	
	while(1 < 5){
		playerOne.selectCards();
		playerOne.playCard();
		playerOne.addCards();
	}
	
	
}
void generateDeck(Deck &initialDeck, int &dealt){
	
	for(int i = 1; i <= 4; i++){
		for(int j = 1; j <= 9; j++){
			initialDeck.push_back(Card(static_cast<Suit>(i), static_cast<Rank>(j)));
		}
	}
	
	std::shuffle(initialDeck.begin(), initialDeck.end(), std::mt19937{std::random_device{}()});
	
}
void dealCards(Deck &orderedDeck, Deck &playerHand, int &dealt, int dealCount){
	try{
		if(dealt == 36){
			throw std::invalid_argument("All the cards have been dealt!");
			return;
		}
		if(dealt + dealCount > 36){
			dealCount = 36 - dealt;
		}	
		for(int i = 0; i < dealCount; i++){
			playerHand.push_back(orderedDeck[dealt]);
			dealt++;
		}
	}
	catch(std::invalid_argument &error){
		throw error;
	}
	
}
Card generateTrumpCard(Deck &orderedDeck, int &dealt){
	Card trump = orderedDeck[0];
	dealt++;
	return trump;
}
