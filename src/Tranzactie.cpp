#include <iostream>
#include <string>
#include <vector>
#include "Tranzactie.h"


Tranzactie::Tranzactie(Date data, TipTranzactie tip, std::string suma, std::string descriere){
    this->data = Date(data);
    this->tip = tip;
    this->suma = suma;
    this->descriere = descriere;
}

Tranzactie::Tranzactie(){
    this->data = Date();
    this->tip = intrare;
    this->suma = "";
    this->descriere = "";
}

Tranzactie::~Tranzactie(){
}


Tranzactie::Tranzactie(const Tranzactie& t){
    this->data = t.data;
    this->tip = t.tip;
    this->suma = t.suma;
    this->descriere = t.descriere;
}

Date Tranzactie::getData() const{
    return this->data;
}
TipTranzactie Tranzactie::getTip() const{
    return this->tip;
}
std::string Tranzactie::getSuma() const{
    return this->suma;
}
std::string Tranzactie::getDescriere() const{
    return this->descriere;
}
bool Tranzactie::operator==(const Tranzactie& t){
    return (this->data == t.data);
}
bool Tranzactie::operator!=(const Tranzactie& t){
    return (this->data != t.data);
}
bool Tranzactie::operator<(const Tranzactie& t){
    return (this->data < t.data);
}
bool Tranzactie::operator>(const Tranzactie& t){
    return (this->data > t.data);
}
std::ostream& operator<<(std::ostream& os, const Tranzactie& t)
{   if (t.tip == intrare)
        os << "Data: " << t.data << " Tip: " << "+" << " Suma: " << t.suma << " Descriere: " << t.descriere;
    else
        os << "Data: " << t.data << " Tip: " << "-" << " Suma: " << t.suma << " Descriere: " << t.descriere;
    return os;
    
}
std::istream& operator>>(std::istream& is, Tranzactie& t)
{
    std::cout << "Data: " << std::endl;
    is >> t.data;
    std::cout << "Tip: " << std::endl;
    std::string tip;
    is >> tip;
    if (tip == "+")
        t.tip = intrare;
    else
        t.tip = iesire;
    std::cout << "Suma: " << std::endl;
    is >> t.suma;
    std::cout << "Descriere: " << std::endl;
    is >> t.descriere;
    return is;
}


