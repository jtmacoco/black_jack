#pragma once
#include <iostream>
#include "players.h"
#include "deck.h"
using namespace std;
class Dealer:public Players
{
  public:
    Dealer(Deck deck, vector<shared_ptr<Players>> players):Players("Dealer",false),deck(deck),players(players){srand(time(0));};
    void begin_round();
    void display_hand_dealer();
    void handout_cards(shared_ptr<Players> player);
    void display_players_cards();
    void draw_cards();
    void clear_table();
    virtual ~Dealer();
  private:
    Deck deck;
    vector<shared_ptr<Players>> players;
};

