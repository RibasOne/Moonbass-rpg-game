#include <string>

using namespace std;

class Jogador{
    public:
        string nome;
        int classe, vida, ataque, defesa, agilidade;
};

struct Entidades{
    string nome;
    int vida, ataque, defesa, inteligencia;
};

struct Equipamentos{
    int moedas = 500;
    int cura = 5;
    bool espada = false;
    bool flauta = false;
    bool mapa = false;
    bool corda = false;
};
