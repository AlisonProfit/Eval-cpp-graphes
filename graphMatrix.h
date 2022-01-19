#pragma once
#include <vector>
#include "graphList.h"

class GraphList;

class GraphMatrix{

    std::vector<double> graph;
    std::vector<std::string> sommets;

    public:
    
    GraphMatrix(std::vector<double> g, std::vector<std::string> sommets);

    void affiche(); //On lit les arrêtes sortantes sur la LIGNE

    double size();

    std::vector<double> getLine(std::string& s); //pour accéder aux arrêtes SORTANTES à partir du nom des sommets
    std::vector<std::string> getSommets();
    double at(int i, int j);


};

