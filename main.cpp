#include "graphList.h"
#include "graphMatrix.h"
#include "arrete.h"
#include "auxi.h"
#include <string>
#include <vector>
#include <iostream>



int main(){
    //GraphList graph = read_list("test.graph");
    GraphMatrix graph = read_mat("test.graph");
    
    //GraphMatrix graph1 = list2matrix(graph);
    //GraphList graph1 = matrix2list(graph);
    //graph1.affiche();
   
    // Pour tester les visites récursives
    std::vector<std::string> visites; //liste qui va accueillir les noms des sommets visités
    std::vector<std::string> n = graph.getSommets();   
    int k = 0;
    while(visites.size() < graph.size()){ //tant que tous les sommets n'ont pas été visités
        std::string s = n[k]; // on pourrait sélectionner les sommets au hasard
        matRec(graph, s, visites);
        k ++;
        }

    //matLargeur(graph,n[0], 2);

    //GraphMatrix g = FloydWarshall(graph);
    //g.affiche();

    return 0;
}