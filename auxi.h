#pragma once
#include "graphList.h"
#include "graphMatrix.h"
#include <vector>
#include <string>

std::unordered_map<std::string,double> getIndex(std::vector<std::string> sommets); 
std::unordered_map<double, std::string> getNames(std::vector<std::string> sommets);

GraphMatrix list2matrix(GraphList graph);
GraphList matrix2list(GraphMatrix graph);

GraphMatrix read_mat(std::string filename);
GraphList read_list(std::string filename);

void matRec(GraphMatrix& g, std::string& s, std::vector<std::string>& visites);
void listRec(GraphList& graph, const std::string& s, std::vector<std::string>& visites);

void listIterative(GraphList& graph, std::string& s);
void matIterative(GraphMatrix& graph, std::string& s);

void listLargeur(GraphList& graph, std::string& s, int level);
void matLargeur(GraphMatrix& graph, std::string& s, int level);

GraphMatrix FloydWarshall(GraphMatrix& graph);