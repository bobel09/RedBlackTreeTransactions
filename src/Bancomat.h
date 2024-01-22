#include <iostream>
#include <string>
#include <vector>
#include "Tranzactie.h"
#ifndef BANCOMAT_H
#define BANCOMAT_H

class Bancomat{
    private:
        int sold; 
        std::vector<Tranzactie> tranzactii;

    public:

    Bancomat(double sold);
    Bancomat();
    ~Bancomat();
    Bancomat(const Bancomat& c);
    double getSold();
    std::vector<Tranzactie> getTranzactii();
    void setSold(double sold);
    void adaugaTranzactie(Tranzactie t);
    void afiseazaBancomat();

};

#endif