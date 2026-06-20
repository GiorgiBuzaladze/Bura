#include <iostream>
#include <random>
#include <vector>
#include <algorithm>


enum Suit {
	Hearts = 1, Diamonds, Clubs, Spades
};
std::ostream& operator<<(std::ostream& out, const Suit s){
	switch(s){
		case Suit::Hearts: out << "Hearts"; break;
		case Suit::Diamonds: out << "Diamonds"; break;
		case Suit::Clubs: out << "Clubs"; break;
		case Suit::Spades: out << "Spades"; break;
	}
	return out;
}
enum Rank{
	Six = 1, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace
};
std::ostream& operator<<(std::ostream& out, const Rank r){
	switch(r){
		case Rank::Six: out << "Six"; break;
		case Rank::Seven: out << "Seven"; break;
		case Rank::Eight: out << "Eight"; break;
		case Rank::Nine: out << "Nine"; break;
		case Rank::Ten: out << "Ten"; break;
		case Rank::Jack: out << "Jack"; break;
		case Rank::Queen: out << "Queen"; break;
		case Rank::King: out << "King"; break;
		case Rank::Ace: out << "Ace"; break;
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
		out << c.r << " Of " << c.s << std::endl;
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

class Player{
	private:
		Deck currentDeck;
		int currentScore;
		int generalScore;
	public:
	Player(Deck d) : currentDeck(d){
		currentScore = 0;
		generalScore = 0;
		std::cout << "Dealt Deck: " << std::endl;
		for(const auto& card : currentDeck){
			std::cout << card;
		}
	}
	void playCard(){
		Deck playedCards;
		int n;
		std::cout << "How many cards to play: ";
		std::cin >> n;
		std::cout << "Which cards to play: ";
		int input;
		for(int i = 0; i < n; i++){
			std::cin >> input;
			playedCards.push_back(currentDeck[input - 1]);
		}
		std::cout << "Played Cards: " << std::endl;
		for(const auto& card : playedCards){
			std::cout << card;
		}
		playedCards.clear();
		
	}
		
};
//class GameManagementSystem{
//	private:
//		Player playerOne;
//		Player playerTwo;
//}

Deck generateDeck();
Card generateTrumpCard();

int main(){
	
	Card trumpCard = generateTrumpCard();
	std::cout << "Trump Card: " << trumpCard << std::endl;;
	
	Player playerOne(generateDeck());
	playerOne.playCard();
	
	
}
Deck generateDeck(){
	std::mt19937 static gen(std::random_device{}());
	std::uniform_int_distribution<> suitRange(1, 4);
	std::uniform_int_distribution<> rankRange(1, 9);
	
	Deck deck;
	
	
	for(int i = 0; i < 5; i++){
		Card generated = Card(static_cast<Suit>(suitRange(gen)), static_cast<Rank>(rankRange(gen)));
		while(generated.dealt){
			generated = Card(static_cast<Suit>(suitRange(gen)), static_cast<Rank>(rankRange(gen)));
		}
		generated.dealt = true;
		deck.push_back(generated);
		
	}
	
	return deck;
	
	
}
Card generateTrumpCard(){
	std::mt19937 static gen(std::random_device{}());
	std::uniform_int_distribution<> suitRange(1, 4);
	std::uniform_int_distribution<> rankRange(1, 9);
	
	Card trump(static_cast<Suit>(suitRange(gen)), static_cast<Rank>(rankRange(gen)));
	while(trump.dealt){
		trump = Card(static_cast<Suit>(suitRange(gen)), static_cast<Rank>(rankRange(gen)));
	}
	trump.dealt = true;
	
	return trump;
}
