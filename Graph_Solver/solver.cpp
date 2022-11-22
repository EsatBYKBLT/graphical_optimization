#include "solver.h"
#include <QDebug>

void Solver::add_kisit_denklemi(Equation kisit_denklemi)
{
    kisit_denklemleri.push_back(kisit_denklemi);
}
void Solver::set_amac_fonksiyonu(Equation amac_fonksiyonu)
{
    this->amac_fonksiyonu=amac_fonksiyonu;
}

void Solver::solve(){
    Equation e1,e2;
    e1.x=0;e1.y=1'000'000'000;e1.bke=BKE::buyuk;e1.b=0;
    e2.x=1'000'000'000;e2.y=0;e2.bke=BKE::kucuk;e2.b=0;
    kisit_denklemleri.push_back(e1);
    kisit_denklemleri.push_back(e2);


    for(Equation& i:kisit_denklemleri)
        for(Equation& j:kisit_denklemleri)
            kesisim_noktalari.push_back(kesisim_noktalarini_bul(i,j));

    kesisim_noktalarini_filtrele();

    p_max = find_p_max();
    p_min = find_p_min();
}

string Solver::get_result(){
    string s1 = to_string(p_max.x)+"x ";
    string s2 = to_string(p_max.y)+"y ";
    string s3 = to_string(p_min.x)+"x ";
    string s4 = to_string(p_min.y)+"y ";
    string temp = "max: "+s1+s2+"  min: "+s3+s4;
    return temp;
}

string Solver::get_kisitdenklemleri()
{
    string s1{}, s2{}, s3{}, s4{};
    string temp {};
    for (auto& i  : kisit_denklemleri) {
        s1 = to_string(i.x)+" x + ";
        s2 = to_string(i.y)+" y ";
        if(i.bke==BKE::kucuk) s3 = "<=";
        else s3 = ">=";
        s4 = to_string(i.b);
        temp += s1+s2+s3+s4+"\n";
    }
    return temp;
}

Point Solver::kesisim_noktalarini_bul(Equation a, Equation b)
{
    Point p;
    p.x = ((a.y*-b.b)-(b.y*-a.b)) /
          ((a.x*b.y)-(b.x*a.y));

    p.y = ((-a.b*b.x)-(-b.b*a.x)) /
          ((a.x*b.y)-(b.x*a.y));

    //qDebug()<<p.x<<"  "<<p.y<<"\n";
    return p;
}

void Solver::kesisim_noktalarini_filtrele()
{
    vector<Point> vec;
    vec.insert(vec.end(), kesisim_noktalari.begin(), kesisim_noktalari.end());

    // noktanin sinirlar icinde olup olmadigini kontrol ediyor
    for(int i = 0; i<vec.size();){
        if(!nokta_gecerli_mi(vec[i]))
            i++;
        else{
            vec.erase(vec.begin()+i);
        }
    }

    qDebug()<<"AYOHA\n";
    kesisim_noktalari=vec;
    for(auto& i : kesisim_noktalari)
        qDebug()<<i.x<<"  "<<i.y<<"\n";
}
bool Solver::nokta_gecerli_mi(Point p)
{
    if(p.x<0 || p.y<0)return true;

    for(auto& i : kisit_denklemleri){
        double d = p.x * i.x + p.y*i.y;

        if(BKE::buyuk == i.bke && i.b<d)//eger buyuk esitse ama kucuk geliyorsa
            return false;
        else if(BKE::kucuk == i.bke && i.b>d)//eger kucuk esitse ama buyuk geliyorsa
            return false;
    }
// tum denklemleri sagliyorsa
    return true;
}

Point Solver::find_p_max()
{
    Point ptemp;
    double dtemp=-999'999'999;

    for (auto& i: kesisim_noktalari) {
        double z = amac_fonksiyonu.x*i.x + amac_fonksiyonu.y * i.y;
        if(z>dtemp){
            dtemp=z;
            ptemp=i;

        }
    }

    return ptemp;
}

Point Solver::find_p_min()
{
    Point ptemp;
    double dtemp=+999'999'999;

    for (auto& i: kesisim_noktalari) {
        double z = amac_fonksiyonu.x*i.x + amac_fonksiyonu.y * i.y;
        if(z<dtemp){
            dtemp=z;
            ptemp=i;
        }
    }

    return ptemp;

}

