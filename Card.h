#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <cassert>
#include <string>

enum Rank {
  TWO     = 0,
  THREE   = 1,
  FOUR    = 2,
  FIVE    = 3,
  SIX     = 4,
  SEVEN   = 5,
  EIGHT   = 6,
  NINE    = 7,
  TEN     = 8,
  JACK    = 9,
  QUEEN   = 10,
  KING    = 11,
  ACE     = 12,
};

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
Rank string_to_rank(const std::string &str);

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank);

//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank);

// Represent a Card's suit
enum Suit {
  SPADES   = 0,
  HEARTS   = 1,
  CLUBS    = 2,
  DIAMONDS = 3,
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
Suit string_to_suit(const std::string &str);

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit);

//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit);


class Card {
public:

  //EFFECTS Initializes Card to the Two of Spades
  Card();

  //EFFECTS Initializes Card to specified rank and suit
  Card(Rank rank_in, Suit suit_in);

  //EFFECTS Returns the rank
  Rank get_rank() const;

  //EFFECTS Returns the suit.  Does not consider trump.
  Suit get_suit() const;

  //EFFECTS Returns the suit
  //HINT: the left bower is the trump suit!
  Suit get_suit(Suit trump) const;

  //EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
  bool is_face_or_ace() const;

  //EFFECTS Returns true if card is the Jack of the trump suit
  bool is_right_bower(Suit trump) const;

  //EFFECTS Returns true if card is the Jack of the next suit
  bool is_left_bower(Suit trump) const;

  //EFFECTS Returns true if the card is a trump card.  All cards of the trump
  // suit are trump cards.  The left bower is also a trump card.
  bool is_trump(Suit trump) const;

  private:
  Rank rank;
  Suit suit;

  // This "friend declaration" allows the implementation of operator>>
  // to access private member variables of the Card class.
  friend std::istream & operator>>(std::istream &is, Card &card);
};

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card);

//EFFECTS Reads a Card from a stream in the format "Two of Spades"
//NOTE The Card class declares this operator>> "friend" function,
//     which means it is allowed to access card.rank and card.suit.
std::istream & operator>>(std::istream &is, Card &card);

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs);

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs);

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs);

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs);

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs);

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs);

//EFFECTS returns the next suit, which is the suit of the same color
Suit Suit_next(Suit suit);

//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, Suit trump);

//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump);

#endif
