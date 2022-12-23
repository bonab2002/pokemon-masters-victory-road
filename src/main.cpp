#include <iostream>
#include "GameCommand.h"

using namespace std;

int main()
{
	Model model = Model();
	View view;
	View display = View();
	model.Display(display);
	char command;
	while (true)
	{
		bool check = true;

		int id, x, y, potion_amount, battle_amount, id1, id2;
		char type;
		cout << "Please enter your command: ";
		cin >> command;
		try {
			switch (command)
			{
			case 'm':
			{
				if(!(cin >> id))
				{
					throw Invalid_Input("Was expecting int");//None of these exceptions work, they just sent into infinite loop, not sure why
					exit(0);
				}
				if (!(cin >> x))
				{
					throw Invalid_Input("Was expecting int");
					exit(0);
				}
				if (!(cin >> y))
				{
					throw Invalid_Input("Was expecting int");
					exit(0);
				}
				DoMoveCommand(model, id, Point2D(x, y));
				break;
			}
			case 'c':
			{
				if (!(cin >> id1))
				{
					throw Invalid_Input("Was expecting int");
					exit(0);
				}
				if (!(cin >> id2))
				{
					throw Invalid_Input("Was expecting int");
					exit(0);
				}
				DoMoveToCenterCommand(model, id1, id2);
				break;
			}
			case 'g':
			{
				if (!(cin >> id1))
				{
					throw Invalid_Input("Was expecting int");
					exit(0);
				}
				if (!(cin >> id2))
				{
					throw Invalid_Input("Was expecting int");
					exit(0);
				}
				DoMoveToGymCommand(model, id1, id2);
				break;
			}
			case 'p':
			{
				if (!(cin >> id1))
				{
					throw Invalid_Input("Was expecting int");
					exit(0);
				}
				if (!(cin >> potion_amount))
				{
					throw Invalid_Input("Was expecting int");
					exit(0);
				}
				DoRecoverInCenterCommand(model, id, potion_amount);
				break;
			}
			case 'b':
			{
				if (!(cin >> id1))
				{
					throw Invalid_Input("Was expecting int");
					exit(0);
				}
				if (!(cin >> battle_amount))
				{
					throw Invalid_Input("Was expecting int");
					exit(0);
				}
				DoBattleCommand(model, id, battle_amount);
				break;
			}
			case 'a':
			{
				DoAdvanceCommand(model, display);
				break;
			}
			case 'r':
			{
				DoRunCommand(model, display);
				break;
			}
			case 'q':
			{
				exit(0);
			}
			case 'n':
			{
				if (!(cin >> type))
				{
					throw Invalid_Input("Was expecting char");
					exit(0);
				}
				if (!(cin >> id))
				{
					throw Invalid_Input("Was expecting int");
					exit(0);
				}
				if (!(cin >> x))
				{
					throw Invalid_Input("Was expecting int");
					exit(0);
				}
				if (!(cin >> y))
				{
					throw Invalid_Input("Was expecting int");
					exit(0);
				}
				model.NewCommand(type, id, x, y);
				break;
			}
			default:
				throw Invalid_Input("Please select valid command");
			}
		}
		catch (Invalid_Input& except)
		{
			cout << "Invalid input: " << except.msg_ptr << endl;
		}
	}

}
