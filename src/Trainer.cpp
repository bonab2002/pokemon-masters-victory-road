#include "Trainer.h"
#include <stdlib.h> 
#include <ctime>
#include <math.h>
#include <string>

Trainer::Trainer():GameObject('T')
{
	is_at_center = false;
	is_IN_GYM = false;
	health = 20;
	experience = 0;
	PokeDollars = 0;
	battles_to_buy = 0;
	potions_to_buy = 0;
	current_center = NULL;
	current_gym = NULL;
	speed = 5;
	cout << "Trainer default constructed" << endl;
}

Trainer::Trainer(char in_code):GameObject('T')
{
	speed = 5;
	state = STOPPED;
	display_code = in_code;
	is_at_center = false;
	is_IN_GYM = false;
	health = 20;
	experience = 0;
	PokeDollars = 0;
	battles_to_buy = 0;
	potions_to_buy = 0;
	current_center = NULL;
	current_gym = NULL;
	cout << "Trainer constructed" << endl;
}
Trainer::Trainer(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc):GameObject('T')
{
	is_at_center = false;
	is_IN_GYM = false;
	health = 20;
	experience = 0;
	PokeDollars = 0;
	battles_to_buy = 0;
	potions_to_buy = 0;
	current_center = NULL;
	current_gym = NULL;
	speed = in_speed;
	name = in_name;
	display_code = in_code;
	location = in_loc;
	id_num = in_id;
	cout << "Trainer constructed" << endl;
}

string Trainer::GetName()
{
	return name;
}
Trainer::~Trainer()
{
	cout << "Trainer destructed" << endl;
}

void Trainer::StartMoving(Point2D dest)
{
	Trainer::SetupDestination(dest);
	state = MOVING;

	if (location.x == destination.x && location.y == destination.y )
	{
		cout << display_code << id_num << ": I'm already there. See?" << endl;
	}
	else if (HasFainted())
	{
		cout << display_code << id_num << ": My pokemon have fainted. I may move but you cannot see me." << endl;
	}
	else
	{
		cout << display_code << id_num << ": On my way." << endl;
		if (is_at_center)
		{
			is_at_center = false;
			current_center->RemoveOneTrainer();
		}
		if (is_IN_GYM)
		{
			is_IN_GYM = false;
			current_gym->RemoveOneTrainer();
		}
	}
}

void Trainer::StartMovingToGym(PokemonGym* gym)
{
	Trainer::SetupDestination(gym->GetLocation());

	if ((gym->GetLocation().x == location.x && gym->GetLocation().y == location.y))
	{
		cout << display_code << id_num << ": I am already at the PokemonGym!" << endl;
	}
	else if (HasFainted())
	{
		cout << display_code << id_num << ": My pokemon have fainted so I can't move to gym..." << endl;
	}
	else
	{
		cout << display_code << id_num << ": on my way to gym "<<(*gym).GetId() << endl;
		current_gym = gym;
		state = MOVING_TO_GYM;
		if (is_at_center)
		{
			is_at_center = false;
			current_center->RemoveOneTrainer();
		}
	}
}
void Trainer::StartMovingToCenter(PokemonCenter* center)
{
	Trainer::SetupDestination((*center).GetLocation());
	if (center->GetLocation().x == location.x && (*center).GetLocation().y == location.y )
	{
		cout << display_code << id_num << ": I am already at the PokemonCenter!" << endl;
	}
	else if (HasFainted())
	{
		cout << display_code << id_num << ": My pokemon have fainted so I should have gone to the center..." << endl;
	}
	else
	{
		cout << display_code << id_num << ": on my way to center " << (*center).GetId() << endl;
		current_center = center;
		state = MOVING_TO_CENTER;
		if (is_IN_GYM)
		{
			is_IN_GYM = false;
			current_gym->RemoveOneTrainer();
		}
	}
}
void Trainer::StartBattling(unsigned int num_battles)
{
	if (HasFainted())
	{
		cout << display_code << id_num << ": My Pokemon have fainted so no more battles for me..." << endl;
	}
	else if (is_IN_GYM == false)
	{
		cout << display_code << id_num << ": I can only battle in a PokemonGym!" << endl;
	}
	else if(current_gym->GetPokeDollarCost(num_battles)> PokeDollars)
	{
		cout << display_code << id_num << ": Not enough money for battles." << endl;
	}
	else if (current_gym->GetNumBattlesRemaining() == 0)
	{
		cout << display_code << id_num << ": Cannot battle! This PokemonGym has no more trainers to battle!" << endl;
	}
	else
	{
		state = BATTLING_IN_GYM;
		unsigned int temp = current_gym->GetNumBattlesRemaining();
		int total = temp - num_battles;
		if (total < 0)
		{
			battles_to_buy = temp;
			cout << display_code << id_num << ": Started to battle at the PokemonGym " << (*current_gym).GetId() << " with " << temp << " battles" << endl;
		}
		else
		{
			battles_to_buy = num_battles;
			cout << display_code << id_num << ": Started to battle at the PokemonGym " << (*current_gym).GetId() << " with " << num_battles << " battles" << endl;
		}
	}
}
void Trainer::StartRecoveringHealth(unsigned int num_potions)
{
	if (current_center->GetPokeDollarCost(num_potions) > PokeDollars)
	{
		cout << display_code << id_num << ": Not enough money to recover health." << endl;
	}
	else if (current_center->GetNumPotionRemaining() == 0)
	{
		cout << display_code << id_num << ": Cannot recover! No potion remaining in this PokemonCenter" << endl;
	}
	else if (is_at_center == false)
	{
		cout << display_code << id_num << ": I can only recover health at a PokemonCenter!" << endl;
	}
	else
	{
		state = RECOVERING_HEALTH;
		potions_to_buy = num_potions; //check
		current_center->DistributePotion(potions_to_buy);
		cout << display_code << id_num << ": Started recovering " << num_potions << " at PokemonCenter " << (*current_center).GetId() << endl;
	}
}
void Trainer::Stop()
{
	state = STOPPED;
	cout << display_code << id_num << ": Stopping..." << endl;
}
bool Trainer::HasFainted()
{
	if (health <= 0)
	{
		return true;
	}
	return false;
}
bool Trainer::ShouldBeVisible()
{
	if (!HasFainted())
	{
		return true;
	}
	return false;
}
void Trainer::ShowStatus()
{
	cout << name << "status: ";
	GameObject::ShowStatus();
	switch (state)
	{
	case STOPPED:
		cout << display_code << id_num << ": Stopped" << endl;
		cout << "Health: " << health << endl;
		cout << "PokeDollars: " << PokeDollars << endl;
		cout << "Experience: " << experience << endl;
		break;
	case MOVING:
		cout << display_code << id_num << ": Moving at a speed of " << speed << " to destination " << destination << " at each step of " << delta << "." << endl;
		cout << "Health: " << health << endl;
		cout << "PokeDollars: " << PokeDollars << endl;
		cout << "Experience: " << experience << endl;
		break;
	case MOVING_TO_GYM:
		cout << display_code << id_num << ": Heading to PokemonGym " << current_gym->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
		cout << "Health: " << health << endl;
		cout << "PokeDollars: " << PokeDollars << endl;
		cout << "Experience: " << experience << endl;
		break;
	case MOVING_TO_CENTER:
		cout << display_code << id_num << ": Heading to PokemonCenter " << current_center->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
		cout << "Health: " << health << endl;
		cout << "PokeDollars: " << PokeDollars << endl;
		cout << "Experience: " << experience << endl;
		break;
	case IN_GYM:
		cout << display_code << id_num << ": Inside PokemonGym " << current_gym->GetId() << endl;
		cout << "Health: " << health << endl;
		cout << "PokeDollars: " << PokeDollars << endl;
		cout << "Experience: " << experience << endl;
		break;
	case AT_CENTER:
		cout << display_code << id_num << ": Inside PokemonCenter " << current_center->GetId() << endl;
		cout << "Health: " << health << endl;
		cout << "PokeDollars: " << PokeDollars << endl;
		cout << "Experience: " << experience << endl;
		break;
	case BATTLING_IN_GYM:
		cout << display_code << id_num << ": Battling in PokemonGym " << current_gym->GetId() << endl;
		cout << "Health: " << health << endl;
		cout << "PokeDollars: " << PokeDollars << endl;
		cout << "Experience: " << experience << endl;
		break;
	case RECOVERING_HEALTH:
		cout << display_code << id_num << ": Recovering health in PokemonCenter " << (*current_center).GetId() << endl;
		cout << "Health: " << health << endl;
		cout << "PokeDollars: " << PokeDollars << endl;
		cout << "Experience: " << experience << endl;
		break;
	}
}
bool Trainer::Update()
{
	bool arrived;
	switch (state)
	{
	case STOPPED:
		return false;
		break;
	case MOVING:
		arrived = Trainer::UpdateLocation();
		if (arrived)
		{
			state = STOPPED;
			return true;
		}
		break;
	case MOVING_TO_GYM:
		arrived = Trainer::UpdateLocation();
		if (arrived)
		{
			state = IN_GYM;
			is_IN_GYM = true;
			return true;
		}
		break;
	case MOVING_TO_CENTER:
		arrived = Trainer::UpdateLocation();
		if (arrived)
		{
			state = AT_CENTER;
			is_at_center = true;
			return true;
		}
		break;
	case IN_GYM:
		return false;
		break;
	case AT_CENTER:
		return false;
		break;
	case BATTLING_IN_GYM:
		health -= current_gym->GetHealthCost(battles_to_buy);
		PokeDollars -= current_gym->GetPokeDollarCost(battles_to_buy);
		unsigned int expGained;
		expGained = current_gym->TrainPokemon(battles_to_buy);
		experience += expGained;
		cout << "** " << name << " completed " << battles_to_buy << " battle(s)! **" << endl;
		cout << "** " << name << " gained " << expGained << " experience! **" << endl;
		state = IN_GYM;
		return true;
	case RECOVERING_HEALTH:
		int oldHealth = health;
		health += 5 * potions_to_buy;
		int recovered = health - oldHealth;
		PokeDollars -= current_center->GetPokeDollarCost(potions_to_buy);
		cout << "** " << name << " recovered " << recovered << " health! **" << endl;
		cout << "** " << name << " bought " << potions_to_buy << " potion(s)! **" << endl;
		state = AT_CENTER;
		return true;
	}
	if (health <= 0)
	{
		cout << name << " is out of health and can't move" << endl;
		state = FAINTED;
	}
}
bool Trainer::UpdateLocation()
{
	int situation;
	if ( destination.x >= location.x && destination.x >= location.y) situation = 0;
	if ( destination.x < location.x && destination.x < location.y) situation = 1;
	if ( destination.x >= location.x && destination.x < location.y) situation = 2;
	if ( destination.x < location.x && destination.x >= location.y) situation = 3;
	location.x += delta.x;
	location.y += delta.y;

	health--;
	PokeDollars += GetRandomAmountOfPokeDollars();
	cout << display_code << id_num << ": Moved to given location" << endl;

	switch(situation) 
	{
	  case 0:

		if ( destination.x <= location.x && destination.y <= location.y)
		{
			location.x = destination.x;
			location.y = destination.y;
			cout << display_code << id_num << ": I'm there!" << endl;
			if (state == MOVING_TO_GYM) current_gym->AddOneTrainer();
			if (state == MOVING_TO_CENTER ) current_center->AddOneTrainer();
			return true;
		} else if( destination.x >= location.x && destination.y >= location.y)
		{
			cout << display_code << id_num << ": step..." << endl;
			return false;
		}
	  case 1:
	  	if ( destination.x >= location.x && destination.y >= location.y)
		{
			location.x = destination.x;
			location.y = destination.y;
			cout << display_code << id_num << ": I'm there!" << endl;
			if (state == MOVING_TO_GYM) current_gym->AddOneTrainer();
			if (state == MOVING_TO_CENTER ) current_center->AddOneTrainer();
			return true;
		} else if( destination.x <= location.x && destination.y <= location.y)
		{
			cout << display_code << id_num << ": step..." << endl;
			return false;
		}
	  case 2:
		if ( destination.x <= location.x && destination.y >= location.y)
		{
			location.x = destination.x;
			location.y = destination.y;
			cout << display_code << id_num << ": I'm there!" << endl;
			if (state == MOVING_TO_GYM) current_gym->AddOneTrainer();
			if (state == MOVING_TO_CENTER ) current_center->AddOneTrainer();
			return true;
		} else if( destination.x >= location.x && destination.y <= location.y)
		{
			cout << display_code << id_num << ": step..." << endl;
			return false;
		}
	  case 3:
		if ( destination.x <= location.x && destination.y >= location.y)
		{
			location.x = destination.x;
			location.y = destination.y;
			cout << display_code << id_num << ": I'm there!" << endl;
			if (state == MOVING_TO_GYM) current_gym->AddOneTrainer();
			if (state == MOVING_TO_CENTER ) current_center->AddOneTrainer();
			return true;
		} else if( destination.x <= location.x && destination.y >= location.y)
		{
			cout << display_code << id_num << ": step..." << endl;
			return false;
		}
	}

}
void Trainer::SetupDestination(Point2D dest)
{
	delta = (dest - location) * ((double)speed / GetDistanceBetween(dest, location));
	destination = dest;
}

double GetRandomAmountOfPokeDollars()
{
	srand(time(NULL));
	double randNum = ((double)rand()) / ((double)RAND_MAX) * 2.0;
	return randNum;

}
void Trainer::LoseHealth(double amount)
{
	health -= amount;
}
