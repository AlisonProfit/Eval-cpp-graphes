#pragma once
#include <string>

class Arrete{

    private:
    std::string d; // sommet de départ
    std::string a; // sommet d'arrivée
    double val; //valeur de l'arrete

    public:
    Arrete(std::string d, std::string a, double val);
    void print() const;
    double getNom() const;
    std::string depart() const;
    std::string arrivee() const;
    bool common(Arrete& arr);
};