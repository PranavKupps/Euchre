// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <array>
#include "Card.h"
#include <string>

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const RANK_NAMES[] = {
  "Two",   // TWO
  "Three", // THREE
  "Four",  // FOUR
  "Five",  // FIVE
  "Six",   // SIX
  "Seven", // SEVEN
  "Eight", // EIGHT
  "Nine",  // NINE
  "Ten",   // TEN
  "Jack",  // JACK
  "Queen", // QUEEN
  "King",  // KING
  "Ace"    // ACE
};

//EFFECTS Initializes Card to the Two of Spades
Card::Card() {
  rank = static_cast<Rank>(0);
  suit = static_cast<Suit>(0);
}

//EFFECTS Initializes Card to specified rank and suit
Card::Card(Rank rank_in, Suit suit_in) {
  rank = rank_in;
  suit = suit_in;
}

//EFFECTS Returns the rank
Rank Card::get_rank() const {
  return rank;
}

//EFFECTS Returns the suit.  Does not consider trump.
Suit Card::get_suit() const {
  return suit;
}

//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
Suit Card::get_suit(Suit trump) const {
  if(is_left_bower(trump)) {
    return trump;
  } else {
    return suit;
  }
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face_or_ace() const {
  if ((rank == 9 || (rank == QUEEN || rank == KING || rank == ACE))) {
    return true;
  } else {
    return false;
  }
}

//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(Suit trump) const {
  if(suit == trump && rank == JACK) {
    return true;
  } else {
    return false;
  }
}

//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(Suit trump) const {
  if(rank == JACK && Suit_next(trump) == suit) {
    return true;
  } else {
    return false;
  }
}

//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(Suit trump) const {
 if((suit == trump) || (is_left_bower(trump) == true)) {
  return true;
 } else {
  return false;
 }
}

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
Rank string_to_rank(const std::string &str) {
  for(int r = TWO; r <= ACE; ++r) {
    if (str == RANK_NAMES[r]) {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank) {
  os << RANK_NAMES[rank];
  return os;
}

//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank) {
  string str;
  is >> str;
  rank = string_to_rank(str);
  return is;
}



/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
Suit string_to_suit(const std::string &str) {
  for(int s = SPADES; s <= DIAMONDS; ++s) {
    if (str == SUIT_NAMES[s]) {
      return static_cast<Suit>(s);
    }
  }
  assert(false); // Input string didn't match any suit
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit) {
  os << SUIT_NAMES[suit];
  return os;
}

//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit) {
  string str;
  is >> str;
  suit = string_to_suit(str);
  return is;
}


/////////////// Write your implementation for Card below ///////////////
// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card) {
  os << card.get_rank() << " of " << card.get_suit();
  return os; 
}

//   operator>>
//EFFECTS Reads a Card from a stream in the format "Two of Spades"
//NOTE The Card class declares this operator>> "friend" function,
//     which means it is allowed to access card.rank and card.suit.
std::istream & operator>>(std::istream &is, Card &card) {
  string word1, word2, word3;
  is >> word1 >> word2 >> word3;
  card.rank = string_to_rank(word1);
  card.suit = string_to_suit(word3);
  return is;
}

//   operator<
//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs) {
  bool output = false;
  int lhs_value = lhs.get_rank();
  int rhs_value = rhs.get_rank();

  int lhs_suit = lhs.get_suit();
  int rhs_suit = rhs.get_suit();

  if(lhs_value < rhs_value) {
    output = true;
  } else if(lhs_value == rhs_value) {
    if(lhs_suit < rhs_suit) {
      output = true;
    }
  }

  if((lhs_value == rhs_value) & (lhs_suit == rhs_suit)) {
    return false;
  }

  return output;
}

//   operator<=
//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs) {
  if ((lhs == rhs) || (lhs < rhs)) {
    return true;
  } else {
    return false;
  }
}

//   operator>
//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs) {
  return (!(lhs <= rhs));
}

//   operator>=
//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs) {
  return ((lhs == rhs) || (lhs > rhs));
}

//   operator==
//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs) {

  if(lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit()) {
    return true;
  } else {
    return false;
  }
}

//   operator!=
//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs) {
  return !(lhs == rhs);
}

//EFFECTS returns the next suit, which is the suit of the same color
Suit Suit_next(Suit suit) {
  if(suit == HEARTS) {
    return DIAMONDS;
  } else if (suit == DIAMONDS) {
    return HEARTS;
  } else if (suit == CLUBS) {
    return SPADES;
  } else {
    return CLUBS;
  }
}

//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, Suit trump) {
 if(a == b) {
  return false;
 }
 if((a.is_right_bower(trump)) || (b.is_right_bower(trump))) {
  if(b.is_right_bower(trump)) {
    return true;
  } else {
    return false;
  }
 } else if((a.is_left_bower(trump)) || (b.is_left_bower(trump))) {
  if(b.is_left_bower(trump)) {
    return true;
  } else {
    return false;
  }
 } else if(a.get_suit() == trump || b.get_suit() == trump) {
  if(a.get_suit() == trump && b.get_suit() == trump) {
    if(a.get_rank() > b.get_rank()) {
      return false;
    } else {
      return true;
    }
  } else if (a.get_suit() != trump) {
    return true;
  } else {
    return false;
  }
 } else if(a > b){
  return false;
 } else {
  return true;
 }
}

//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump) {
 if((a == b)) { 
  return false;
 } else if(led_card.is_left_bower(trump)) { 
  return Card_less(a, b, trump);
  }

  if(a.get_suit() == b.get_suit()) {
    return (Card_less(a, b, trump));
  }
  

 if((a.is_right_bower(trump)) || (b.is_right_bower(trump))) {
  if(a.is_right_bower(trump)) { 
    return false;
  } else { 
    return true;
    }
 } else if((a.is_left_bower(trump)) || (b.is_left_bower(trump))) {
  if((a.is_left_bower(trump))) {
    return false;
    } else { 
      return true;
    }
 } else if(a.get_suit() == trump || b.get_suit() == trump) {
  if (a.get_suit() == trump) { 
    return false;
  } else {
    return true;}
 } else if(a.get_suit() == led_card.get_suit() || b.get_suit() == led_card.get_suit()) {
  if (a.get_suit() == led_card.get_suit()) { 
    return false;
  } else {
    return true;
  }
 } else if(a < b) { 
  return true;
  } else {
    return false;
  }
}