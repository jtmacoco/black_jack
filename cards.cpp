#include "cards.h"
#define c_value_pos 12
void Cards::print_card(int index)//this function will print the cards side by side.
{
  switch(index)
  {
    case 0: cout<<rows[0]<<" ";//print the first row of the card:   **********
      break;
    case 1:
      cout<<rows[1]<<" ";//print the second row of the card:        *n       *
      break;
    case 2:
      cout<<rows[2]<<" ";//print the third row of the card:         *        * 
      break;
    case 3:
      cout<<rows[3]<<" ";//print the fourth row of the card:        *   s    *
      break;
    case 4:
      cout<<rows[4]<<" ";//print the fith row of the card:          *        *
      break;
    case 5:
      cout<<rows[5]<<" ";//print the sixth row of the card:         *       z*
      break;
    case 6:
      cout<<rows[6]<<" ";//print the seventh row of the card:       **********
      break;
    default:
      cerr<<"something went wrong when printing the cards"<<endl;//if for some reason the defualt case is hit display an error
      break;
  }
}
void Cards::set_card_rows()
{
  if(!rows.empty())
    rows.clear();//make sure the the rows vector is empty.
  stringstream ss(card);//this allows for the manipulation of a string as if it were a stream like an input or output stream.
  string card_row;
  while(getline(ss,card_row,'\n'))//read the string until it hits the delimeter then push the portion of the string onto the vector.
    rows.push_back(card_row);//This will split up the card into rows which makes printing cards side by side easier.
}
void Cards::set_blank_card_rows()
{
  if(!rows.empty())
    rows.clear();//make sure the the rows vector is empty;
  stringstream ss(blank_card);//this allows for the manipulation of a string as if it were a stream like an input or output stream
  string card_row;
  while(getline(ss,card_row,'\n'))//read the string until it hits the delimeter then push the portion of the string onto the vector. 
    rows.push_back(card_row);//This will split up the card into rows which makes printing cards side by side easier.
}
void Cards::edit_cards(char suit,int card_value)
{
  //  below are examples of finding the position of the identifiers that will be used to edit the cards
  //  int pos1 = card.find("n");//12
  //  int pos3 = card.find("s");//37
  //  int pos2 = card.find("z");//63
  card[37] = suit;
  for(int i = 12; i < card.size(); i++)//start at 12 since it's the position of the first identifier and no need to start loop form 0
  {
    if((card_value == 1 && card[i] == 'n' ) || (card_value == 1 && card[i] == 'z'))//check if card[i] is an identifer if so replace with card value
    {                                                                             
      card[i]='a';//set value to a for ace
    }
    else if ((card_value == 11 && card[i] == 'n') || (card_value == 11 && card[i] == 'z'))//split into 2 diffent if statements for readability
    {
      card[i]='j';
    }
    else if ((card_value == 12 && card[i] == 'n') || (card_value == 12 && card[i] == 'z'))
    {
      card[i]='q';
    }
    else if ((card_value == 13 && card[i] == 'n') || (card_value == 13 && card[i] == 'z'))
    {
      card[i]='k';
    }
    else if((card_value < 10 && card[i] == 'n') || (card_value < 10 && card[i] == 'z'))
      card[i]=card_value+'0';//convert the number into a character instead of having the number read as an asci value
    else if(card_value == 10 && card[i] == 'n')//if the card value is 10, the placement of two characters is needed
    {
      card[i]='1';
      card[i+1]='0';
    }
    else if(card_value == 10 && card[i] == 'z')//I split this up into 2 seperate if statements for readability this can be combined into 1 statement
    {
      card[i-1] ='1';
      card[i]='0';
    }
  }
}
int Cards::card_value(bool cur_user, int total)
{
  int card_value = -1;//intilize variables
  bool first_input = true;
  if(card[c_value_pos] == 'a' && cur_user)// check if the card is an ace and if it's the current user's card, if so prompt user to choose a value
  {
    if(ace)//this is to make sure cur_user isn't prompt more than once for the ace value
      return card_value_ace;
    while(!ace)
    {
      if(card_value == 1)//check if the input value 1
      {
        ace = true;
        card_value_ace = card_value;
        return card_value;
      }
      else if(card_value == 11)//check if input value is 11
      { 
        ace = true;
        card_value_ace = card_value;
        return card_value;
      }
      else if(first_input)//if it's first input prmpt user
      {
        cout<<"would you like the ace value to be a 1 or 11?"<<endl;
        cin>>card_value;
        first_input = false;
      }
      else{//if input any value other than 1 or 11 then prompt user to pick correct value
        cout<<"you must pick 1 or 11 as the value"<<endl;
        cin>>card_value;
      }
    }
  }
  else if(card[c_value_pos] == 'a' && !cur_user)//check if card is an ace and not the current user
  {
    if((total + 11) > 21)//have ace value be 1 or 11 based on the current total of players hand
      card_value = 1;
    else
      card_value = 11;
  }
  else if(card[c_value_pos] == '2')//check the rest of the card values
    card_value = 2;
  else if(card[c_value_pos] == '3')
    card_value = 3;
  else if(card[c_value_pos] == '4')
    card_value = 4;
  else if(card[c_value_pos] == '5')
    card_value = 5;
  else if(card[c_value_pos] == '6')
    card_value = 6;
  else if(card[c_value_pos] == '7')
    card_value = 7;
  else if(card[c_value_pos] == '8')
    card_value = 8;
  else if(card[c_value_pos] == '9')
    card_value = 9;
  else if(card[c_value_pos] == '1')
    card_value = 10;
  else if(card[c_value_pos] == 'j' || card[c_value_pos] == 'q' || card[c_value_pos] == 'k')
    card_value = 10;
  else{
    cerr<<"something went wrong when trying to get the card value"<<endl;
    return -1;
  }
  return card_value;
    
}
void Cards::print_card_vertical()
{
  cout<<card<<endl;
}
