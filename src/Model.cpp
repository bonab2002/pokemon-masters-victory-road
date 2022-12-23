#include "Model.h"

Model::Model()
{
    time = 0;
    PokemonCenter* C1 = new PokemonCenter(1, 1, 100, Point2D(1, 20));
    PokemonCenter* C2 = new PokemonCenter(2, 2, 200, Point2D(10, 20));
    Trainer* T1 = new Trainer("Ash", 1, 'T', 2, Point2D(5, 1));
    Trainer* T2 = new Trainer("Misty", 2, 'T', 1, Point2D(10, 1));
    PokemonGym* G1 = new PokemonGym(10, 1, 2, 3, 1, Point2D(0, 0));
    PokemonGym* G2 = new PokemonGym(20, 5, 7.5, 4, 2, Point2D(5, 5));
   WildPokemon* W1 = new WildPokemon("WildPokemon1", 2, 10, 5, 1, Point2D(10, 12));
    WildPokemon* W2 = new WildPokemon("WildPokemon2", 3, 9, 7, 2, Point2D(15, 5));
    object_ptrs.push_back(C1);
    object_ptrs.push_back(C2);
    object_ptrs.push_back(T1);
    object_ptrs.push_back(T2);
    object_ptrs.push_back(G1);
    object_ptrs.push_back(G2);
    object_ptrs.push_back(W1);
    object_ptrs.push_back(W2);
    active_ptrs.assign(object_ptrs.begin(), object_ptrs.end());
    center_ptrs.push_back(C1);
    center_ptrs.push_back(C2);
    trainer_ptrs.push_back(T1);
    trainer_ptrs.push_back(T2);
    gym_ptrs.push_back(G1);
    gym_ptrs.push_back(G2);
    wildpokemon_ptrs.push_back(W1);
    wildpokemon_ptrs.push_back(W2);
    cout << "Model default constructed" << endl;
}

Model::~Model()
{
    for (list<GameObject*>::iterator iter1 = object_ptrs.begin(); iter1 != object_ptrs.end(); iter1++)
    {
        delete *iter1;
    }
    cout << "Model destructed" << endl;
}
int Model::GetTime()
{
    return time;
}
Trainer* Model::GetTrainerPtr(int id)
{
    for (list<Trainer*>::iterator iter1 = trainer_ptrs.begin(); iter1 != trainer_ptrs.end(); iter1++)
    {
        if ((*iter1)->GetId() == id)
        {
            return *iter1;
        }
    }
    return nullptr;
}

PokemonCenter* Model ::GetPokemonCenterPtr(int id)
{
    for (list<PokemonCenter*>::iterator iter1 = center_ptrs.begin(); iter1 != center_ptrs.end(); iter1++)
    {
        if ((*iter1)->GetId() == id)
        {
            return *iter1;
        }
    }
    return nullptr;
}

PokemonGym* Model ::GetPokemonGymPtr(int id)
{
    for (list<PokemonGym*>::iterator iter1 = gym_ptrs.begin(); iter1 != gym_ptrs.end(); iter1++)
    {
        if ((*iter1)->GetId() == id)
        {
            return *iter1;
        }
    }
    return nullptr;
}

bool Model::Update()
{
    time++;
    int output = 0;
    int temp1 = 0;
    int temp2 = 0;
    list<GameObject*>::iterator iter1;
    for (iter1 = active_ptrs.begin(); iter1 != active_ptrs.end(); iter1++)
    {
        if ((*iter1)->Update())
        {
            output++;
        }
    }
    for (list<GameObject*>::iterator iter = active_ptrs.begin(); iter != active_ptrs.end(); iter++)
    {
        if (!(*iter)->ShouldBeVisible())
        {
            active_ptrs.erase(iter);
            break;
        }
    }
    list<PokemonGym*>::iterator iter2;
    for (iter2 = gym_ptrs.begin(); iter2 != gym_ptrs.end(); iter2++)
    {
        if ((*iter2)->GetNumBattlesRemaining() == 0)
        {
            temp1++;
        }
    }
    list<Trainer*>::iterator iter3;
    for (iter3 = trainer_ptrs.begin(); iter3 != trainer_ptrs.end(); iter3++)
    {
        if ((*iter3)->HasFainted())
        {
            temp2++;
        }
    }
    if (temp1 == gym_ptrs.size())
    {
        cout << "GAME OVER: You win! All battles done!" << endl;
        exit(0);
    }
    if (temp2 == trainer_ptrs.size())
    {
        cout << "GAME OVER: You lose! All of your Trainers have lost!" << endl;
        exit(0);
    }
    for (iter3 = trainer_ptrs.begin(); iter3 != trainer_ptrs.end(); iter3++)
    {
        for (list<WildPokemon*>::iterator iter4 = wildpokemon_ptrs.begin(); iter4 != wildpokemon_ptrs.end(); iter4++)
        {
            if (GetDistanceBetween((*iter3)->GetLocation(), (*iter4)->GetLocation()) == 0)//why less than 10
            {
                (*iter4)->follow(*iter3);
            }
        }
    }
    if (output > 0)
    {
        return true;
    }
    return false;
}

void Model::Display(View& view)
{
    cout << "Current time: " <<time<< endl;
    view.Clear();
    for (list<GameObject*>::iterator iter1 = active_ptrs.begin(); iter1 != active_ptrs.end(); iter1++)
    {
        if (*iter1 != NULL)
        {
            view.Plot(*iter1);
            (*iter1)->ShowStatus();
        }
    }
    view.Draw();
}
void Model::ShowStatus()
{
    cout << "Time: " << time << endl;
    for (list<GameObject*>::iterator iter1 = active_ptrs.begin(); iter1 != active_ptrs.end(); iter1++)
    {
        (*iter1)->ShowStatus();
    }
}
void Model::NewCommand(char type, int in_id, double x, double y)
{
    switch (type)
    {
    case 'c':
    {
        for (list<PokemonCenter*>::iterator iter1 = center_ptrs.begin(); iter1 != center_ptrs.end(); iter1++)
        {
            if (in_id == (*iter1)->GetId())
            {
                throw Invalid_Input("Please enter unique PokemonCenter ID");
            }
            if (x == (*iter1)->GetLocation().x && y == (*iter1)->GetLocation().y)
            {
                throw Invalid_Input("There is already a PokemonCenter here");
            }
            if (x > 20 || y > 20 || x < 0 || y < 0)
            {
                throw Invalid_Input("Please enter a valid point on the grid");
            }
        }
        PokemonCenter* C = new PokemonCenter(in_id, 100, 2, Point2D(x, y));
        object_ptrs.push_back(C);
        active_ptrs.push_back(C);
        center_ptrs.push_back(C);
        cout << "New PokemonCenter created" << endl;
        break;
    }
    case 'g':
    {
        for (list<PokemonGym*>::iterator iter1 = gym_ptrs.begin(); iter1 != gym_ptrs.end(); iter1++)
        {
            if (in_id == (*iter1)->GetId())
            {
                throw Invalid_Input("Please enter unique PokemonGym ID");
            }
            if (x == (*iter1)->GetLocation().x && y == (*iter1)->GetLocation().y)
            {
                throw Invalid_Input("There is already a PokemonGym here");
            }
            if (x > 20 || y > 20 || x < 0 || y < 0)
            {
                throw Invalid_Input("Please enter a valid point on the grid");
            }
        }
        PokemonGym* G = new PokemonGym(25, 2, 10, 5, in_id, Point2D(x, y));
        object_ptrs.push_back(G);
        active_ptrs.push_back(G);
        gym_ptrs.push_back(G);
        cout << "New PokemonGym created" << endl;
        break;
    }
    case 't':
    {
        for (list<Trainer*>::iterator iter1 = trainer_ptrs.begin(); iter1 != trainer_ptrs.end(); iter1++)
        {
            if (in_id == (*iter1)->GetId())
            {
                throw Invalid_Input("Please enter unique Trainer ID");
            }
            if (x > 20 || y > 20 || x < 0 || y < 0)
            {
                throw Invalid_Input("Please enter a valid point on the grid");
            }
        }
        Trainer* T = new Trainer("NewTrainer", in_id, 'S', 1, Point2D(x, y));
        object_ptrs.push_back(T);
        active_ptrs.push_back(T);
        trainer_ptrs.push_back(T);
        cout << "New Trainer created" << endl;
        break;
    }
    case 'w':
    {
        for (list<WildPokemon*>::iterator iter1 = wildpokemon_ptrs.begin(); iter1 != wildpokemon_ptrs.end(); iter1++)
        {
            if (in_id == (*iter1)->GetId())
            {
                throw Invalid_Input("Please enter unique WildPokemon ID");
            }
            if (x > 20 || y > 20 || x < 0 || y < 0)
            {
                throw Invalid_Input("Please enter a valid point on the grid");
            }
        }
        WildPokemon* W = new WildPokemon("NewWildPokemon", in_id, 1, true, 1, Point2D(x, y));
        object_ptrs.push_back(W);
        active_ptrs.push_back(W);
        wildpokemon_ptrs.push_back(W);
        cout << "New WildPokemon created" << endl;
        break;
    }
    default:
        throw Invalid_Input("Please enter c, g, t, or w");
    }
}
