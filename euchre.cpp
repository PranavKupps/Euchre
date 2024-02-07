#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <string>
#include <fstream>

#include "Card.h"
#include "Pack.h"
#include "Player.h"

using namespace std;

const int TRICK_CARD_SIZE = 4;

class Full_Game {
private:
 Pack pack;
 vector<Player *> table;
 int hand = 0, d = 0;
 Card upcard;
 Card led_card;
 Suit t_s = upcard.get_suit();
 string trump_card = "";
 int p1_3_pts = 0, p0_2_pts = 0;
 bool trump = false;
 int current_index = 0;
 vector<Card> trick_card;
 int trump_maker_number = 0;
 int p_0__2_win_trick = 0, p_1_or_3_win_trick = 0;
 int return_hand_helper = 0;

public:

    int find_max(vector<Card> trick_card, Suit trump, Card led_card, vector<int> order) {
     Card max_card = trick_card[0];
     int max_index = 0;
    
     for (int i = 1; i < TRICK_CARD_SIZE; ++i) {
         if (Card_less(max_card, trick_card[i], led_card, trump)) {
            max_card = trick_card[i];
            max_index = i;
        }
     }

     int x = order[max_index];
    
     return x;
   }
    
    void read_in_pack_input(string file_name) {
     ifstream pack_in;
     pack_in.open(file_name);
     
     if (!pack_in.is_open()) {
       cout << "Error opening " << file_name << endl;
    }
     pack = Pack(pack_in);
  }

    void create_table(vector<string> names, vector<string> types) {
      Player *player1 = Player_factory(names.at(0), types.at(0));
      table.push_back(player1);

      Player *player2 = Player_factory(names.at(1), types.at(1));
      table.push_back(player2);

      Player *player3 = Player_factory(names.at(2), types.at(2));
      table.push_back(player3);

      Player *player4 = Player_factory(names.at(3), types.at(3));
      table.push_back(player4);
  }

    void shuffle_the_pack(string shuffle) {
    if(shuffle == "shuffle") {
        pack.shuffle();
    } else {
        pack.reset();
    }
  }

    void Deal() {
        d = hand % 4;
        
        table[(d + 1) % 4]->add_card(pack.deal_one());
        table[(d + 1) % 4]->add_card(pack.deal_one());
        table[(d + 1) % 4]->add_card(pack.deal_one());
        
        table[(d + 2) % 4]->add_card(pack.deal_one());
        table[(d + 2) % 4]->add_card(pack.deal_one());
        
        table[(d + 3) % 4]->add_card(pack.deal_one());
        table[(d + 3) % 4]->add_card(pack.deal_one());
        table[(d + 3) % 4]->add_card(pack.deal_one());
        
        table[(d + 4) % 4]->add_card(pack.deal_one());
        table[(d + 4) % 4]->add_card(pack.deal_one());
        
        table[(d + 1) % 4]->add_card(pack.deal_one());
        table[(d + 1) % 4]->add_card(pack.deal_one());
        
        table[(d + 2) % 4]->add_card(pack.deal_one());
        table[(d + 2) % 4]->add_card(pack.deal_one());
        table[(d + 2) % 4]->add_card(pack.deal_one());
        
        table[(d + 3) % 4]->add_card(pack.deal_one());
        table[(d + 3) % 4]->add_card(pack.deal_one());
        
        table[(d + 4) % 4]->add_card(pack.deal_one());
        table[(d + 4) % 4]->add_card(pack.deal_one());
        table[(d + 4) % 4]->add_card(pack.deal_one());
        
        upcard = pack.deal_one();
        cout << upcard << " turned up" << endl;
    }

    Player* find_dealer() {
        d = hand % 4;
        return table[d];
    }

    int return_hand() {
        hand = return_hand_helper;
        ++return_hand_helper;
        d = hand % 4;
        return hand;
    }

    void winning_message(int points_to_win) {
        if(p0_2_pts >= points_to_win) {
            cout << *table[0] << " and " << *table[2] << " win!" << endl;
        } else {
            cout << *table[1] << " and " << *table[3] << " win!" << endl;
        }
    }

    int get_p0_2_pts() const {
        return p0_2_pts;
    }

    int get_p1_3_pts() const {
        return p1_3_pts;
    }

    void make_trump() {
        trump = false;
        d = hand % 4;
        int round;
        int x = 9;

        for(int i = 1; i < x; ++i) {
            if(i < 5) {
                round = 1;
            } else {
                round = 2;
            }

            if(table[(d + i) % 4]->make_trump(upcard, i % 4 == d, round, t_s)) {
                if(round == 1) {
                  cout << table[(d + i) % 4]->get_name() << 
                      " orders up " << t_s << endl;
                  trump_maker_number = d + i % 4;
                  table[d]->add_and_discard(upcard);
                  break;
                } else if(round == 2) {
                    cout << table[(d + i) % 4]->get_name() << 
                        " orders up " << t_s << endl << endl;
                    trump_maker_number = d + i % 4;
                    break;
                }
            } else {
                cout << table[(d + i) % 4]->get_name() << " passes" << endl;
            }
        }
    }

    void play() {
        vector<int> order;
        current_index = (d + 1) % 4;

        for(int j = 0; j <= table.size(); ++j) {
            order.clear();
            trick_card.clear();
            led_card = table[current_index]->lead_card(t_s);
            trick_card.push_back(led_card);
            cout << led_card << " led by " << table[current_index]->get_name() << endl;
            order.push_back(current_index);

          for(int i = 1; i < table.size(); ++i) {
            if(((current_index + i) % 4) == 3) {
                Card test_card = table[3]->play_card(led_card, t_s);
                cout << test_card << " played by " << *table[3] << endl;
                trick_card.push_back(test_card);
                order.push_back(3);
            } else if(((current_index + i) % 4) == 2) {
                Card test_card = table[2]->play_card(led_card, t_s);
                cout << test_card << " played by " << *table[2] << endl;
                trick_card.push_back(test_card);
                order.push_back(2);
            } else if(((current_index + i) % 4) == 1) {
                Card test_card = table[1]->play_card(led_card, t_s);
                cout << test_card << " played by " << *table[1] << endl;
                trick_card.push_back(test_card);
                order.push_back(1);
            } else if(((current_index + i) % 4) == 0) {
                Card test_card = table[0]->play_card(led_card, t_s);
                cout << test_card << " played by " << *table[0] << endl;
                trick_card.push_back(test_card);
                order.push_back(0);
            }
          }

          current_index = find_max(trick_card, t_s, led_card, order);
          cout << *table[current_index] << " takes the trick" << endl << endl;

          if(current_index % 2 == 0) {
              ++p_0__2_win_trick;
          } else {
              ++p_1_or_3_win_trick;
          }
        }
    }

    void find_trick_winner() {
        if (p_0__2_win_trick >= 3) {
            cout << *table[0] << " and " << *table[2] << " win the hand" << endl;
            if (trump_maker_number % 2 == 0) {
                if (p_0__2_win_trick == 5) {
                    p0_2_pts += 2;
                    cout << "march!" << endl;
                }
                else {
                    p0_2_pts++;
                }
            }
            else {
                p0_2_pts+= 2;
                cout << "euchred!" << endl;
            }
        }
        else {
            cout << *table[1] << " and " << *table[3] << " win the hand" << endl;
            if (trump_maker_number % 2 == 1) {
                if (p_1_or_3_win_trick == 5) {
                    p1_3_pts += 2;
                    cout << "march!" << endl;
                }
                else {
                    p1_3_pts ++;
                }
            }
            else {
                p1_3_pts += 2;
                cout << "euchred!" << endl;
            }
        }
        
        p_1_or_3_win_trick = 0;
        p_0__2_win_trick = 0;
        trump = "";
        cout << *table[0] << " and " << *table[2] << " have " << p0_2_pts << " points";
        cout << endl;
        cout << *table[1] << " and " << *table[3] << " have " << p1_3_pts << " points";
        cout << endl << endl;
    }

    void delete_game() {
        table.clear();
    }
};

int main(int argc, char* argv[]) {
    Full_Game game;
    
    int pts_to_win = atoi(argv[3]);
    game.read_in_pack_input(argv[1]);

    vector<string> names {argv[4], argv[6], argv[8], argv[10]};
    vector<string> types {argv[5], argv[7], argv[9], argv[11]};
    
    game.create_table(names, types);
    
    for (int i = 0; i < argc; ++i) {
        cout << argv[i] << " ";
    }
    cout << endl;
    
    while ((game.get_p0_2_pts() < pts_to_win) & (game.get_p1_3_pts() < pts_to_win)) {
        cout << "Hand " << game.return_hand() << endl;
        game.shuffle_the_pack(argv[2]);
        cout << *game.find_dealer() << " deals" << endl;
        game.Deal();
        game.make_trump();
        game.play();
        game.find_trick_winner();
    }
    
    game.winning_message(pts_to_win);
    game.delete_game();
    delete game.find_dealer();
    return 0;
}
