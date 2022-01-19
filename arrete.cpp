#include "arrete.h"
#include <string>
#include <iostream>

Arrete::Arrete (std::string d,std::string a, double val):
    d(d),
    a(a),
    val(val) {}



void Arrete::print() const {
    std::cout << a << " " << d << " " << val << std::endl;
}

double Arrete::getNom() const {
    return val;
}

std::string Arrete::depart() const {
    return d;
}

std::string Arrete::arrivee() const {
    return a;
}

bool Arrete::common(Arrete& arr){
    if((arr.depart() == d) && (arr.arrivee() == a) && (arr.getNom() == val)){
        return true;
    }
    else{
        return false;
    }
}