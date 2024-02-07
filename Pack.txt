// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <array>
#include "Card.h"
#include "Pack.h"

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack() {
 int r = 0;
 next = 0;
 for(int suit = 0; suit <= 3; ++suit) {
   for(int num = 7; num <= 12; ++num) {
     Card newCard(static_cast<Rank>(num), static_cast<Suit>(suit));
     cards[r] = newCard;
     ++r;
  }
 }
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(istream& pack_input) {
  string str1, str2, str3;
  next = 0;

  for(int i = 0; i < PACK_SIZE; ++i) {
    pack_input >> str1 >> str2 >> str3;
    Card newCard(string_to_rank(str1), string_to_suit(str3));
    cards[i] = newCard;
  }

}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
  Card deal = cards[next];
  ++next;
  return deal;
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
  next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() {
  for(int j = 0; j < 7; ++j) {
    int even = 0, odd = 1, shuffle2 = PACK_SIZE / 2, shuffle1 = 0;
    array<Card, PACK_SIZE> shuffle;
    
    for(int i = 0; i < PACK_SIZE; i+=2){
      shuffle[even] = cards[shuffle2];
      even = i + 2;
      shuffle[odd] = cards[shuffle1];
      odd = even + 1;
      shuffle2++;
      shuffle1++;
    }
    cards = shuffle;
    reset();
  }
}


// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {
 if(next == PACK_SIZE) {
   return true;
 } else {
   return false;
 }
}