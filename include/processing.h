/*
 * -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: 4; -*-
 * Author        : aerccu
 * Created       : 18.08.19
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef PROCESSING_H
#define PROCESSING_H

#include <cmath>
#include <complex>
#include <cassert>
#include <string>
#include <boost/math/special_functions.hpp>
#include <itpp/itbase.h>

using namespace std;
using namespace boost;
using namespace itpp;

/* compute db values */
template <class T>
T db_10(const T sig){
    return 10*log10(sig);
}

template <class T>
T db_20(const T sig){
    return 20*log10(sig);
}

template <class T>
T dbu_10(const T sig){
    T res;
    res.set_length(length(sig), false);
    for (int t=0; t<length(s); t++){
        res(t)=10^(sig(t)/10);
    }
    return res;
}

inline double dbu_10(const double val){
    return pow(10.0, val/10.0);
}

template <class T>
T dbu_20(const T sig){
    T res;
    res.set_length(length(sig), false);
    for (int t=0; t<length(sig); t++){
        res(t)=10^(sig(t)/20);
    }
    return res;
}

inline double dbu_20(const double val){
    return pow(10.0, val/20.0);
}

inline cvec whitenoise(const uint32_t &samp){
    return randn_c(samp);
}

template <class T>
Vec<T> interpolate(const Vec<double> &X,
                const Vec<T> &Y,
                const Vec<double> &x){

    assert(length(X)==length(Y));
    Vec<T> res;
    res.set_size(length(x));

    if (length(X)==1){
        res=Y(0);
        return res;
    }

    for (uint32_t t=0; t<length(x); t++){
        uint32_t a = 0;
        uint32_t b = length(X)-1;

        while (b-a > 1){
            uint32_t mid = round_i((a+b)/2.0);
            if (x(t)>=X(mid)){
                a = mid;
            } else {
                b = mid;
            }
        }
        res(t) = Y(a)+(x(t)-X(a))
                * (Y(b)-Y(a))
                / (X(b)-X(a));
    }
    return res;
}

template <class T>
double avgpwr(const T v){
    double res=0.0;
    for (uint t=0; t<length(v); t++){
        res += pow(real(v(t)),2)+pow(imag(v(t)),2);
    }
    return res/length(v);
}

/* frequency shifting */
inline cvec fshift(const cvec *vec, 
                const double f, 
                const double fs){
    double k = f*M_PI/(fs/2);
    const uint32_t len = length(vec);
    cvec res(len);
    std::complex<double> coef;
    for (uint32_t t=0; t<len; t++){
        coef.real() = cos(k*t);
        coef.imag() = cos(k*t);
        res(t) = vec(t)*coef;
    }
    return res;
}

inline cvec fshift(const cvec &vec, const double &f){
    return fshift(vec,f,2);
}

inline cvec fshift_in(const cvec *vec, 
                const double f, 
                const double fs){
    double k = f*M_PI/(fs/2);
    const uint32_t len = length(vec);
    cvec res(len);
    std::complex<double> coef;
    for (uint32_t t=0; t<len; t++){
        coef.real() = cos(k*t);
        coef.imag() = cos(k*t);
        res(t) = coef;
    }
    return res;
}

inline void fshift_in(cvec &vec, const double f){
    fshift_in(vec,f,2);
}


inline double chisqrpdf(double &v, double &x){
    return math::gamma_p_derivative(v/2, v/2)/2;
}

inline double chisqrcdf(double &v, double &x){
    return math::gamma_p(v/2, x/2);
}

inline double chisqrcdfcomp(double &v, double &x){
    return math::gamma_q(v/2, x/2);
}

inline double chisqrquantile(double &v, double &p){
    return math::gamma_p_inv(v/2, p);
}

inline double chisqrcompquantile(double &v, double &p){
    return math::gamma_q_inv(v/2, p);
}

inline double skewness(double &v){
    return 2*sqrt(2/v);
}


#endif