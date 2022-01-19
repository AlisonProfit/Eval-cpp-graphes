#include "graphList.h"
#include "graphMatrix.h"
#include "arrete.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>

GraphList::GraphList(std::unordered_map <std::string, std::vector<Arrete>> graph) : 
    graph(graph) {}

int GraphList::size() const {
    return graph.size();
}

void GraphList::affiche() {
    for(const auto& s: graph){
        std::cout << "Sommet" << " " << s.first << " " << "lié aux arrêtes : ";
        for(const auto& v: s.second){
            std::cout << v.getNom() << " "; 
        }
        std::cout << std::endl;
    }
}

std::vector<Arrete> GraphList::at(const std::string& s) const {
    // renvoie la liste des arretes
    return graph.at(s);
}


std::vector<std::string> GraphList::names(){
    std::vector<std::string> res;
    for(const auto& k : graph){
        res.push_back(k.first);
    }
    return res;
}