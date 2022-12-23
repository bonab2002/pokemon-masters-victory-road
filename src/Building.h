#ifndef BUILDING_H
#define BUILDING_H
#include "GameObject.h"

class Building : public GameObject
{
	public:
		Building();
		Building(char, int, Point2D);
		void AddOneTrainer();
		void RemoveOneTrainer();
		void ShowStatus();
		bool ShouldBeVisible();
	private:
		unsigned int trainer_count;
};
#endif
