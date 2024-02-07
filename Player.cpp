#include "Card.h"
#include "Player.h"
#include <string>
#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

class SimplePlayer : public Player{
 private:
 string name_in;
 vector<Card> hand;
 
 public:
 
 SimplePlayer(string  name) : name_in(name) {}
 
 //EFFECTS returns player's name
 virtual const string & get_name() const override {
    return name_in;
 }

 //REQUIRES player has less than MAX_HAND_SIZE cards
 //EFFECTS  adds Card c to Player's hand
 virtual void add_card(const Card &c) override {
    hand.push_back(c);
    sort(hand.begin(), hand.end());
 }

 //REQUIRES round is 1 or 2
 //MODIFIES order_up_suit
 //EFFECTS If Player wishes to order up a trump suit then return true and
 //  change order_up_suit to desired suit.  If Player wishes to pass, then do
 //  not modify order_up_suit and return false.
 virtual bool make_trump(const Card &upcard, bool is_dealer, 
                          int round, Suit &order_up_suit) const override{
    int trump_count = 0;
    bool return_value = false;
    vector<Card> hand1 = hand;
    Suit suit1 = upcard.get_suit();
    
    if(round == 1) {
      for(int i = 0; i < hand1.size(); ++i) {
        if(hand1[i].is_face_or_ace() && hand1[i].is_trump(suit1)) {
          ++trump_count;
        }
      }

      if(trump_count >= 2) {
        order_up_suit = upcard.get_suit();
        return_value = true;
      }
    } else if (round == 2) {
      for(int i = 0; i < hand1.size(); ++i) {
        if(hand1[i].is_face_or_ace() & hand1[i].is_trump(Suit_next(suit1))) {
           order_up_suit = Suit_next(upcard.get_suit());
           return_value = true;
        } else if(is_dealer) {
            order_up_suit = Suit_next(upcard.get_suit());
           return_value = true;
        }
      }
    } else if((round == 2) & (is_dealer)) {
      order_up_suit = Suit_next(upcard.get_suit());
      return_value = true;
    }
    return return_value;
 }

 //REQUIRES Player has at least one card
 //EFFECTS  Player adds one card to hand and removes one card from hand.
 virtual void add_and_discard(const Card &upcard) override{
    hand.push_back(upcard);
    int index = 0;
    Card lowest_card = hand[0];
    for(int i = 0; i < hand.size(); ++i) {
      if(Card_less(hand[i], lowest_card, upcard.get_suit())) {
        index = i;
        lowest_card = hand[i];
      }
    }
    hand.erase(hand.begin() + index);
   cout << endl;
 }

 //REQUIRES Player has at least one card
 //EFFECTS  Leads one Card from Player's hand according to their strategy
 //  "Lead" means to play the first Card in a trick.  The card
 //  is removed the player's hand.
 virtual Card lead_card(Suit trump) override{
    int trump_count = 0;
    for(int i = 0; i < hand.size(); ++i) {
        if(hand[i].is_trump(trump)) {
            ++trump_count;
        }
    }

    Card return_card;
    if(trump_count == hand.size()) {
        Card highest_card = hand[0];
        int index = 0;
        for(int i = 0; i < hand.size(); ++i) {
            if(Card_less(highest_card, hand[i], trump)) {
                index = i;
            }
        }

        return_card = hand[index];
        hand.erase(hand.begin() + index);
        return return_card;
    } else {
        int index = 0;
        vector<Card> non_trump_cards;
        for(int i = 0; i < hand.size(); ++i) {
          if((hand[i].is_trump(trump) == false)) {
            non_trump_cards.push_back(hand[i]);
          }
        }
        
        Card highest_card = non_trump_cards[0];
        for(int j = 0; j < non_trump_cards.size(); ++j) {
          if(Card_less(highest_card, non_trump_cards[j], trump)) {
            highest_card = non_trump_cards[j];
          }
        }

        for(int k = 0; k < hand.size(); ++k) {
          if(hand[k] == highest_card) {
              index = k;
          }
        }
        hand.erase(hand.begin() + index);
        return highest_card;
    }

 }

 //REQUIRES Player has at least one card
 //EFFECTS  Plays one Card from Player's hand according to their strategy.
 //  The card is removed from the player's hand.
 virtual Card play_card(const Card &led_card, Suit trump) override{
    bool fol_s = false;
    Card r_c = hand[0];
    int index = 0;
    Suit lc_suit;
    if(led_card.is_left_bower(trump)) {
      lc_suit = trump;
    } else {
      lc_suit = led_card.get_suit();
    }
    
    for(int j = 0; ((j < hand.size()) & (lc_suit == trump)); ++j) {
      if((hand[j].is_trump(lc_suit))) {
        fol_s = true;
        r_c = hand[j];
        index = j;
        break;
      }
    }
    for(int j = 0; ((j < hand.size()) & (lc_suit != trump)); ++j) {
      if((hand[j].get_suit() == lc_suit) & (!hand[j].is_left_bower(trump))) {
        fol_s = true;
        r_c = hand[j];
        index = j;
        break;
        }
      }
      
      for(int i = 0; ((i < hand.size()) & (fol_s)); ++i) {
        if((hand[i].get_suit() == lc_suit) & (!hand[i].is_left_bower(trump))) {
          if(Card_less(r_c, hand[i], led_card, trump)) {
            r_c = hand[i];
            index = i;
          }
        }
      }
        for(int i = 0; ((i < hand.size()) & (!fol_s)); ++i) {
          if(Card_less(hand[i], r_c, led_card, trump)) {
            r_c = hand[i];
            index = i;
          }
        }
      hand.erase(hand.begin() + index);
      return r_c;
 }
};



class HumanPlayer : public Player{
 private:
 string na;
 vector<Card> hand;

 void print_hand() const {
  for (size_t i = 0; i < hand.size(); ++i) {
    cout << "Human player " << na << "'s hand: " << "[" << i << "] " << hand[i] << endl;
  }
 }
 
 public:
 
 HumanPlayer(string  name) : na(name) {}
 
 //EFFECTS returns player's name 
 virtual const string & get_name() const override {
    return na;
 }

 //REQUIRES player has less than MAX_HAND_SIZE cards
 //EFFECTS  adds Card c to Player's hand
 virtual void add_card(const Card &c) override {
    hand.push_back(c);
    std::sort(hand.begin(), hand.end());
  }

 //REQUIRES round is 1 or 2
 //MODIFIES order_up_suit
 //EFFECTS If Player wishes to order up a trump suit then return true and
 //  change order_up_suit to desired suit.  If Player wishes to pass, then do
 //  not modify order_up_suit and return false.
 virtual bool make_trump(const Card &upcard, bool is_dealer, 
                            int round, Suit &order_up_suit) const override{
   print_hand();

   cout << "Human player " << na << ", please enter a suit, or \"pass\":\n";
   string decision;
   cin >> decision;

   if (decision != "pass") {
      order_up_suit = string_to_suit(decision);
      return true;
   } else {
      return false;
   }
  }

 //REQUIRES Player has at least one card
 //EFFECTS  Player adds one card to hand and removes one card from hand.
 virtual void add_and_discard(const Card &upcard) override{
   print_hand();
   cout << "Discard upcard: [-1]\n";
   cout << "Human player " << na << ", please select a card to discard:\n" << endl;
   int decision;
   cin >> decision;

   hand.erase(hand.begin() + decision);
   add_card(upcard);
 }

 //REQUIRES Player has at least one card
 //EFFECTS  Leads one Card from Player's hand according to their strategy
 //  "Lead" means to play the first Card in a trick.  The card
 //  is removed the player's hand.
 virtual Card lead_card(Suit trump) override{
    print_hand();

   cout << "Human player " << na << ", please select a card:\n";
   int decision;
   cin >> decision;


   Card lead_card = hand[decision];
   hand.erase(hand.begin() + decision);
   return lead_card;
 }

 //REQUIRES Player has at least one card
 //EFFECTS  Plays one Card from Player's hand according to their strategy.
 //  The card is removed from the player's hand.
 virtual Card play_card(const Card &led_card, Suit trump) override{
   print_hand();

   cout << "Human player " << na << ", please select a card:\n";
   int decision;
   cin >> decision;


   Card play_card = hand[decision];
   hand.erase(hand.begin() + decision);
   return play_card;  
 }
};

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy) {
  if(strategy == "Simple") {
      return new SimplePlayer(name);
  } else if(strategy == "Human") {
      return new HumanPlayer(name);
  } else {
      assert(false);
      return nullptr;
  }
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p) {
    return os << p.get_name();
};
