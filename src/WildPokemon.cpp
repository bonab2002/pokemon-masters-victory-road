
#include "WildPokemon.h"
#include <time.h>
#include <stdlib.h>
#include<math.h>

WildPokemon::WildPokemon(string in_name, double in_attack, double in_health, bool in_variant, int in_id, Point2D in_loc) : GameObject(in_loc, in_id, 'W')
{
	name = in_name;
	health = in_health;
	variant = in_variant;
	id_num = in_id;
	location = in_loc;
	current_trainer = 0;
	state = IN_ENVIRONMENT;
}
void WildPokemon::follow(Trainer* t)
{
	current_trainer = t;
	state = IN_TRAINER;
	destination = t->GetLocation();
}
bool WildPokemon::get_variant()
{
	return variant;
}
double WildPokemon::get_attack()
{
	return attack;
}
double WildPokemon::get_health()
{
	return health;
}
bool WildPokemon::get_in_combat()
{
	return in_combat;
}
bool WildPokemon::Update()
{
	if (!isAlive())
	{
		state = DEAD;
	}
	switch (state)
	{
	case IN_ENVIRONMENT:
	{
		UpdateLocation();
		return false;
		break;
	}
	case DEAD:
	{
		return false;
		break;
	}
	case IN_TRAINER:
	{
		location = current_trainer->GetLocation();
		if (UpdateLocation())
		{
			current_trainer->LoseHealth(attack);
			return true;
		}
		return false;
		break;
	}
	}
	
}
void WildPokemon::ShowStatus()
{
	cout << "WildPokemon status: " << endl;
	GameObject::ShowStatus();
	switch (state)
	{
	case IN_ENVIRONMENT:
	{
		cout << display_code << id_num << " is alive and in environment" <<endl;
		break;
	}
	case DEAD:
	{
		cout << display_code << id_num << " is dead" << endl;
		break;
	}
	case IN_TRAINER:
	{
		cout << display_code << id_num << " is in trainer" << endl;
		break;
	}
	}

}
bool WildPokemon::isAlive()
{
	if (health <= 0)
	{
		return false;
	}
	return true;
}
void WildPokemon::SetupDestination(Point2D dest)
{
	destination = dest;
	delta = (dest - location) * (2 / GetDistanceBetween(destination, location));
}
bool WildPokemon::ShouldBeVisible()
{
	if (!isAlive())
	{
		return false;
	}
	return true;
}
bool WildPokemon::UpdateLocation()
{
	if (fabs((destination - location).x) <= fabs(delta.x) && fabs((destination - location).y) <= fabs(delta.y)) 
	{ 
		location = destination;
		return true;
	}
	else if (location.x == destination.x && location.y == destination.y) 
	{
		return true;
	}
	else 
	{
		if (fabs((destination - location).x) <= fabs(delta.x)) 
		{
			location.x = destination.x;
			location.y = location.y + delta.y;
		}
		else if (fabs((destination - location).y) <= fabs(delta.y))
		{
			location.x = location.x + delta.x;
			location.y = destination.y;
		}
		else if (fabs((destination - location).x) > fabs(delta.x) && fabs((destination - location).y) > fabs(delta.y)) 
		{
			location.x = location.x + delta.x;
			location.y = location.y + delta.y;
		}
		cout << display_code << id_num << ": step" << endl;
		return false;
	}

}

double WildPokemon::randomlocation()
{
	srand(time(NULL));
	double randNum = ((double)rand()) / ((double)RAND_MAX) * 2.0;
	return ((double)rand()) / ((double)RAND_MAX) * 20.0;
}
