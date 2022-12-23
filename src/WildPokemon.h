#include "Trainer.h"
#include <string>
#include <iostream>

enum WildPokemonStates
{
	IN_ENVIRONMENT = 0,
	DEAD = 1,
	IN_TRAINER = 2
};
class WildPokemon : public GameObject
{
protected:
	double attack;//define vals where?
	double health;
	bool variant;
	bool in_combat;
	string name;
	Trainer* current_trainer;
	Vector2D delta;
	Point2D destination;
public:
	WildPokemon(string, double, double, bool, int, Point2D);
	void follow(Trainer* t);
	bool get_variant();
	double get_attack();
	double get_health();
	bool get_in_combat();
	bool Update();
	void ShowStatus();
	bool isAlive();
	void SetupDestination(Point2D);
	bool ShouldBeVisible();
	bool UpdateLocation();
	double randomlocation();
};
