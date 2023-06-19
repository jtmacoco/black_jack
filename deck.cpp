#include "deck.h"
void Deck::print_deck()//print all the cards in the deck vertically
{
  for(int i = 0; i < decks.size(); i++)
  {
    decks[i]->print_card_vertical();
  }
}
void Deck::create_deck()//create the deck of cards
{
  enum suit_types{hearts,spades,clubs,diamonds};//enum allows for easier and more readable code when setting the suit type
  char suits = ' ';//intilze empty varaible for suits
  for(int i = 0; i < deck_amount; i++)
  {
    for(int suit = hearts; suit <= diamonds; suit++)
    {
      suit_types st = static_cast<suit_types>(suit);
      switch(st)//switch st based on the enum value basically go through all the suit types
      {
        case hearts:
          suits='h';
          break;
        case spades:
          suits='s';
          break;
        case clubs:
          suits='c';
          break;
        case diamonds:
          suits='d';
          break;
        default:
          cerr<<"something went wrong when generating deck"<<endl;
          break;
      }
      for(int j = 1; j <=13; j++)//loop through 13 times for the 13 cards per suit
      {
        shared_ptr<Cards> card( new Cards());
        card->edit_cards(suits,j);
        decks.push_back(card);
      }
    }
  }
}
shared_ptr<Cards> Deck::get_card()
{
  shared_ptr<Cards> top_card = decks.front();//draw a card from the top of the deck
  decks.erase(decks.begin());//erase the top element from the deck
  decks.shrink_to_fit();
  return top_card;
}
void Deck::add_card_back(shared_ptr<Cards> card)
{
  decks.push_back(card);
}
void Deck::shuffle_deck()
{
  random_device rd;
  mt19937 g(rd());
  shuffle(decks.begin(),decks.end(),g);
}
int Deck::get_size()
{
  return decks.size();
}
Deck::~Deck()//make sure to delete all the cards when done
{

}

