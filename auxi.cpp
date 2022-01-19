#include "graphList.h"
#include "graphMatrix.h"
#include "arrete.h"
#include "auxi.h"
#include <string>
#include <cmath>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <cstdio>


std::unordered_map<std::string,double> getIndex(std::vector<std::string>& sommets){
    std::unordered_map<std::string, double> res;
    for(double k=0 ; k < sommets.size(); k++){
        res.insert({sommets[k],k});
    }
    return res;
}
std::unordered_map<double, std::string> getNames(std::vector<std::string>& sommets){
    std::unordered_map<double, std::string> res;
    for(double k=0 ; k < sommets.size(); k++){
        res.insert({k,sommets[k]});
    }
    return res;
}



GraphMatrix list2matrix(GraphList& graph) {
    std::vector<double> mat;
    std::vector<std::string> sommets;
    int len = graph.size();

    // On initialise la matrice
    for( int  k=0; k<len; k++){
        for( int  i=0; i<len; i++){
            mat.push_back(0.);
        }
    }

    // On remplis la liste des sommets car on va en avoir besoin 
    for( double  k=0; k<len; k++){
        sommets.push_back(graph.names()[k]);
    } 

    for( double  k=0; k<len; k++){
        std::vector<Arrete> aux = graph.at(graph.names()[k]);
        for(auto a: aux){
            mat.at(getIndex(sommets)[a.depart()]*len+getIndex(sommets)[a.arrivee()]) = a.getNom();
        }
    }
    
    GraphMatrix res(mat,sommets);
    return res;
}


GraphList matrix2list(GraphMatrix& graph){
    std::unordered_map <std::string, std::vector<Arrete>> list;
    for(auto s: graph.getSommets()){
        list.insert({s,{}}); //sommet non relié pour l'instant
        for(auto k: graph.getSommets()){
            if(graph.at(getIndex(graph.getSommets())[s], getIndex(graph.getSommets())[k])){
                Arrete aux (s,k,graph.at(getIndex(graph.getSommets())[s], getIndex(graph.getSommets())[k]));
                list.at(s).push_back(aux);
            }
            if(graph.at(getIndex(graph.getSommets())[k], getIndex(graph.getSommets())[s])){
                Arrete aux (k,s,graph.at(getIndex(graph.getSommets())[k], getIndex(graph.getSommets())[s]));
                list.at(s).push_back(aux);
            }
        }
    }
    return list;
}


GraphMatrix read_mat(std::string filename) {
  // chaque ligne du fichier contient le nom d'un sommet et ses arrêtes sortantes
    std::ifstream input_file(filename);

    if (!input_file.is_open()) {
        std::cerr << "cannot open file '" << filename << "'" << std::endl;
    }
    // erreur si le fichier n'est pas postfixé par .graph
    if(!(filename.find(".graph") != std::string::npos)){
        std::cerr << "files must be postfixed .graph" << std::endl;
    }


    std::vector<double> g;
    std::vector<std::string> sommets;
    std::vector<Arrete> tempo;
    std::string line;


    while (getline(input_file, line)) {
        //std::cout << "analyse de la ligne " << line << std::endl;

        std::istringstream iss(line);

        std::string dep;
        iss >> dep;
        // si on n'a jamais rencontré le sommet, onl'ajoute à la liste des sommets
        if(find(sommets.begin(),sommets.end(), dep)==sommets.end()){
            sommets.push_back(dep);
        }


        std::string arrive;
        iss >> arrive;
        // si on n'a jamais rencontré le sommet, onl'ajoute à la liste des sommets
        if(find(sommets.begin(),sommets.end(),arrive)==sommets.end()){
            sommets.push_back(arrive);
        }


        double x;
        iss >> x;
        tempo.push_back(Arrete (dep,arrive,x));

    }

    // Initialisation de la map
    for(int i=0; i<sommets.size(); i++){
        for(int j=0; j<sommets.size(); j++){
            g.push_back(0.);
        }
    }

    for(auto& k: tempo){
        g.at(getIndex(sommets).at(k.depart())*sommets.size()+getIndex(sommets).at(k.arrivee())) = k.getNom();
    }

    GraphMatrix res(g,sommets);
    return res;
}


GraphList read_list(std::string filename) {
    // chaque ligne du fichier contient le nom d'un sommet et ses arrêtes sortantes
    std::ifstream input_file(filename);

    if (!input_file.is_open()) {
        std::cerr << "cannot open file '" << filename << "'" << std::endl;
    }
    // erreur si le fichier n'est pas postfixé par .graph
    if(!(filename.find(".graph") != std::string::npos)){
        std::cerr << "files must be postfixed .graph" << std::endl;
    }


    std::unordered_map <std::string, std::vector<Arrete>> g;
    std::vector<std::string> sommets;
    std::string line;


    while (getline(input_file, line)) {
        //std::cout << "analyse de la ligne " << line << std::endl;

        std::istringstream iss(line);

        // on récupère toutes les variables sur une ligne
        std::string dep;
        iss >> dep;
        std::string arrive;
        iss >> arrive;
        double x;
        iss >> x;

        Arrete a0(dep,arrive,x); // arrete représentée par la ligne

        // si on n'a jamais rencontré le sommet d'arrivée, on l'ajoute à la map avec son arrête
        if(find(sommets.begin(),sommets.end(),arrive)==sommets.end()){
            g.insert({arrive,{a0}});
            sommets.push_back(arrive);
        }
        // si on a déja vu le sommet, on ne fait qu'ajouter l'arrête
        else{
            g.at(arrive).push_back(a0);
        }


        // si on n'a jamais rencontré le sommet de départ, on l'ajoute à la liste des sommets
        if(find(sommets.begin(),sommets.end(), dep)==sommets.end()){
            g.insert({dep,{a0}});
            sommets.push_back(dep);
        }
        else{
            g.at(dep).push_back(a0);
        }

    }

    GraphList res(g);
    return res;
}


void matRec(GraphMatrix& g, std::string& s, std::vector<std::string>& visites){
    visites.push_back(s);
    std::cout << "Sommet " << s << std::endl;

    int c = 0;
    for(double k: g.getLine(s)){ // on regarde chaque arrete SORTANTE
        if(k != 0.){
            std::cout << "Arrête " << k << std::endl;
            std::string nouv = g.getSommets().at(c);

            // si le sommet nouv n'est pas dans visites, on lance sa visite via l'arrête k que l'on explore
            if(find(visites.begin(), visites.end(), nouv) == visites.end()){                 
                matRec(g, nouv, visites);
            }
        }
        c ++;
    }
}


void listRec(GraphList& graph, const std::string& s, std::vector<std::string>& visites){
    visites.push_back(s);
    std::cout << "Sommet inital " << s << std::endl;
    for(auto k: graph.at(s)){ // on regarde chaque arrete voisine
        if(k.depart() == s){  
            std::cout << "Arrête " << k.getNom() << " sommet " << k.arrivee() << std::endl;
            if(find(visites.begin(), visites.end(), k.arrivee()) == visites.end()){ //le sommet n'a pas encore été visité, sinon on regarde les autres arrêtes
                listRec(graph, k.arrivee(), visites);
            }
        }
        
    }

}




void listIterative(GraphList& graph, std::string& s){
    std::stack<Arrete> stk;
    std::vector<double> visites;
    std::cout << "Départ du sommet " << s << std::endl;

    // initialisation de la pile avec les arretes sortantes du premier sommet
    for(auto & k : graph.at(s)){
        if(k.depart() == s){
            stk.push(k);
        }        
    }
    
    while(!(stk.empty())){
        Arrete current = stk.top();       
        stk.pop();        
        
        if(find(visites.begin(),visites.end(),current.getNom()) == visites.end()){
            std::cout << "le sommet " << current.arrivee() << " " << "a été visité via l'arrête " << current.getNom() << std::endl;
            visites.push_back(current.getNom());
            
            for(auto & k : graph.at(current.arrivee())){
                if(k.depart() == current.arrivee()){ //S'il s'agit bien d'une arrête sortante
                    stk.push(k);
                }
                
            }        
        }
        
    }
}



void matIterative(GraphMatrix& graph, std::string& s){
    std::cout << "Départ du sommet " << s << std::endl;
    std::vector<double> visites;
    std::stack<double> stk;
    std::stack<double> ind;

    // initialisation de la pile avec les voisins du premier sommet
    double i = 0;
    for(auto k : graph.getLine(s)){
        if(k!=0.){
            stk.push(k);
            ind.push(i);  
        }

        i++;
    }
    
    while(!(stk.empty())){
        double current = stk.top();
        double cursor = ind.top(); 
        stk.pop();
        ind.pop();

        if(find(visites.begin(),visites.end(),current)==visites.end()){ //Si on n'a pas encore visité cette arrête
            std::cout << "le sommet " << getNames(graph.getSommets()).at(cursor) << " via l'arrête " << current << std::endl;
            visites.push_back(current);

            // On empile les nouvelles arrêtes accessibles à partir de ce sommet
            double j = 0;
            for(auto k : graph.getLine(graph.getSommets().at(cursor))){
                if(k!=0.){
                stk.push(k);
                ind.push(j);               
                } 
                j++;      
            }
        }
    }
}


void listLargeur(GraphList& graph, std::string& s, int level){
    std::queue <Arrete> q;
    std::vector <double> visites;
    std::queue<int> lev;
    std::cout << "Départ du sommet " << s << std::endl;

    // initialisation de la pile avec les arretes sortantes du premier sommet
    for(auto & k : graph.at(s)){
        if(k.depart() == s){
            q.push(k);
            lev.push(0);
        }        
    }
    
    // On parcourt tout le graph par défaut
    if(level == 0){
        while(!(q.empty())){
            Arrete current = q.front();       
            q.pop();        
        
            if(find(visites.begin(),visites.end(),current.getNom()) == visites.end()){
                std::cout << "le sommet " << current.arrivee() << " via l'arrête " << current.getNom() << std::endl;
                visites.push_back(current.getNom());
            
                for(auto & k : graph.at(current.arrivee())){
                    if(k.depart() == current.arrivee()){ //S'il s'agit bien d'une arrête sortante
                        q.push(k);
                    }
                
                }        
            }
        
        }
    }

    else{ // On a spécifié un niveau auquel on souhaite s'arrêter
        int l = 0;
        while(l<level){   
            Arrete current = q.front();       
            q.pop();        
            lev.pop();
        
            if(find(visites.begin(),visites.end(),current.getNom()) == visites.end()){
                std::cout << "le sommet " << current.arrivee() << "via l'arrête " << current.getNom() << " fils de " << current.arrivee() << std::endl;
                visites.push_back(current.getNom());
            
                for(auto & k : graph.at(current.arrivee())){
                    if(k.depart() == current.arrivee()){ //S'il s'agit bien d'une arrête sortante
                        q.push(k);
                        lev.push(l+1);
                    }
                }
                l = lev.front();        
            }
        }
    }
}






void matLargeur(GraphMatrix& graph, std::string& s, int level){
    std::cout << "Départ du sommet " << s << std::endl;
    std::queue <double> q;
    std::vector <double> visites;
    std::queue <int> lev;
    std::queue <double> ind;

    // initialisation de la pile avec les voisins du premier sommet
    double i = 0;
    for(auto k : graph.getLine(s)){
        if(k!=0.){
            q.push(k);
            ind.push(i);
            lev.push(0);  
        }

        i++;
    }

    // On parcourt tout le graph par défaut
    if(level == 0){
        while(!(q.empty())){
            double current = q.front();
            double cursor = ind.front(); 
            q.pop();
            ind.pop();

            if(find(visites.begin(),visites.end(),current)==visites.end()){ //Si on n'a pas encore visité cette arrête
                std::cout << "le sommet " << getNames(graph.getSommets()).at(cursor) << " via l'arrête " << current << std::endl;
                visites.push_back(current);

                // On empile les nouvelles arrêtes accessibles à partir de ce sommet
                double j = 0;
                for(auto k : graph.getLine(graph.getSommets().at(cursor))){
                    if(k!=0.){
                    q.push(k);
                    ind.push(j);               
                    }    
                    j++;      
                }
            }
        }
    }

    else{ // On a spécifié un niveau auquel on souhaite s'arrêter
        int l = 0;
        while(l<level){   
            double current = q.front();
            double cursor = ind.front(); 
            q.pop();
            ind.pop();
            lev.pop();

            if(find(visites.begin(),visites.end(),current)==visites.end()){ //Si on n'a pas encore visité cette arrête
                std::cout << "le sommet " << getNames(graph.getSommets()).at(cursor) << " via l'arrête " << current << std::endl;
                visites.push_back(current);

                // On empile les nouvelles arrêtes accessibles à partir de ce sommet
                double j = 0;
                for(auto k : graph.getLine(graph.getSommets().at(cursor))){
                    if(k!=0.){
                        q.push(k);
                        ind.push(j);  
                        lev.push(l+1);             
                    } 
                    j++;      
                }
    
                l = lev.front();        
            }
        }
    }
}


GraphMatrix FloydWarshall(GraphMatrix& graph){ 
    double n = graph.size();
    std::vector<double> g;

    // on initialise la matrice en remplaçant les 0 par inf pour que le min fonctionne
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            double d = graph.at(i,j);
            if(d == 0.){
                g.push_back(INFINITY);
            }
            else{
                g.push_back(d);
            }

        } 
    }      

    // on calcule le chemin le plus court
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){   
            for(int k=0; k<n; k++){
                double a = g.at(i*n+j);
                double b = g.at(i*n+k) + g.at(k*n+j);
                g.at(i*n+j) = std::min(a,b);
            }
        }
    }

    return GraphMatrix(g,graph.getSommets());
}