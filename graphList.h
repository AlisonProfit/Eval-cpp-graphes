#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "graphMatrix.h"
#include "arrete.h"

class GraphMatrix;

class GraphList{

    std::unordered_map <std::string, std::vector<Arrete>> graph; //vecteur avec toutes les arretes, in and out

    public:
    GraphList(std::unordered_map <std::string, std::vector<Arrete>> graph);

    void affiche();

    int size() const;
    std::vector<Arrete> at(const std::string& s) const; //renvoie la liste des arretes reliées au sommet
    std::vector<std::string> names();

};