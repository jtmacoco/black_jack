#include "dealer.h"
#define LR 7
#define dm 8
void Dealer::begin_round()
{
  shared_ptr<Cards> card1=deck.get_card();
  shared_ptr<Cards> card2=deck.get_card();
  add_to_hand(card1);
  add_to_hand(card2);
  for (int i = 0; i < players.size(); i++)
  {
    card1 = deck.get_card();
    card2 = deck.get_card();
    players[i]->add_to_hand(card1);
    players[i]->add_to_hand(card2);
  }
} void Dealer::display_hand_dealer()
{
  for(int i = 0; i < dm; i++)
    cout<<" ";
  cout<<"DEALER"<<endl;
  hand[0]->set_card_rows();
  Cards *blank = new Cards();
  blank->set_blank_card_rows();
  for (int i = 0; i < LR; i++)
  {
    hand[0]->print_card(i);
    blank->print_card(i);
    cout << endl;
  }
}
void Dealer::handout_cards(shared_ptr<Players> player)
{
  shared_ptr<Cards> card = deck.get_card();
  player->add_to_hand(card);
}
void Dealer::draw_cards()
{
  while(get_score() < 17)
  {
    shared_ptr<Cards> card = deck.get_card();
    add_to_hand(card);
    calc_score();
  }
  calc_score();
  for(int i = 0; i < dm; i++)
    cout<<" ";
  cout<<"DEALER"<<endl;
  for(int i = 0; i < LR; i++)
  {
    display_hand(i);
    cout<<endl;
  }

}
void Dealer::clear_table()
{
  for(int i = 0; i < (int)players.size(); i++)
  {
    vector<shared_ptr<Cards>> players_hand = players[i]->return_cards();
    for(int j = 0; j < (int)players_hand.size(); j++)
      deck.add_card_back(players_hand[j]);
  }
  vector<shared_ptr<Cards>> dealers_hand = return_cards();
  for(int i = 0; i < (int)dealers_hand.size(); i++)
    deck.add_card_back(dealers_hand[i]);

}
void Dealer::display_players_cards()
{
  for(int i = 0 ; i < LR; i++)
  {
    for(int j = 0; j < (int)players.size(); j++)
      players[j]->display_hand(i);
    cout<<endl;
  }
}
Dealer::~Dealer()
{
}
