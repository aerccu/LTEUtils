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

#ifndef LIBLTEUTILS_H
#define LIBLTEUTILS_H

#include <stdint.h>
#include <itpp/itbase.h>
#include <vector>

using namespace itpp;
using namespace std;

/* Pseudo Random Binary Sequence */
bvec prbs(const uint32_t cinit, const uint32_t pn);


/* Primary and Secondary Sync Signal - TD & FD */
class PSSTD {
    public:
    PSSTD();

    const cvec& operator[](const uint8_t& idx) const;
    private:
    vector<cvec> seq;
};

class PSSFD {
    public:
    PSSFD();

    const cvec& operator[](const uint8_t& idx) const;
    private:
    vector<cvec> seq;
};


class SSSFD {
    public:
    SSSFD();

    const itpp& operator()(const uint8_t& id1, 
                        const uint8_t& id2, 
                        const uint8_t& slot) const;
    private:
    static vector<vector<vector<cvec> > > table;
};







#endif // LIBLTEUTILS_H