#include <iostream>
#include <string>
#include <vector>
#include "Bancomat.h"

Bancomat::Bancomat(double sold){
    this->sold = sold;
}

Bancomat::Bancomat(){
    this->sold = 0;
}

Bancomat::~Bancomat(){
    this->sold = 0;
}

Bancomat::Bancomat(const Bancomat& c){
    this->sold = c.sold;
    this->tranzactii = c.tranzactii;
}

double Bancomat::getSold(){
    return this->sold;
}

std::vector<Tranzactie> Bancomat::getTranzactii(){
    return this->tranzactii;
}

void Bancomat::setSold(double sold){
    this->sold = sold;
}

void Bancomat::adaugaTranzactie(Tranzactie t){
    if (t.getTip() == intrare){
        this->sold += std::stod(t.getSuma());
        tranzactii.push_back(t);
    }
    else{
        if (std::stod(t.getSuma()) > this->sold){
            std::cout << "Nu aveti destui bani in cont pentru a efectua aceasta tranzactie" << std::endl;
            return;
        }
        else
        {
            this->sold -= std::stod(t.getSuma());
            tranzactii.push_back(t);
        }
    }
}

void Bancomat::afiseazaBancomat(){
    std::cout<< "Sold: " << this->sold << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "Tranzactii: " << std::endl;
    for (int i = 0; i < tranzactii.size(); i++){
        if (tranzactii[i].getTip() == intrare){
            std::cout << "Data: " << tranzactii[i].getData() << std::endl;
            std::cout << "Tip: " << "+" << std::endl;
            std::cout << "Suma: " << tranzactii[i].getSuma() << std::endl;
            std::cout << "Descriere: " << tranzactii[i].getDescriere() << std::endl;
            std::cout << "-------------------------------------" << std::endl;
        }
        else{
            std::cout << "Data: " << tranzactii[i].getData() << std::endl;
            std::cout << "Tip: " << "iesire" << std::endl;
            std::cout << "Suma: " << tranzactii[i].getSuma() << std::endl;
            std::cout << "Descriere: " << tranzactii[i].getDescriere() << std::endl;
            std::cout << "-------------------------------------" << std::endl;
        }
    }
}