#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#ifndef TRANZACTIE_H
#define TRANZACTIE_H

class Date {
    int zi;
    int luna;
    int an;
public:
    Date (int zi, int luna, int an) 
    {
        this->zi = zi;
        this->luna = luna;
        this->an = an;
    }
    Date() 
    {
        this->zi = 0;
        this->luna = 0;
        this->an = 0;
    }
    Date(const Date& d) 
    {
        this->zi = d.zi;
        this->luna = d.luna;
        this->an = d.an;
    }

    int getZi() const
    {
        return this->zi;
    }
    int getLuna() const
    {
        return this->luna;
    }
    int getAn() const
    {
        return this->an;
    }
    void setZi(int zi)
    {
        this->zi = zi;
    }
    void setLuna(int luna)
    {
        this->luna = luna;
    }
    void setAn(int an)
    {
        this->an = an;
    }
    friend std::ostream& operator<<(std::ostream& os, const Date& d)
    {
        os << d.zi << "." << d.luna << "." << d.an;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Date& d)
    {
        is >> d.zi >> d.luna >> d.an;
        return is;
    }
    bool operator==(const Date& d)
    {
        return (this->zi == d.zi && this->luna == d.luna && this->an == d.an);
    }
    bool operator!=(const Date& d)
    {
        return (this->zi != d.zi || this->luna != d.luna || this->an != d.an);
    }

    bool operator<(const Date& d)
    {
        if (this->an < d.an)
            return true;
        else if (this->an == d.an && this->luna < d.luna)
            return true;
        else if (this->an == d.an && this->luna == d.luna && this->zi < d.zi)
            return true;
        else
            return false;
    }
    bool operator>(const Date& d)
    {
        if (this->an > d.an)
            return true;
        else if (this->an == d.an && this->luna > d.luna)
            return true;
        else if (this->an == d.an && this->luna == d.luna && this->zi > d.zi)
            return true;
        else
            return false;
    }
};
enum TipTranzactie{
    intrare,
    iesire
};
class Tranzactie{
    private:
        Date data;
        TipTranzactie tip;
        std::string suma;
        std::string descriere;

    public:
    Tranzactie(Date data, TipTranzactie tip, std::string suma, std::string descriere);
    Tranzactie();
    ~Tranzactie();
    Tranzactie(const Tranzactie& t);
    Date getData() const;
    TipTranzactie getTip() const;
    std::string getSuma() const;
    std::string getDescriere() const;
    bool operator==(const Tranzactie& t);
    bool operator!=(const Tranzactie& t);
    bool operator<(const Tranzactie& t);
    bool operator>(const Tranzactie& t);
    bool operator<=(const Tranzactie& t);
    bool operator>=(const Tranzactie& t);
    friend std::ostream& operator<<(std::ostream& os, const Tranzactie& t);
    friend std::istream& operator>>(std::istream& is, Tranzactie& t);
};
#endif