// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;


TEST(test_card_ctor) {
  Card c(ACE, HEARTS);
  ASSERT_EQUAL(ACE, c.get_rank());
  ASSERT_EQUAL(HEARTS, c.get_suit());

  Card card1;
  ASSERT_EQUAL(TWO, card1.get_rank());
  ASSERT_EQUAL(SPADES, card1.get_suit());
}

// Add more test cases here

TEST(test_suit_next1) {
 Card card1 = Card(NINE, SPADES);
 ASSERT_EQUAL(Suit_next(card1.get_suit()),CLUBS);
}

TEST(test_suit_next2) {
 Card card1 = Card(NINE, DIAMONDS);
 ASSERT_EQUAL(Suit_next(card1.get_suit()),HEARTS);
}

TEST(test_cardless1_trial1) {
  Card card1 = Card(NINE, SPADES);
  Card card2 = Card(TEN, SPADES);

  ASSERT_EQUAL(Card_less(card1, card2, SPADES), true);
}

TEST(test_cardless1_trial2) {
  Card card1 = Card(JACK, CLUBS);
  Card card2 = Card(JACK, SPADES);

  ASSERT_EQUAL(Card_less(card1, card2, SPADES), true);
}

TEST(test_cardless1_trial3) {
  Card card1 = Card(ACE, SPADES);
  Card card2 = Card(JACK, CLUBS);

  ASSERT_EQUAL(Card_less(card1, card2, SPADES), true);
  ASSERT_EQUAL(Card_less(card2, card1, SPADES), false);
}

TEST(test_cardless1_trial4) {
  Card card1 = Card(KING, SPADES);
  Card card2 = Card(ACE, SPADES);

  ASSERT_EQUAL(Card_less(card1, card2, SPADES), true);
}

TEST(test_cardless1_trial5) {
  Card card1 = Card(ACE, DIAMONDS);
  Card card2 = Card(NINE, SPADES);

  ASSERT_EQUAL(Card_less(card1, card2, SPADES), true);
}

TEST(test_cardless1_trial6) {
  Card card1 = Card(KING, DIAMONDS);
  Card card2 = Card(ACE, DIAMONDS);

  ASSERT_EQUAL(Card_less(card1, card2, SPADES), true);
}

TEST(test_cardless1_trial7) {
  Card card1 = Card(NINE, CLUBS);
  Card card2 = Card(NINE, HEARTS);

  ASSERT_EQUAL(Card_less(card1, card2, SPADES), false);
}

TEST(test_cardless1_trial8) {
  Card card1 = Card(JACK, HEARTS);
  Card card2 = Card(TEN, HEARTS);

  ASSERT_EQUAL(Card_less(card1, card2, SPADES), false);
}

TEST(test_cardless2_trial1) {
  Card card1 = Card(KING, DIAMONDS);
  Card card2 = Card(ACE, CLUBS);
  Card led_card = Card(ACE, DIAMONDS);

  ASSERT_EQUAL(Card_less(card1, card2, led_card, SPADES), false);
}

TEST(test_cardless2_trial2) {
  Card card1 = Card(TEN, DIAMONDS);
  Card card2 = Card(ACE, CLUBS);
  Card led_card = Card(ACE, DIAMONDS);

  ASSERT_EQUAL(Card_less(card1, card2, led_card, SPADES), false);
}

TEST(test_cardless2_trial3) {
  Card card1 = Card(TEN, DIAMONDS);
  Card card2 = Card(ACE, CLUBS);
  Card led_card = Card(ACE, DIAMONDS);

  ASSERT_EQUAL(Card_less(card1, card2, led_card, SPADES), false);
}

TEST(test_cardless2_trial4) {
  Card card1 = Card(NINE, SPADES);
  Card card2 = Card(TEN, SPADES);
  Card led_card = Card(ACE, DIAMONDS);

  ASSERT_EQUAL(Card_less(card1, card2, led_card, SPADES), true);
}

TEST(test_cardless2_trial5) {
  Card card1 = Card(JACK, CLUBS);
  Card card2 = Card(JACK, SPADES);
  Card led_card = Card(ACE, DIAMONDS);

  ASSERT_EQUAL(Card_less(card1, card2, led_card, SPADES), true);
}

TEST(test_cardless2_trial6) {
  Card card1 = Card(ACE, SPADES);
  Card card2 = Card(JACK, CLUBS);
  Card led_card = Card(ACE, DIAMONDS);

  ASSERT_EQUAL(Card_less(card1, card2, led_card, SPADES), true);
}

TEST(test_cardless2_trial7) {
  Card card1 = Card(KING, SPADES);
  Card card2 = Card(ACE, SPADES);
  Card led_card = Card(ACE, DIAMONDS);

  ASSERT_EQUAL(Card_less(card1, card2, led_card, SPADES), true);
}

TEST(test_cardless2_trial8) {
  Card card1 = Card(ACE, DIAMONDS);
  Card card2 = Card(NINE, SPADES);
  Card led_card = Card(ACE, DIAMONDS);

  ASSERT_EQUAL(Card_less(card1, card2, led_card, SPADES), true);
}

TEST(test_cardless2_trial9) {
  Card card1 = Card(KING, DIAMONDS);
  Card card2 = Card(ACE, DIAMONDS);
  Card led_card = Card(ACE, DIAMONDS);

  ASSERT_EQUAL(Card_less(card1, card2, led_card, SPADES), true);
}

TEST(test_cardless2_trial10) {
  Card card1 = Card(NINE, CLUBS);
  Card card2 = Card(NINE, HEARTS);
  Card led_card = Card(ACE, DIAMONDS);

  ASSERT_EQUAL(Card_less(card1, card2, led_card, SPADES), false);
}

TEST(test_cardless2_trial11) {
  Card card1 = Card(JACK, HEARTS);
  Card card2 = Card(TEN, HEARTS);
  Card led_card = Card(ACE, DIAMONDS);

  ASSERT_EQUAL(Card_less(card1, card2, led_card, SPADES), false);
}

TEST(basic_tests) {
  // finds suit of a left bower
  Card card1 = Card(JACK, DIAMONDS);
  ASSERT_EQUAL(card1.get_suit(HEARTS), HEARTS);

  //tests for face card or not
  Card card2(JACK, DIAMONDS);
  Card card3(THREE, SPADES);

  ASSERT_EQUAL(card2.is_face_or_ace(), true);
  ASSERT_EQUAL(card3.is_face_or_ace(), false);

  //tests for right and left bower
  card1 = Card(JACK, HEARTS);
  card2 = Card(JACK, DIAMONDS);

  ASSERT_EQUAL(card1.is_right_bower(HEARTS), true);
  ASSERT_EQUAL(card2.is_right_bower(HEARTS), false);

  ASSERT_EQUAL(card1.is_left_bower(HEARTS), false);
  ASSERT_EQUAL(card2.is_left_bower(HEARTS), true);

  //tests the < operator
  card1 = Card(JACK, SPADES);
  card2 = Card(KING, HEARTS);
  card3 = Card(JACK, DIAMONDS);
  ASSERT_TRUE(card1 < card2);
  ASSERT_TRUE(card1 < card3);

  //tests == and != operators
  card1 = Card(JACK, SPADES);
  card2 = Card(JACK, SPADES);
  ASSERT_TRUE(card1 == card2);
  ASSERT_FALSE(card1 != card2);

  //tests <= and > operators
  card1 = Card(JACK, SPADES);
  card2 = Card(KING, HEARTS);
  card3 = Card(JACK, DIAMONDS);
  ASSERT_TRUE(card1 <= card2);
  ASSERT_TRUE(card1 <= card3);
  ASSERT_TRUE(card1 <= card1);
  ASSERT_TRUE(card2 > card1);
  ASSERT_TRUE(card3 > card1);

  //tests >= operator
  card1 = Card(JACK, SPADES);
  card2 = Card(KING, HEARTS);
  card3 = Card(JACK, DIAMONDS);
  ASSERT_TRUE(card2 >= card1);
  ASSERT_TRUE(card3 >= card1);
  ASSERT_TRUE(card1 >= card1);
}

TEST(test_card_get_rank) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
}

TEST(test_card_get_suit) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(test_card_suit_next) {
    Card c(ACE, DIAMONDS);
    ASSERT_EQUAL(HEARTS, Suit_next(c.get_suit()));
}

TEST(test_card_suit_next1) {
    Card c(ACE, SPADES);
    ASSERT_EQUAL(CLUBS, Suit_next(c.get_suit()));
}

TEST(test_card_suit_next2) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(DIAMONDS, Suit_next(c.get_suit()));
}

TEST(test_card_suit_next3) {
    Card c(ACE, CLUBS);
    ASSERT_EQUAL(SPADES, Suit_next(c.get_suit()));
}

TEST_MAIN()
