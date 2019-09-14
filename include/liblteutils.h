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


/* Ref Specific DL*/
class RSDL {
    public:
    RSDL(const uint16_t& nCellID,
        const uint8_t& nDLRB,
        const int& CPType);

    const cvec& getRS(const uint8_t slot,
                    const uint8_t symb) const;

    double getShift(const uint8_t& slot,
                const uint8_t& symb,
                const uint8_t& port) const;

    private:
    uint8_t nSymbDL;
    std::vector<cvec> table;
    mat shiftTable;
};

/* Rate matching/unmatching of convolutionally */
/* coded transport                             */
cvec rateMatch(const cmat& d, const uint32_t& nE);
mat rateUnmatch(const vec& eEst, const uint32_t nC);

/* Convolutional encoding and decoding */
bmat convEncode(const bvec& c);
bvec convDecode(const mat& dEst);

/* Class holding modulation maps */
class ModMap {
    public:
    ModMap();

    /* mod : QAM QAM16 QAM64 */
    const cvec& operator()(const int8_t mod) const;

    private:
    Array <cvec> table;

};

/* Compute CRC */
/* crc : CRC8 CRC16 CRC24A/B */
bvec getCRC(const bvec& a, const int8_t crc);

/* Mod bits to symbols and demod symbols to bits */
cvec modBits(const bvec& bits, const int8_t mod);
vec demodSymbs(const cvec& symbs, vec nP, const int8_t mod);


#endif // LIBLTEUTILS_H