// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "Card.h"
#include "unit_test_framework.h"

#include <iostream>
#include <sstream>
#include <cassert>
#include <fstream>
#include <algorithm>
#include <vector>


using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_player_insertion) {
  // Create a Human player
  Player * human = Player_factory("NotRobot", "Human");

  // Print the player using the stream insertion operator
  ostringstream oss1;
  oss1 << * human;

  // Verify that the output is the player's name
  ASSERT_EQUAL(oss1.str(), "NotRobot");

  // Create a Simple player
  Player * alice = Player_factory("Alice", "Simple");

  // Print the player using the stream insertion operator
  ostringstream oss2;
  oss2 << *alice;
  ASSERT_EQUAL(oss2.str(), "Alice");

  // Clean up players that were created using Player_factory()
  delete human;
  delete alice;
}

TEST(test_simple_player_make_trump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, CLUBS));
  bob->add_card(Card(TEN, CLUBS));
  bob->add_card(Card(QUEEN, CLUBS));
  bob->add_card(Card(KING, CLUBS));
  bob->add_card(Card(ACE, CLUBS));

  // Bob makes tump
  Card nine_spades(NINE, CLUBS);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, CLUBS);

  delete bob;
}

TEST(test_simple_player_lead_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(NINE, HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades(ACE, SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete bob;
}

TEST(test_simple_player_play_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob plays a card
  Card nine_diamonds(NINE, DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    HEARTS    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(NINE, SPADES));
  delete bob;
}

TEST(test_two_trump_cards_make_trump) {
    // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, HEARTS));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, HEARTS));

  //Game Details
  int round = 1;
  bool is_dealer = true;
  Card trump = Card(KING, HEARTS);
  Suit order_up_suit;

  // Bob orders up a card
  bool status = bob->make_trump(trump, is_dealer, round, order_up_suit);

  // Verify the card Bob played
  ASSERT_EQUAL(status, true);
  ASSERT_EQUAL(order_up_suit, trump.get_suit());
  delete bob;
}

TEST(test_two_trump_cards_one_trump) {
    // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, HEARTS));

  //Game Details
  int round = 1;
  bool is_dealer = true;
  Card upcard = Card(KING, HEARTS);
  Suit order_up_suit = upcard.get_suit();

  // Bob orders up a card
  bool status = bob->make_trump(upcard, is_dealer, round, order_up_suit);

  // Verify the card Bob played
  ASSERT_FALSE(status);
  delete bob;
}

TEST(test_two_trump_cards_one_trump1) {
    // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, HEARTS));

  //Game Details
  int round = 2;
  bool is_dealer = true;
  Card upcard = Card(KING, DIAMONDS);
  Suit order_up_suit = upcard.get_suit();

  // Bob orders up a card
  bool status = bob->make_trump(upcard, is_dealer, round, order_up_suit);

  // Verify the card Bob played
  ASSERT_TRUE(status);
  ASSERT_EQUAL(order_up_suit, HEARTS);
  delete bob;
}

TEST(test_two_trump_cards_one_trump2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, DIAMONDS));
  bob->add_card(Card(QUEEN, DIAMONDS));
  bob->add_card(Card(KING, DIAMONDS));
  bob->add_card(Card(ACE, DIAMONDS));

  // Bob makes tump
  Card nine_spades(NINE, CLUBS);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    2,              // Second round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Suit_next(CLUBS));

  delete bob;

}

TEST(test_make_trump_is_dealer) {
    // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  //Game Details
  int round = 2;
  bool is_dealer = true;
  Card upcard = Card(KING, DIAMONDS);
  Suit order_up_suit = upcard.get_suit();

  // Bob orders up a card
  bool status = bob->make_trump(upcard, is_dealer, round, order_up_suit);

  // Verify the card Bob played
  ASSERT_TRUE(status);
  delete bob;
}

TEST(test_simple_add_and_discard1) {
    // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob makes tump
  Card ace_diamonds(ACE, DIAMONDS);
  bob->add_and_discard(ace_diamonds);

  Card led_card = Card(ACE, CLUBS);

  int discarded_card = 0;

  for(int i = 0; i < bob->MAX_HAND_SIZE; ++i) {
    Card card_played = bob->play_card(led_card, led_card.get_suit());
    if(card_played == Card(NINE, SPADES)) {
      ++discarded_card;
    }
  }

  ASSERT_EQUAL(discarded_card, 0);

  // Verify Bob's order up and trump suit

  delete bob;
}

TEST(test_add_and_discard2) {
    // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(JACK, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob makes tump
  Card ace_diamonds(NINE, SPADES);
  bob->add_and_discard(ace_diamonds);

  Card led_card = Card(ACE, CLUBS);

  int discarded_card = 0;

  for(int i = 0; i < bob->MAX_HAND_SIZE; ++i) {
    Card card_played= bob->play_card(led_card, led_card.get_suit());
    if(card_played == Card(NINE, SPADES)) {
      ++discarded_card;
    }
  }

  ASSERT_EQUAL(discarded_card, 0);

  // Verify Bob's order up and trump suit

  delete bob;
}

TEST(test_simple_leading_trick1) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob makes tump
  Card trick = bob->lead_card(DIAMONDS);

  bool status = false;

  if(trick == Card(ACE, SPADES)) {
    status = true;
  }

  ASSERT_TRUE(status);

  // Verify Bob's order up and trump suit

  delete bob;
}

TEST(test_simple_leading_trick2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob makes tump
  Card trick = bob->lead_card(SPADES);

  bool status = false;

  if(trick == Card(ACE, SPADES)) {
    status = true;
  }

  ASSERT_TRUE(status);

  // Verify Bob's order up and trump suit

  delete bob;
}

TEST(test_simple_leading_trick3) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, DIAMONDS));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(ACE, CLUBS));

  // Bob makes tump
  Card trick = bob->lead_card(SPADES);

  bool status = false;

  if(trick == Card(ACE, CLUBS)) {
    status = true;
  }

  ASSERT_TRUE(status);

  // Verify Bob's order up and trump suit

  delete bob;
}

TEST(test_simple_play_tricks1) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob makes tump
  Card led_card = Card(QUEEN, DIAMONDS);
  Card trick = bob->play_card(led_card, led_card.get_suit());

  bool status = false;

  if(trick == Card(NINE, SPADES)) {
    status = true;
  }

  ASSERT_TRUE(status);

  // Verify Bob's order up and trump suit

  delete bob;

}

TEST(test_simple_play_tricks2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, DIAMONDS));
  bob->add_card(Card(QUEEN, DIAMONDS));
  bob->add_card(Card(KING, DIAMONDS));
  bob->add_card(Card(ACE, DIAMONDS));

  // Bob makes tump
  Card led_card = Card(JACK, DIAMONDS);
  Card trick = bob->play_card(led_card, led_card.get_suit());

  bool status = false;

  if(trick == Card(ACE, DIAMONDS)) {
    status = true;
  }

  ASSERT_TRUE(status);

  // Verify Bob's order up and trump suit

  delete bob;

}

TEST(test_simple_play_tricks3) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, CLUBS));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(ACE, HEARTS));

  // Bob makes tump
  Card led_card = Card(JACK, DIAMONDS);
  Card trick = bob->play_card(led_card, led_card.get_suit());

  bool status = false;

  if(trick == Card(NINE, DIAMONDS)) {
    status = true;
  }

  ASSERT_TRUE(status);

  // Verify Bob's order up and trump suit

  delete bob;

}

TEST(test_play_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(ACE, SPADES));
  bob->add_card(Card(NINE, HEARTS));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(QUEEN, CLUBS));
  bob->add_card(Card(KING, CLUBS));

  // Bob plays a card
  Card nine_diamonds(JACK, SPADES);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    DIAMONDS    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(ACE, SPADES));
  delete bob;
}

TEST(test_play_card_1) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(JACK, CLUBS));
  bob->add_card(Card(ACE, SPADES));
  bob->add_card(Card(KING, SPADES));

  // Bob plays a card
  Card nine_diamonds(KING, DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    SPADES    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(QUEEN, SPADES));
  delete bob;
}

TEST(test_play_card_2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(JACK, DIAMONDS));
  bob->add_card(Card(ACE, HEARTS));

  // Bob plays a card
  Card nine_diamonds(KING, HEARTS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    HEARTS    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(JACK, DIAMONDS));
  delete bob;
}

TEST(test_play_card_3) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(NINE, HEARTS));
  bob->add_card(Card(ACE, HEARTS));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(QUEEN, HEARTS));

  // Bob plays a card
  Card nine_diamonds(KING, DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    HEARTS    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(KING, SPADES));
  delete bob;
}

TEST(test_lead_card_4) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(JACK, DIAMONDS));
  bob->add_card(Card(KING, HEARTS));

  // Bob plays a card
  Card card_played = bob->lead_card(
    HEARTS    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(JACK, DIAMONDS));
  delete bob;
}

TEST(test_lead_card_5) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, CLUBS));
  bob->add_card(Card(JACK, DIAMONDS));
  bob->add_card(Card(QUEEN, HEARTS));

  // Bob plays a card
  Card led_card = Card(KING, DIAMONDS);
  Card card_played = bob->play_card(
    led_card, HEARTS    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(NINE, CLUBS));
  delete bob;
}

TEST(test_lead_card_6) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(JACK, HEARTS));
  bob->add_card(Card(ACE, HEARTS));

  // Bob plays a card
  Card led_card = Card(JACK, SPADES);
  Card card_played = bob->play_card(
    led_card, HEARTS    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(ACE, HEARTS));
  delete bob;
}

TEST(test_lead_card_7) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(JACK, DIAMONDS));
  bob->add_card(Card(QUEEN, HEARTS));

  // Bob plays a card
  Card led_card = Card(JACK, SPADES);
  Card card_played = bob->play_card(
    led_card, HEARTS    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(QUEEN, HEARTS));
  delete bob;
}

TEST(test_simple_player_lead_card_1) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(NINE, HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades(ACE, SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete bob;
}

TEST(test_play_card_5) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(NINE, DIAMONDS));

  Card jack_hearts(JACK, HEARTS);
  Card card_played = bob->play_card(
    jack_hearts,  // Nine of Diamonds is led
    DIAMONDS    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(NINE, DIAMONDS));
  delete bob;
}

TEST(test_play_card_4) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(QUEEN, DIAMONDS));
  bob->add_card(Card(NINE, CLUBS));
  bob->add_card(Card(TEN, CLUBS));

  Card jack_clubs(JACK, CLUBS);
  Card card_played = bob->play_card(
    jack_clubs,  // Nine of Diamonds is led
    SPADES    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(NINE, CLUBS));
  delete bob;
}

TEST(test_play_card_9) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(JACK, DIAMONDS));
  bob->add_card(Card(TEN, DIAMONDS));
  bob->add_card(Card(NINE, HEARTS));
  bob->add_card(Card(ACE, DIAMONDS));
  bob->add_card(Card(ACE, HEARTS));

  Card jack_clubs(JACK, HEARTS);
  Card card_played = bob->play_card(
    jack_clubs,  // Nine of Diamonds is led
    DIAMONDS    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(JACK, DIAMONDS));
  delete bob;
}

TEST(test_play_card_10) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(JACK, DIAMONDS));
  bob->add_card(Card(TEN, DIAMONDS));
  bob->add_card(Card(JACK, HEARTS));
  bob->add_card(Card(ACE, DIAMONDS));
  bob->add_card(Card(ACE, HEARTS));

  Card jack_clubs(JACK, HEARTS);
  Card card_played = bob->play_card(
    jack_clubs,  // Nine of Diamonds is led
    DIAMONDS    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(JACK, DIAMONDS));
  delete bob;
}

// Add more tests here

TEST_MAIN()
