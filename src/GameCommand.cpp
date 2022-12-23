#include "GameCommand.h"
#include <string>

void DoMoveCommand(Model& model, int trainer_id, Point2D p1)
{
	Trainer* temp = model.GetTrainerPtr(trainer_id);
	if (temp == 0)
	{
		throw Invalid_Input("Please select valid trainer");
	}
	if (p1.x > 20 || p1.y > 20 || p1.x < 0 || p1.y < 0)
	{
		throw Invalid_Input("Please enter a valid point on the grid");
	}
	else
	{
		temp->StartMoving(p1);
		temp->ShowStatus();
		cout << "Moving " << temp->GetName() << " to " << p1 << endl;
	}
}
void DoMoveToCenterCommand(Model& model, int trainer_id, int center_id)
{
	Trainer* temp = model.GetTrainerPtr(trainer_id);
	PokemonCenter* cen = model.GetPokemonCenterPtr(center_id);
	if (temp == 0 || cen == 0)
	{
		throw Invalid_Input("Please select valid center/trainer");
	}
	else
	{
		temp->StartMovingToCenter(cen);
		temp->ShowStatus();
		cout << "Moving " << temp->GetName() << " to pokemon center " << center_id << endl;
	}
}
void DoMoveToGymCommand(Model& model, int trainer_id, int gym_id)
{
	Trainer* temp = model.GetTrainerPtr(trainer_id);
	PokemonGym* gym = model.GetPokemonGymPtr(gym_id);
	if (temp == 0 || gym == 0)
	{
		throw Invalid_Input("Please select valid gym/trainer");
	}
	else
	{
		temp->StartMovingToGym(gym);
		temp->ShowStatus();
		cout << "Moving " << temp->GetName() << " to pokemon gym " << gym_id << endl;
	}
}
void DoStopCommand(Model& model, int trainer_id)
{
	Trainer* temp = model.GetTrainerPtr(trainer_id);
	if (temp == 0)
	{
		throw Invalid_Input("Please select valid trainer to stop");
	}
	else
	{
		temp->Stop();
		temp->ShowStatus();
		cout << "Stopping " << temp->GetName() << endl;
	}
}
void DoBattleCommand(Model& model, int trainer_id, unsigned int battles)
{
	Trainer* temp = model.GetTrainerPtr(trainer_id);
	if (temp == 0)
	{
		throw Invalid_Input("Please select valid trainer to battle with");
	}
	if (battles <= 0)
	{
		throw Invalid_Input("Please enter valid number of battles");
	}
	else
	{
		temp->StartBattling(battles);
		temp->ShowStatus();
	}
}
void DoRecoverInCenterCommand(Model& model, int trainer_id, unsigned int potions_needed)
{
	Trainer* temp = model.GetTrainerPtr(trainer_id);
	if (temp == 0)
	{
		throw Invalid_Input("Please select valid trainer to recover");
	}
	if (potions_needed <= 0)
	{
		throw Invalid_Input("Please enter valid number of potions");
	}
	else
	{
		temp->StartRecoveringHealth(potions_needed);
		temp->ShowStatus();
	}
}
void DoAdvanceCommand(Model& model, View& view) //fix
{
	model.Model::Update();
	model.Model::ShowStatus();
	model.Model::Display(view);
	cout << "Advancing one tick." << endl;
}
void DoRunCommand(Model& model, View& view) //fix
{
	int startTime = model.GetTime();
	for (int i = 0; i < 5; i++)
	{
		model.Model::Update();
	}
	model.Model::ShowStatus();
	model.Model::Display(view);
	cout << "Advancing to next event." << endl;
}
