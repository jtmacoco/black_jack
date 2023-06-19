#pragma once
#include <iostream>
#include "cards.h"
#include <time.h>
using namespace std;
class Players
{
  public:
    Players(string name, bool cur_user): name(name),cur_user(cur_user)
  {
    srand(time(0));
  };
    void add_money(int amount);
    void subtract_money(int amount);
    void print_stats();
    void display_hand(int index);
    void calc_score();
    void add_to_hand(shared_ptr<Cards> card);
    double hit_prob();
    double double_down_prob();
    bool hit();
    bool double_down();
    bool get_double_down();
    int player_input();
    int get_score();
    int get_stats_string_length();
    int get_money();
    int get_bet();
    int get_hand_size();
    string get_name();
    vector<shared_ptr<Cards>> return_cards();
    virtual~Players();
  protected:
    string name;
    int score = 0;
    int money = 1000;
    int bet = 0;
    bool cur_user;
    bool dd=false;
    vector<shared_ptr<Cards>> hand;
};
