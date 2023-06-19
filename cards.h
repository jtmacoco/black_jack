#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
class Cards{
  public:
    Cards(){
      card = "**********\n*n       *\n*        *\n*   s    *\n*        *\n*       z*\n**********\n";
    };
    void print_card(int index);
    void print_card_vertical();
    void set_card_rows();
    void set_blank_card_rows();
    void edit_cards(char suit,int index);
    int card_value(bool cur_user, int total); 
  private:
    string card;
    string blank_card="**********\n*        *\n*        *\n*        *\n*        *\n*        *\n**********\n";
    vector<string>rows;
    bool ace = false;
    int card_value_ace = -1;

};
