#include "graphMatrix.h"
#include "graphList.h"
#include "arrete.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

GraphMatrix::GraphMatrix(std::vector<double> g, std::vector<std::string> sommets):
    graph(g),
    sommets(sommets) {}


void GraphMatrix::affiche () {

    std::cout << " "; // raisons esthétiques

    //on affiche les sommets
    for(double i = 0; i < sommets.size(); i ++){
        std::cout << sommets[i] ;
    }
    std::cout << std::endl;

    // on affiche les arrêtes
    for(double i = 0; i < sommets.size(); i ++){
        std::cout << sommets[i];
        for(double k = 0; k < sommets.size(); k ++){
            std::cout << graph.at(i*sommets.size() + k);
        }
        std::cout << std::endl;
    }
}


double GraphMatrix::size(){
    return sommets.size();
}


double GraphMatrix::at(int i, int j){
    return graph[i*sommets.size()+j];
}


std::vector<double> GraphMatrix::getLine(std::string& s) {
    //renvoie les arretes sortantes
    std::vector<double> res;
    for(int i=0; i<sommets.size(); i++){
        if(sommets[i] == s){
            for(int k=0; k<sommets.size(); k++){
                res.push_back(graph[i*sommets.size()+k]);
            }
        }
    }

    return res;
}

std::vector<std::string> GraphMatrix::getSommets(){
    return sommets;
}
