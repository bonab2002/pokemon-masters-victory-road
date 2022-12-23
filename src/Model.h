
#include "View.h"
#include "WildPokemon.h"
#include "Input_Handling.h"
#include <list>

class Model 
{
private:
    int time;
    list <GameObject*> object_ptrs;
    list <GameObject*> active_ptrs;
    list <Trainer*> trainer_ptrs;
    list <PokemonCenter*> center_ptrs;
    list <PokemonGym*> gym_ptrs;
    list <WildPokemon*> wildpokemon_ptrs;
public:
    Model();
    ~Model();
    Trainer* GetTrainerPtr(int id);
    PokemonCenter* GetPokemonCenterPtr(int id);
    PokemonGym* GetPokemonGymPtr(int id);
    void NewCommand(char, int, double, double);
    bool Update();
    void Display(View& view);
    void ShowStatus();
    int GetTime();
};
