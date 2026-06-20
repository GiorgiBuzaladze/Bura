#include <iostream>
#include <random>
#include <vector>

enum class Suit {
	Hearts, Diamonds, Clubs, Spades
	
};
std::ostream& operator<<(std::ostream& out, Suit s){
		switch(s){
			case Suit::Hearts:
				out << "Hearts";
				break;
			case Suit::Clubs:
				out << "Clubs";
				break;
			case Suit::Diamonds:
				out << "Diamonds";
				break;
			case Suit::Spades:
				out << "Spades";
				break;			
		}
		return out;
	}
enum class Rank {
	Six, Seven, Eight, Nine, Ten,
	Jack, Queen, King, Ace
	
	
};
std::ostream& operator<<(std::ostream& out, Rank r){
		switch(r){
			case Rank::Six:
				out << "Six";
				break;
			case Rank::Seven:
				out << "Seven";
				break;
			case Rank::Eight:
				out << "Eight";
				break;
			case Rank::Nine:
				out << "Nine";
				break;
			case Rank::Ten:
				out << "Ten";
				break;
			case Rank::Jack:
				out << "Jack";
				break;
			case Rank::Queen:
				out << "Queen";
				break;
			case Rank::King:
				out << "King";
				break;
			case Rank::Ace:
				out << "Ace";
				break;								
		}
		return out;
	}

struct Card{
	Suit s;
	Rank r;
};
std::ostream& operator<<(std::ostream& out, const Card& c){
		out << c.r << " Of " << c.s;
		return out;
}

class Player{
	private:
		std::vector<Card> deck;
		int scoreCurrent;
		int scoreGeneral;
	public:
	Player(std::vector<Card> d, int c, int g) : deck(d), scoreCurrent(c), scoreGeneral(g){}
	void displayDeck() const {
		for(int i = 0; i < 5; i++){
			std::cout << deck[i] << std::endl;
		}
	}
	
};

std::vector<Card> generateCards();

int main(){
	Player player1(generateCards(), 0, 0);
	player1.displayDeck();
}
std::vector<Card> generateCards(){
	std::mt19937 static gen(std::random_device{}());
	std::uniform_int_distribution<> suitRange(0, 3);
	std::uniform_int_distribution<> rankRange(0, 8);
	std::vector<Card> generated;
	
	for(int i = 0 ; i < 5; i++){
		generated.push_back(Card{static_cast<Suit>(suitRange(gen)), static_cast<Rank>(rankRange(gen))});
	}
	return generated;
}
