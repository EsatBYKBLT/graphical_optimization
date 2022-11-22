#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <QString>

using namespace std;

enum class BKE{
    buyuk, kucuk, esit
};

struct Equation{
    double x{}, y{}, b{};
    BKE bke;
    Equation(){}
    Equation(double x, double y, double b, BKE bke)
        :x{x},y{y},b{b},bke{bke}{}
};

struct Point{
    double x{},y{};
    Point(){}
    Point(double x, double y):x{x},y{y} {}

    bool operator == (const Point &p) const {
        if(x==p.x && y==p.y)return true;
        return false;
    }
};

class Solver
{
public:
    Solver(){}
    void add_kisit_denklemi(Equation kisit_denklemi);
    void set_amac_fonksiyonu(Equation amac_fonksiyonu);
    void solve();
    string get_result();
    string get_kisitdenklemleri();
    vector<Equation> kisit_denklemleri;
private:
    Equation amac_fonksiyonu;

    Point p_max;
    Point p_min;

    vector<Point> kesisim_noktalari;

    Point kesisim_noktalarini_bul(Equation a, Equation b);
    void kesisim_noktalarini_filtrele();
    bool nokta_gecerli_mi(Point p);

    Point find_p_max();
    Point find_p_min();
};

#endif // SOLVER_H
