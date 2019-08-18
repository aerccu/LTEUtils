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
#include <itpp/itbase.h>

using namespace std;
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


#endif