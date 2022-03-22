#include <vector>
#include <math.h>
#include <spdlog/spdlog.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

class GR4J
{

private:
    double _X1; // the production store maximal capacity (mm)
    double _X2; // the catchment water exchange coefficient (mm/day)
    double _X3; // the one-day maximal capacity of the routing reservoir (mm)
    double _X4; // the UH1 unit hydrograph time base (days)

    std::vector<long double> _S;           // the production store (mm)
    double _R_initial;                     // the routing reservoir initial val (mm)
    std::vector<long double> _R;           // the routing reservoir (mm)
    std::vector<long double> _Perculation; // the perculation rate (mm/day)
    std::vector<long double> _F;           // groundwater exchange term
    std::vector<long double> _D;           // Discharge readings
    double _Area;                          // the catchment area (km2)

    std::vector<long double> _Pr;        // Precipitation readings
    std::vector<long double> _SH1;       // S-curve 1
    std::vector<long double> _SH2;       // S-curve 2
    std::vector<long double> _UH1;       // Unit Hydrograph 1 - X4
    std::vector<long double> _UH2;       // Unit Hydrograph 2 - 2*X4
    size_t _UH1_size = 10;                  // Unit Hydrograph 1 - X4 ceil
    size_t _UH2_size = 20;                  // Unit Hydrograph 2 - 2*X4 ceil
    std::vector<long double> _Pnet;      // Net precipitation
    std::vector<long double> _Enet;      // Net evapotranspiration
    std::vector<long double> _wQuantity; // Water quantity

    std::vector<long double> _Es;
    std::vector<long double> _Ps;

    size_t _T = _Pr.size();         // Precipitation data size
    std::vector<long double> _E; // Evapotranspiration readings

    std::vector<long double> _Q9;   // 90% quantile
    std::vector<long double> _Q1;   // 10% quantile
    std::vector<long double> _Q;    // Discharge readings
    std::vector<long double> _Qsim; // Simulated discharge
    std::vector<long double> _Qr;
    std::vector<long double> _Qd;

    std::vector<long double> _Q_mm_vec;

    double _R_squared; // R-squared method output

public:
    GR4J();
    ~GR4J();

    void setup();
    void setArea(double area);
    double getArea();
    void setPr(std::vector<long double> Pr);
    void setET(std::vector<long double> E);
    void setQ(std::vector<long double> Q);
    
    void setX1(double X1);
    double getX1();

    void setX2(double X2);
    double getX2();

    void setX3(double X3);
    double getX3();

    void setX4(double X4);
    double getX4();

    void setRinitial(double R_initial);
    void setUH1_size(int UH1_size);
    void setUH2_size(int UH2_size);
    void setS(double S);
    int getUH1_size();
    int getUH2_size();
    std::vector<long double> getUH1();
    std::vector<long double> getUH2();
    std::vector<long double> getSH1();
    std::vector<long double> getSH2();
    std::vector<long double> getPnet();
    std::vector<long double> getEnet();
    std::vector<long double> getS();
    std::vector<long double> getQ1();
    std::vector<long double> getQ9();
    std::vector<long double> getwQuantity();
    std::vector<long double> getQ();
    void updateSH1(int i, int n);
    void updateSH2(int i, int n);
    void updateWaterQuantity(int i);
    void updateQ9(int i);
    void updateQ1(int i);
    void updateR(int i);
    std::vector<long double> getR();
    void updateF(int i);
    std::vector<long double> getF();
    void updateQr(int i);
    std::vector<long double> getQr();
    void updateQd(int i);
    std::vector<long double> getQd();
    void updateQsim(int i);
    std::vector<long double> getQsim();
    void updatePerculation(int i);
    std::vector<long double> getPerculation();
    double getR_squared();
    void calculate();
    void evaporation_gen();
    void r_squared();
};
