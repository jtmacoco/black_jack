#include "dealer.h"
#define LR 7//stands for last row
#define dm 8//dealer spaces to be centered
void Dealer::begin_round()//dealer will start the round
{
  shared_ptr<Cards> card1=deck.get_card();//intilize two random cards from deck
  shared_ptr<Cards> card2=deck.get_card();
  add_to_hand(card1);//add the cards to the dealers hand
  add_to_hand(card2);
  for (int i = 0; i < players.size(); i++)//loop through the players vector
  {
    card1 = deck.get_card();//intilzie random cards to hand out to players
    card2 = deck.get_card();
    players[i]->add_to_hand(card1);//players will add these cards to their hand
    players[i]->add_to_hand(card2);
  }
} void Dealer::display_hand_dealer()//display the dealers hand
{
  for(int i = 0; i < dm; i++)//this loop allows for the correct amount of spaces do "DEALER" string is centered
    cout<<" ";
  cout<<"DEALER"<<endl;
  hand[0]->set_card_rows();//set the rows which will prep the cards to be printed horizontally
  Cards *blank = new Cards();//set a blank card since it will be fliped when the dealer draws
  blank->set_blank_card_rows();
  for (int i = 0; i < LR; i++)
  {
    hand[0]->print_card(i);//print the cards horizontally 
    blank->print_card(i);
    cout << endl;
  }
}
void Dealer::handout_cards(shared_ptr<Players> player)
{
  shared_ptr<Cards> card = deck.get_card();//hand out the cards to the players 
  player->add_to_hand(card);//players will add the card to the hand
}
void Dealer::draw_cards()
{
  while(get_score() <= 17)//dealer will continue to draw cards unless score is 17 or higher
  {
    shared_ptr<Cards> card = deck.get_card();
    add_to_hand(card);
    calc_score();
  }
  calc_score();
  for(int i = 0; i < dm; i++)//print spaces so "DEALER" is centered
    cout<<" ";
  cout<<"DEALER"<<endl;
  for(int i = 0; i < LR; i++)//print all the cards the dealer took form deck
  {
    display_hand(i);
    cout<<endl;
  }

}
void Dealer::clear_table()//clear the table of all cards and return them to the deck
{
  for(int i = 0; i < (int)players.size(); i++)//loop through the players vector
  {
    vector<shared_ptr<Cards>> players_hand = players[i]->return_cards();//grab each players hand
    for(int j = 0; j < (int)players_hand.size(); j++)//grab each card player has by looping through their hand vector
      deck.add_card_back(players_hand[j]);//return the players cards to the deck
  }
  vector<shared_ptr<Cards>> dealers_hand = return_cards();
  for(int i = 0; i < (int)dealers_hand.size(); i++)//loop will allow dealer to return his cards back as well
    deck.add_card_back(dealers_hand[i]);

}
void Dealer::display_players_cards()//display all the players hands potentially don't need
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
