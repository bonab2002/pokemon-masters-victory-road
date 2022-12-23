#include "PokemonCenter.h"

PokemonCenter::PokemonCenter()
{
	display_code = 'C';
	potion_capacity = 100;
	num_potions_remaining = potion_capacity;
	pokedollar_cost_per_potion = 5;
	state = POTIONS_AVAILABLE;
	cout << "PokemonCenter default constructed" << endl;
}
PokemonCenter::PokemonCenter(int in_Id, double potion_cost, unsigned int potion_cap, Point2D in_loc)
{
	id_num = in_Id;
	location = in_loc;
	display_code = 'C';
	pokedollar_cost_per_potion = potion_cost;
	potion_capacity = potion_cap;
	num_potions_remaining = potion_capacity;
	cout << "PokemonCenter constructed" << endl;
	state = POTIONS_AVAILABLE;
}
PokemonCenter::~PokemonCenter()
{
	cout << "PokemonCenter destructed" << endl;
}
bool PokemonCenter::HasPotions()
{
	if (num_potions_remaining >= 1)
	{
		return true;
	}
	return false;
}
unsigned int PokemonCenter::GetNumPotionRemaining()
{
	return num_potions_remaining;
}
bool PokemonCenter::CanAffordPotion(unsigned int potion, double budget)
{
	if (pokedollar_cost_per_potion * potion > budget)
	{
		return false;
	}
	return true;
}
double PokemonCenter::GetPokeDollarCost(unsigned int potion)
{
	return pokedollar_cost_per_potion * potion;
}
unsigned int PokemonCenter::DistributePotion(unsigned int potion_needed)
{
	if (num_potions_remaining >= potion_needed)
	{
		num_potions_remaining -= potion_needed;
		return num_potions_remaining;
	}
	unsigned int ret = num_potions_remaining;
	num_potions_remaining = 0;
	return ret;
}
bool PokemonCenter::Update()
{
	if (num_potions_remaining == 0)
	{
		state = NO_POTIONS_AVAILABLE;
		display_code = 'c';
		cout << "PokemonCenter " << id_num << " has ran out of potions." << endl;
		return true;
	}
	return false;
}
void PokemonCenter::ShowStatus()
{
	cout << "PokemonCenter Status: ";
	Building::ShowStatus();
	cout << "PokeDollars per potion: " << pokedollar_cost_per_potion << " has " << num_potions_remaining << " potion(s) remaining." << endl;
}
