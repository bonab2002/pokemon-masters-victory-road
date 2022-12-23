#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Point2D.h"
#include <iostream>
using namespace std;

class GameObject
{
public:
	GameObject(char);
	GameObject(Point2D, int, char);
	virtual ~GameObject(); //add
	Point2D GetLocation();
	int GetId();
	char GetState();
	virtual void ShowStatus();
	virtual bool Update() = 0; //add
	virtual bool ShouldBeVisible() = 0; //add 
	void DrawSelf(char*);
protected:
	Point2D location;
	int id_num;
	char display_code;
	char state;
};
#endif
