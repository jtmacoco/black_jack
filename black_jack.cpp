#include <iostream>
#include "cards.h"
#include "deck.h"
#include "players.h"
#include "dealer.h"
#include <unistd.h>
#include <term.h> 
#include <sys/ioctl.h>
using namespace std;
#define LR 7//LR stand for last row
//#define lc2 22//length of two cards 
void calc_bets(vector<shared_ptr<Players>> players)//calculate all the players bets
{
  srand(time(0));//allows for new random number every time rather than once per program execution
  for(int i = 1; i < (int)players.size(); i++)//start at 1 since don't want to include the cur_user
  { 
    int player_money=players[i]->get_money();//get how much money the player has
    if(player_money < 0)//if the player is out of money don't subtract anything and break
    {
      //players[i]->subtract_money(0);
      break;
    }
    int bet = rand() % 500 +1;//get a random bet between 1 and 500
    while(bet > player_money|| (player_money-bet) < 0)//check if the bet is a valid amout without the player having netative money
      bet = rand() % players[i]->get_money() +1;//if random bet is to high calculate bet again using the players current money as a constraint

    players[i]->subtract_money(bet);
  }
}
int calc_stats_spaces(shared_ptr<Players> players)//calculates the stats spaces so they are even and line up with the players cards
{
  int lc = players->get_hand_size()*11;//grab how many cards the player has and multiple by 11 since each card is about 11 spaces 
  int str_length=players->get_stats_string_length();//grab the stats string length
  return lc-str_length;//subtract the cards length rom the stats string length
}
int start_display()//display all options for to start the game
{
  int input;
  cout<<"select amount of players you would to play agains"<<endl;
  cout << "[0]: no other players" << endl;
  cout << "[1]: 1 other player" << endl;
  cout << "[2]: 2 other playrs" << endl;
  cout<<"input: ";
  cin>>input;
  return input;


}
void display_rounds(int round)
{
  //1 2 3 4 5 6
  //r o u n d #
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  int terminal_width =  size.ws_col;
  for(int i = 0; i < terminal_width; i++)
    cout<<"-";
  cout<<endl;
  int middle = (terminal_width/2); for(int i = 0; i < middle; i++)
  {
    if(i < middle && i > middle-6)
    {
      cout<<"ROUND: "<<round<<endl;
      break;
    }
    else
      cout<<" ";
  }
  for(int i = 0; i < terminal_width; i++)
    cout<<"-";
  cout<<endl;
}
void display_input_options()
{
  cout << "input either of the following" << endl;
  cout << "[0]: stand" << endl;
  cout << "[1]: hit" << endl;
  cout << "[2]: double down" << endl;
  cout << "input: ";
}
void setup_game(int amount_of_players, vector<shared_ptr<Players>> &players)
{
  string username;
  cout<<"please enter a username: ";
  cin>>username;
  shared_ptr<Players> cur_user(new Players(username,true));
  players.push_back(cur_user);
  for(int i = 1; i <= amount_of_players; i++)
  {
    string player_name = "player"+ to_string(i);
    shared_ptr<Players> p(new Players(player_name,false));
    players.push_back(p);
  }
}
void display_stats(vector<shared_ptr<Players>> players)
{
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  int terminal_width =  size.ws_col;
  int card_spaces = terminal_width/(players.size()+2);
  for(int i = 0; i < players.size(); i++)
  {
    players[i]->calc_score();
    players[i]->print_stats();
    for(int j = 0; j < card_spaces+calc_stats_spaces(players[i]); j++)
      cout<<" ";
  }

  cout<<endl;
}
void print_players_cards(vector<shared_ptr<Players>> players)
{
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  int terminal_width =  size.ws_col;
  int card_spaces = terminal_width/(players.size()+2);
  for(int i = 0; i < LR; i++)
  {
    for(int j = 0; j < players.size(); j++)
    {
      players[j]->display_hand(i);
      for(int k = 0; k < card_spaces; k++)
        cout<<" ";
    }
    cout<<endl;
  }
  display_stats(players);
  for(int i = 0; i < terminal_width; i++)
  {
    cout<<"-";
  }
  cout<<endl;
}
void calc_user_bet(shared_ptr<Players> cur_user)
{
  int bet;
  cout<<"place your bet: ";
  cin>>bet;
  while(bet > cur_user->get_money() || bet < 0)
  {
    cout << "bet must be within your price range!" << endl;
    cout << "Place your bet: ";
    cin.clear();
    cin>>bet;
  }
  cur_user->subtract_money(bet);
}
void player_inputs(vector<shared_ptr<Players>> players,Dealer dealer)
{
  enum options{stand,hit,double_down};
  for(int i = 1; i < (int)players.size(); i++)
  {
    int input = players[i]->player_input();
    int bet = players[i]->get_bet();
    while(input != stand)
    {
      switch(input)
      {
        case hit:
          dealer.handout_cards(players[i]);
          players[i]->calc_score();
          break;
        case double_down:
          players[i]->subtract_money(bet);
          break;
        default:
          cerr<<"something went wrong with inputs"<<endl;
          break;
      }
      players[i]->calc_score();
      input = players[i]->player_input();
    }
  }
}
void cur_user_input(vector<shared_ptr<Players>> players,Dealer dealer)
{
  shared_ptr<Players> cur_user=players[0];
  int input = -1;
  int bet = cur_user->get_bet();
  enum options{stand,hit,double_down};
  bool check_double_down = false;
  while(input != stand && cur_user->get_score() < 21)
  {
    display_input_options();
    cin>>input;
    cur_user->calc_score();
    switch(input)
    {
      case hit:
        dealer.handout_cards(cur_user);
        break;
      case double_down:
        if(check_double_down)
          cout<<"ALREADY DOUBLED DOWN"<<endl;
        else
        {
          check_double_down = true;
          cur_user->subtract_money(bet);
        }
        break;
      case stand:
        break;
      default: 
        cerr<<"Must pick one of the options"<<endl;
        break;
    }
    dealer.display_hand_dealer();
    print_players_cards(players);
    cur_user->calc_score();
  }
  if(cur_user->get_score() > 21)
    cout<<"YOU BUST"<<endl;
  if(cur_user->get_score() == 21 && cur_user->get_hand_size() == 2)
    cout<<"YOU GOT BLACKJACK"<<endl;
}
void calc_winner(Dealer dealer, vector<shared_ptr<Players>> players)
{
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  int terminal_width =  size.ws_col;
  int card_spaces = terminal_width/(players.size()+2);
  int dealer_score = dealer.get_score();

  for(int i = 0; i < (int)players.size(); i++)
  {
    players[i]->calc_score();
    string player_name = players[i]->get_name();
    string won= player_name +" WON";
    string tie= player_name +" TIED";
    string lost= player_name + " LOST";
    string bust= player_name +" BUST";
    int player_score = players[i]->get_score();
    int lc = players[i]->get_hand_size()*11;
    int spaces = 0;
    int bet = players[i]->get_bet();
    //    cout<<players[i]->get_name()<<" bet: "<<bet<<endl;
    bool double_down = players[i]->get_double_down();
    if(player_score < dealer_score && dealer_score <= 21)
    {
      spaces = lc - (int)lost.size();
      cout<<lost;
    }
    else if(player_score == dealer_score && dealer_score <= 21 && player_score <= 21)
    {
      players[i]->add_money(bet);
      spaces = lc - (int)tie.size();
      cout<<tie;
    }
    else if((player_score <= 21 && player_score > dealer_score) || (dealer_score > 21 && player_score <= 21)){ 
      if(double_down)
        players[i]->add_money((bet*3));
      else
        players[i]->add_money(bet*2);
      spaces = lc - (int)won.size();
      cout<<won;
    }
    else if(player_score > 21)
    {
      spaces = lc-(int)bust.size();
      cout<<bust;
    }
    else
      cerr<<"SOMETHING WENT WRONG"<<endl;
    for(int j = 0; j < card_spaces+spaces; j++)
      cout<<" ";
  }
  cout<<endl;
  for(int i = 0; i < (int)players.size(); i++)
  {
    string player_name = players[i]->get_name();
    string str_bet = to_string(players[i]->get_bet());
    bool double_down = players[i]->get_double_down();
    string amount_bet;
    if(double_down)
      amount_bet = player_name + " amount bet: " +  str_bet + " player doubled down";
    else
      amount_bet = player_name + " amount bet: " +  str_bet ; 
    int lc = players[i]->get_hand_size()*11;
    int amount_bet_spaces = lc - (int)amount_bet.size();
    cout<<amount_bet;
    for(int j = 0; j < card_spaces+amount_bet_spaces; j++)
      cout<<" ";
  }
  cout<<endl;
  display_stats(players);
}
int main()
{
  int amount_of_players = start_display();
  vector<shared_ptr<Players>> players;
  setup_game(amount_of_players,players);
  players[0]->print_stats();
  cout<<" ";
  cout<<endl;
  Deck deck(1);
  deck.create_deck();
  deck.shuffle_deck();
  Dealer dealer(deck,players);
  int rounds = 1;
  while(1)
  {
    display_rounds(rounds);
    if(players.size() > 1)
      calc_bets(players);
    calc_user_bet(players[0]);
    dealer.begin_round();
    dealer.display_hand_dealer();
    player_inputs(players,dealer);
    print_players_cards(players);
    cur_user_input(players,dealer);
    dealer.draw_cards();
    cout<<"dealer score: "<<dealer.get_score()<<endl;
    print_players_cards(players);
    calc_winner(dealer,players);
    dealer.clear_table();
    rounds++;
  }
  return 0;
}
