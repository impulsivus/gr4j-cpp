#include "GR4J.h"

GR4J::GR4J()
{
    _X1 = 0;
    _X2 = 0;
    _X3 = 0;
    _X4 = 0;

    _S.clear();
    _Pr.clear();
    _SH1.clear();
    _SH2.clear();
    _UH1.clear();
    _UH2.clear();
    _Q9.clear();
    _Q1.clear();
    _Q.clear();
}
GR4J::~GR4J()
{
    _X1 = 0;
    _X2 = 0;
    _X3 = 0;
    _X4 = 0;
    _S.clear();
    _Pr.clear();
    _SH1.clear();
    _SH2.clear();
    _UH1.clear();
    _UH2.clear();
    _Q9.clear();
    _Q1.clear();
    _Q.clear();
}

void GR4J::setQ(std::vector<long double> Q)
{
    _Q = Q;
}

void GR4J::setArea(double area)
{
    _Area = area;
}

double GR4J::getArea()
{
    return _Area;
}

std::vector<long double> GR4J::getQ()
{
    return _Q;
}

void GR4J::setPr(std::vector<long double> Pr)
{
    _Pr = Pr;
    _T = _Pr.size();
}
void GR4J::setET(std::vector<long double> E)
{
    _E = E;
}
void GR4J::setX1(double X1)
{
    _X1 = X1;
    _S.clear();
    //_S.push_back(_X1 * 0.7);
    _S.push_back(325);
}
void GR4J::setX2(double X2)
{
    _X2 = X2;
}

void GR4J::setX3(double X3)
{
    _X3 = X3;
}

void GR4J::setX4(double X4)
{
    if (X4 < 0.5)
    {
        printf("X4 must be greater than 0.5. Accepting X4 = 0.5...\n");
        X4 = 0.5;
    }
    _X4 = X4;
    _UH1_size = ceil(_X4);
    _UH2_size = ceil(_X4 * 2);
}

void GR4J::setRinitial(double R_initial)
{
    _R.push_back(R_initial);
}

void GR4J::setUH1_size(int UH1_size)
{
    _UH1_size = UH1_size;
}
void GR4J::setUH2_size(int UH2_size)
{
    _UH2_size = UH2_size;
}
int GR4J::getUH1_size()
{
    return _UH1_size;
}
int GR4J::getUH2_size()
{
    return _UH2_size;
}
std::vector<long double> GR4J::getwQuantity()
{
    return _wQuantity;
}

double GR4J::getX1()
{
    return _X1;
}
double GR4J::getX2()
{
    return _X2;
}
double GR4J::getX3()
{
    return _X3;
}
double GR4J::getX4()
{
    return _X4;
}
std::vector<long double> GR4J::getUH1()
{
    return _UH1;
}
std::vector<long double> GR4J::getUH2()
{
    return _UH2;
}
std::vector<long double> GR4J::getSH1()
{
    return _SH1;
}
std::vector<long double> GR4J::getSH2()
{
    return _SH2;
}
std::vector<long double> GR4J::getPnet()
{
    return _Pnet;
}
std::vector<long double> GR4J::getEnet()
{
    return _Enet;
}
std::vector<long double> GR4J::getS()
{
    return _S;
}
std::vector<long double> GR4J::getQ1()
{
    return _Q1;
}
std::vector<long double> GR4J::getQ9()
{
    return _Q9;
}
void GR4J::setS(double S)
{
    _S.clear();
    _S.push_back(S);
}
std::vector<long double> GR4J::getR()
{
    return _R;
}
std::vector<long double> GR4J::getF()
{
    return _F;
}
std::vector<long double> GR4J::getQr()
{
    return _Qr;
}
std::vector<long double> GR4J::getQd()
{
    return _Qd;
}
std::vector<long double> GR4J::getQsim()
{
    return _Qsim;
}
std::vector<long double> GR4J::getPerculation()
{
    return _Perculation;
}

double GR4J::getR_squared()
{
    return _R_squared;
}

void GR4J::setup()
{
}

void GR4J::calculate()
{
    _SH1.reserve(_UH1_size);
    _SH1.resize(_UH1_size);
    _SH2.reserve(_UH2_size);
    _SH2.resize(_UH2_size);
    for (size_t i = 0; i < MAX(_UH1_size, _UH2_size); i++)
    {
        int n = i + 1;
        if (i < _UH1_size)
        {
            if (n < _X4)
            {
                _SH1[i] = (pow((n / _X4), (5 / 2)));
            }
            else
            {
                _SH1[i] = (1);
            }
        }
        if (i < _UH2_size)
        {
            if (n <= _X4)
            {
                _SH2[i] = (pow((n / _X4), (5 / 2)) / 2);
            }
            else if (n < 2 * _X4)
            {
                _SH2[i] = (1 - (pow((2 - (n / _X4)), (5 / 2)) / 2));
            }
            else
            {
                _SH2[i] = (1);
            }
        }
    }
    _UH1.reserve(_UH1_size);
    _UH1.resize(_UH1_size);
    _UH2.reserve(_UH2_size);
    _UH2.resize(_UH2_size);
    for (size_t i = 0; i < _SH1.size(); i++)
    {
        _UH1[i] = (_SH1[i] - _SH1[i - 1]);
    }
    for (size_t i = 0; i < _SH2.size(); i++)
    {
        _UH2[i] = (_SH2[i] - _SH2[i - 1]);
    }
}

void GR4J::evaporation_gen()
{

    _F.reserve(_T);
    _F.resize(_T);

    _wQuantity.reserve(_T);
    _wQuantity.resize(_T);

    _Qsim.reserve(_T);
    _Qsim.resize(_T);

    _Q_mm_vec.reserve(_T);
    _Q_mm_vec.resize(_T);

    _S.reserve(_T + 1);
    _S.resize(_T + 1);

    _Perculation.reserve(_T);
    _Perculation.resize(_T);

    _Pnet.reserve(_T);
    _Pnet.resize(_T);
    _Enet.reserve(_T);
    _Enet.resize(_T);

    _Es.reserve(_T);
    _Es.resize(_T);
    _Ps.reserve(_T);
    _Ps.resize(_T);

    _Qr.reserve(_T);
    _Qr.resize(_T);

    _Qd.reserve(_T);
    _Qd.resize(_T);

    _Q9.reserve(_T);
    _Q9.resize(_T);

    _Q1.reserve(_T);
    _Q1.resize(_T);

    _R.reserve(_T);
    _R.resize(_T);
    for (size_t i = 0; i < _T; i++)
    {
        if (_Pr[i] >= _E[i])
        {
            _Pnet[i] = (_Pr[i] - _E[i]);
            _Enet[i] = (0);
        }
        else
        {
            _Pnet[i] = (0);
            _Enet[i] = (_E[i] - _Pr[i]);
        }
        if (_Enet[i] == 0)
        {
            _Es[i] = (0);
            _Ps[i] = ((_X1 * (1 - pow((_S[i] / _X1), 2)) * tanh(_Pnet[i] / _X1) / (1 + _S[i] * tanh(_Pnet[i] / _X1) / _X1)));
        }
        else
        {
            _Es[i] = (_S[i] * (2 - _S[i] / _X1) * tanh(_Enet[i] / _X1) / (1 + (1 - _S[i] / _X1) * tanh(_Enet[i] / _X1)));
            _Ps[i] = (0);
        }
        updatePerculation(i);
        updateWaterQuantity(i);
        updateQ1(i);
        updateQ9(i);
        updateR(i);
        updateQd(i);
        updateQsim(i);
    }

    std::vector<long double>().swap(_wQuantity);
    std::vector<long double>().swap(_F);
    std::vector<long double>().swap(_S);
    std::vector<long double>().swap(_Qr);
    std::vector<long double>().swap(_Qd);
    std::vector<long double>().swap(_Pnet);
    std::vector<long double>().swap(_Enet);
    std::vector<long double>().swap(_Es);
    std::vector<long double>().swap(_Ps);
    std::vector<long double>().swap(_Q1);
    std::vector<long double>().swap(_Q9);
    std::vector<long double>().swap(_R);
}

void GR4J::updatePerculation(int i)
{
    double _S_tmp = _S[i] - _Es[i] + _Ps[i];
    double _Per_tmp = (_S_tmp * (1.0f - pow(1 + pow((4 * _S_tmp / 9 / _X1), 4), (1 / 4))));
    _Perculation[i] = (_Per_tmp);
    _S[i + 1] = (_S_tmp - _Per_tmp);
}

void GR4J::updateWaterQuantity(int i)
{
    _wQuantity[i] = (MAX(0, _Perculation[i] + _Pnet[i] - _Ps[i] - _Es[i]));
}

void GR4J::updateQ1(int i)
{
    long double sum = 0;
    for (size_t j = 0; j < _UH2.size(); j++)
    {
        sum += _UH2[j] * _wQuantity[i - j];
    }
    _Q1[i] = (sum * 0.1);
}
void GR4J::updateQ9(int i)
{
    long double sum = 0;
    for (size_t j = 0; j < _UH1.size(); j++)
    {
        sum += _UH1[j] * _wQuantity[i - j];
    }
    _Q9[i] = (sum * 0.9);
}
void GR4J::updateR(int i)
{
    updateF(i);
    _R[i] = MAX(0, _R[i] + _Q9[i] + _F[i]);
    updateQr(i);
    _R[i + 1] = (_R[i] - _Qr[i]);
}
void GR4J::updateQr(int i)
{
    _Qr[i] = (_R[i] * (1 - (pow(1 + (pow(_R[i] / _X3, 4.0)), (-1.0 / 4.0)))));
}
void GR4J::updateQd(int i)
{
    _Qd[i] = (_Q1[i] + _F[i]);
}
void GR4J::updateQsim(int i)
{
    _Qsim[i] = (_Qd[i] + _Qr[i]);
}
void GR4J::updateF(int i)
{
    _F[i] = (_X2 * pow((_R[i] / _X3), (7.0 / 2.0)));
}
void GR4J::r_squared()
{
    clock_t start = clock();
    double _Q_mm_sum = 0;
    double _Q_diff_sq_sum = 0;

    for (size_t i = 0; i < _Qsim.size(); i++)
    {
        double _Q_mm = (_Q[i] * 86400) / (_Area * pow(1000, 2)) * 1000;
        _Q_mm_sum += _Q_mm;
        _Q_mm_vec[i] = (_Q_mm);
        _Q_diff_sq_sum += pow(_Q_mm - _Qsim[i], 2);
    }
    double _Q_mm_avg = _Q_mm_sum / _Qsim.size();
    std::vector<long double>().swap(_Qsim);

    double _Avg_sum = 0;
    for (size_t i = 0; i < _Q_mm_vec.size(); i++)
    {
        _Avg_sum += pow(_Q_mm_vec[i] - _Q_mm_avg, 2);
    }
    std::vector<long double>().swap(_Q_mm_vec);
    double _r_squared = 1 - (_Q_diff_sq_sum / _Avg_sum);
    start = clock() - start;

    _R_squared = _r_squared;
}