#include "players.h"
void Players::add_money(int amount)//allow players to add money
{ money+=amount;
}
void Players::subtract_money(int amount)//players will subtract money if lost
{
  bet = amount;
  money-=amount;
}
void Players::print_stats()//display players stats
{
  calc_score();
  cout<<name<< " money: "<< money<< "$ "<<"score: "<<score;
}
void Players::display_hand(int index)//display the playres current hand
{
  for(int i = 0; i < (int)hand.size(); i++)
  {
    hand[i]->set_card_rows();
    hand[i]->print_card(index);
  }
}
void Players::calc_score()//calcuate the score based on the cards the players have
{
  score = 0;
  for(int i = 0; i < (int)hand.size(); i++)
  {
    score +=hand[i]->card_value(cur_user,score);
  }
}
double Players::hit_prob()//calculate the hit probability based on the players score
{
  calc_score();
  double prob = 0;
  if(score < 11)
    prob = 1;
  else if (score > 11 && score < 15)
    prob = .6;
  else if (score >= 15 && score < 17)
    prob = .3;
  else if (score >= 17 && score < 21)
    prob = .1;
  else if (score > 21)
    prob = 0;
  return prob;
}
double Players::double_down_prob()//calculate double down probability
{
  if(hand.size() <= 2)
  {
    if (score == 11)
      return 1;
    else
      return .1;
  }
  else
    return -1;
}
bool Players::hit()//return true if based on hit probability
{
  double prob = hit_prob() * 100;
  double num = rand() % 100 + 1;
  if (num <= prob)
    return true;
  else
    return false;
}
bool Players::double_down()//return true based on double down proability
{
  double prob = double_down_prob() * 100;
  int num = rand() % 100 + 1;
  if(num <= prob)
  {
    dd=true;//this is to make sure that double down only happens once per round
    return true;
  }
  else
    return false;
}
int Players::player_input()//return the players input based on the probability
{
  if(cur_user)
    return -1;
  else if(double_down() && dd)
  {
    dd=false;
    return 2;
  }
  else if(hit())
    return 1;
  else
    return 0;
}
void Players::add_to_hand(shared_ptr<Cards> card)//adds a card to players hand vector
{
  hand.push_back(card);
}
int Players::get_score()
{
  return score;
}
vector<shared_ptr<Cards>> Players::return_cards()//allows dealer to collect the cards from players
{
  vector<shared_ptr<Cards>> temp = hand;
  hand.clear();//make sure to clear the vector so hand is empty
  return temp;
}
int Players::get_stats_string_length()//used to calculate amout of spaces 
{
  string length = name+" money: "+to_string(money)+"$"+" score: "+to_string(score);
  return length.size();
}
int Players::get_money()
{
  return money;
}
int Players::get_bet()
{
  return bet;
}
int Players::get_hand_size()
{
  return hand.size();
}
string Players::get_name()
{
  return name;
}
bool Players::get_double_down()
{
  return dd;
}
Players::~Players()
{
}
