/*
 * -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: 4; -*-
 * Author        : aerccu
 * Created       : 15.09.19
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

#ifndef UTILS_H
#define UTILS_H

#include <itpp/itbase.h>

inline int mod(const int k, const int n){
    return (n == 0)? k: (k-n*itpp::floor_i((double)k/n));
}

inline unsigned int mod(const unsigned int k, const unsigned int n){
    return (n == 0)? k: (k-n*itpp::floor_i((double)k/n));
}

inline int mod(const unsigned int k, const int n){
    return (n == 0)? k: (k-n*itpp::floor_i((double)k/n));
}

inline unsigned int mod(const int k, const unsigned int n){
    return (n == 0)? k: (k-n*itpp::floor_i((double)k/n));
}

inline double mod(const double k, const double n){
    return (n == 0)? k: (k-n*itpp::floor_i((double)k/n));
}

inline double mod(const double k, const unsigned int n){
    return (n == 0)? k: (k-n*itpp::floor_i((double)k/n));
}


ivec range(const uint32_t first, const uint32_t last){
    return range(first, (unsigned)1, last);
}

ivec range(const int first, const int last){
    return range(first, 1, last);
}

ivec range(const uint32_t first, const uint32_t incr, const uint32_t last){
    Vec<int> res;
    res.set_length(floor_i((last-first)/((double)incr))+1,false);
    for (int t=0; t<length(res); t++){
        res(t) = first + t*incr;
    }
    return res;
}





#endif // UTILS_H