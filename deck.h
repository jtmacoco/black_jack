#pragma once
#include <iostream>
#include <random>
#include <memory>
#include "cards.h"
using namespace std;
class Deck{
  public:
    Deck(int deck_amount):deck_amount(deck_amount){};
    void create_deck();
    void print_deck();
    void shuffle_deck();
    void add_card_back(shared_ptr<Cards> card);
    shared_ptr<Cards> get_card();
    int get_size();
    virtual ~Deck();
  private:
    vector<shared_ptr<Cards>> decks;
    int deck_amount;
};
