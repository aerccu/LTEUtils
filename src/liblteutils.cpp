/*
 * -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: 4; -*-
 * Author        : aerccu
 * Created       : 14.09.19
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


#include "liblteutils.h"
#include "utils.h"
#include "rom.h"


bvec genPRBS(const uint32_t cinit, const uint32_t pn) {
    bvec x1(31);
    bvec x2(31);

    uint32_t cinitTemp(cinit);
    for(uint8_t t=0; t<31; t++){
        x1(t) = 0;
        x2(t) = cinitTemp & 1;
        cinitTemp = cinitTemp >> 1;
    }
    x1(0) = 1;

    /* #GPP 36.211 7,2 */
    const static bin x1Init[] =  {
        0,1,0,1,1,1,1,0,0,1,0,0,1,0,0,0,0,1,0,1,1,0,0,0,0,1,0,0,0,0,0,
        0,0,1,0,1,1,1,1,0,0,1,0,0,1,0,0,0,0,1,0,1,1,0,0,0,0,1,0,0,0,0,
        0,0,0,1,0,1,1,1,1,0,0,1,0,0,1,0,0,0,0,1,0,1,1,0,0,0,0,1,0,0,0,
        0,0,0,0,1,0,1,1,1,1,0,0,1,0,0,1,0,0,0,0,1,0,1,1,0,0,0,0,1,0,0,
        0,0,0,0,0,1,0,1,1,1,1,0,0,1,0,0,1,0,0,0,0,1,0,1,1,0,0,0,0,1,0,
        0,0,0,0,0,0,1,0,1,1,1,1,0,0,1,0,0,1,0,0,0,0,1,0,1,1,0,0,0,0,1,
        1,0,0,1,0,0,0,1,0,1,1,1,1,0,0,1,0,0,1,0,0,0,0,1,0,1,1,0,0,0,0,
        0,1,0,0,1,0,0,0,1,0,1,1,1,1,0,0,1,0,0,1,0,0,0,0,1,0,1,1,0,0,0,
        0,0,1,0,0,1,0,0,0,1,0,1,1,1,1,0,0,1,0,0,1,0,0,0,0,1,0,1,1,0,0,
        0,0,0,1,0,0,1,0,0,0,1,0,1,1,1,1,0,0,1,0,0,1,0,0,0,0,1,0,1,1,0,
        0,0,0,0,1,0,0,1,0,0,0,1,0,1,1,1,1,0,0,1,0,0,1,0,0,0,0,1,0,1,1,
        1,0,0,1,0,1,0,0,1,0,0,0,1,0,1,1,1,1,0,0,1,0,0,1,0,0,0,0,1,0,1,
        1,1,0,1,1,0,1,0,0,1,0,0,0,1,0,1,1,1,1,0,0,1,0,0,1,0,0,0,0,1,0,
        0,1,1,0,1,1,0,1,0,0,1,0,0,0,1,0,1,1,1,1,0,0,1,0,0,1,0,0,0,0,1,
        1,0,1,0,0,1,1,0,1,0,0,1,0,0,0,1,0,1,1,1,1,0,0,1,0,0,1,0,0,0,0,
        0,1,0,1,0,0,1,1,0,1,0,0,1,0,0,0,1,0,1,1,1,1,0,0,1,0,0,1,0,0,0,
        0,0,1,0,1,0,0,1,1,0,1,0,0,1,0,0,0,1,0,1,1,1,1,0,0,1,0,0,1,0,0,
        0,0,0,1,0,1,0,0,1,1,0,1,0,0,1,0,0,0,1,0,1,1,1,1,0,0,1,0,0,1,0,
        0,0,0,0,1,0,1,0,0,1,1,0,1,0,0,1,0,0,0,1,0,1,1,1,1,0,0,1,0,0,1,
        1,0,0,1,0,1,0,1,0,0,1,1,0,1,0,0,1,0,0,0,1,0,1,1,1,1,0,0,1,0,0,
        0,1,0,0,1,0,1,0,1,0,0,1,1,0,1,0,0,1,0,0,0,1,0,1,1,1,1,0,0,1,0,
        0,0,1,0,0,1,0,1,0,1,0,0,1,1,0,1,0,0,1,0,0,0,1,0,1,1,1,1,0,0,1,
        1,0,0,0,0,0,1,0,1,0,1,0,0,1,1,0,1,0,0,1,0,0,0,1,0,1,1,1,1,0,0,
        0,1,0,0,0,0,0,1,0,1,0,1,0,0,1,1,0,1,0,0,1,0,0,0,1,0,1,1,1,1,0,
        0,0,1,0,0,0,0,0,1,0,1,0,1,0,0,1,1,0,1,0,0,1,0,0,0,1,0,1,1,1,1,
        1,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,1,1,0,1,0,0,1,0,0,0,1,0,1,1,1,
        1,1,0,1,0,0,0,0,0,0,1,0,1,0,1,0,0,1,1,0,1,0,0,1,0,0,0,1,0,1,1,
        1,1,1,1,1,0,0,0,0,0,0,1,0,1,0,1,0,0,1,1,0,1,0,0,1,0,0,0,1,0,1,
        1,1,1,0,1,1,0,0,0,0,0,0,1,0,1,0,1,0,0,1,1,0,1,0,0,1,0,0,0,1,0,
        0,1,1,1,0,1,1,0,0,0,0,0,0,1,0,1,0,1,0,0,1,1,0,1,0,0,1,0,0,0,1,
        1,0,1,0,1,0,1,1,0,0,0,0,0,0,1,0,1,0,1,0,0,1,1,0,1,0,0,1,0,0,0
    };
    const static bmat x1InitMat(x1Init, 31, 31);

    const static bin x2Init[] = {
        0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,
        0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,
        0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,1,0,0,1,0,0,0,0,0,
        0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,1,0,0,1,0,0,0,0,
        0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,1,0,0,1,0,0,0,
        0,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,1,0,0,1,0,0,
        0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,1,0,0,1,0,
        0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,1,0,0,1,
        1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,1,0,0,
        0,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,1,0,
        0,0,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,1,
        1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,
        1,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,
        0,1,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,
        0,0,1,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,
        1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,
        0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,
        0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,
        0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,
        1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,
        0,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,
        0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,
        0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,
        1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,
        0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,
        0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,
        0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,
        0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,
        1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,
        1,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,
        1,0,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0
    };
    const static bmat x2InitMat(x2Init, 31, 31);

    x1 = x1InitMat*x1;
    x2 = x1InitMat*x2;

    bvec res(pn);
    for (uint32_t t=0; t<pn; t++){
        res(t) = x1(0) + x2(0);
        bool x1New = x1(0) + x1(3);
        bool x2New = x2(0) + x2(1) + x2(2) + x2(3);
        for (uint8_t k=0; k<30; k++){
            x1(k) = x1(k+1);
            x2(k) = x2(k+1);
        }
        x1(30) = x1New;
        x2(30) = x2New;
    }

    return res;
}

cvec getPSSFD(const uint8_t& t){
    /* Zadoff-Chu root sequence            */
    /* Ensuring zero cyclic autocorrection */
    /* at all nonzero lags                 */
    const int zcRootSeq[3] = {25, 29, 34};
    const vector<int> zcSeq(zcRootSeq, zcRootSeq+3);
    cvec res = exp((complex<double>(0,-1)*pi*zcSeq[t]/63)
                *elem_mult(ivec("0:62"), ivec("1:63")));
    res.del(31);
    return res;
}

PSSFD::PSSFD(){
    seq.resize(3);
    for (uint8_t t=0; t<3; t++){
        seq[t] = getPSSFD(t);
    }
}

const cvec& PSSFD::operator[](const uint8_t& idx) const {
    return seq[idx];
}

PSSTD::PSSTD(){
    cvec fd; cvec td;
    cvec idft;
    seq.resize(3);
    for (uint8_t t=0; t<3; t++){
        fd = getPSSFD(t);
        idft = concat(zeros_c(1), fd(31, 61), zeros_c(65), fd(0,30));
        td = ifft(idft)*sqrt(length(idft)) * sqrt(128.0/62.0);
        seq[t] = concat(td(119, 127), td);
    }
}

const cvec& PSSTD::operator[](const uint8_t& idx) const {
    return seq[idx];
}




ivec getSSSFD(const uint8_t nID1, const uint8_t nID2, const uint8_t slot){

    const uint32_t qPrime = floor_i(nID1/30);
    const uint32_t q      = floor_i((nID1+qPrime*(qPrime+1)/2)/30);
    const uint32_t mPrime = nID1+q*(q+1)/2;
    const uint32_t m0     = utils::mod(mPrime, 31);
    const uint32_t m1     = utils::mod(m0+floor_i(mPrime/31)+1, 31);

    ivec sTilda("0 0 0 0 1 0 0 1 0 1 1 0 0 1 1 1 1 1 0 0 0 1 1 0 1 1 1 0 1 0 1");
    sTilda = 1-2*sTilda;

    ivec cTilda("0 0 0 0 1 0 1 0 1 1 1 0 1 1 0 0 0 1 1 1 1 1 0 0 1 1 0 1 0 0 1");
    cTilda = 1-2*cTilda;

    ivec zTilda("0 0 0 0 1 1 1 0 0 1 1 0 1 1 1 1 1 0 1 0 0 0 1 0 0 1 0 1 0 1 1");
    zTilda = 1-2*zTilda;

    ivec s0_m0 = sTilda(utils::mod(utils::range(m0,m0+30),31));
    ivec s1_m1 = sTilda(utils::mod(utils::range(m1,m1+30),31));

    ivec c0 = cTilda(utils::mod(utils::range(nID2,nID2+30),31));
    ivec c1 = cTilda(utils::mod(utils::range(nID2+3,nID2+30+3),31));

    ivec z1_m0 = zTilda(utils::mod(utils::range(0,30)+utils::mod(m0,8),31));
    ivec z1_m1 = zTilda(utils::mod(utils::range(0,30)+utils::mod(m1,8),31));

    ivec d1, d2;
    if (slot == 0){
        d2=elem_mult(s1_m1,c1,z1_m0);
        d1=elem_mult(s0_m0,c0);
    } else {
        d2=elem_mult(s0_m0,c1,z1_m1);
        d1=elem_mult(s1_m1,c0);
    }

    imat SSS(2,31);
    SSS.set_row(0,d1);
    SSS.set_row(1,d2);
    return cvectorize(SSS);
}

SSSFD::SSSFD(){
    table = vector <vector<vector<ivec> > > (168, vector<vector<ivec>>(3, vector<ivec> (2)));
    for (uint8_t nID1=0; nID1<168; nID1++){
        for(uint8_t nID2=0; nID2<3; nID2++){
            for(uint8_t slot=0; slot<2; slot++){
                table[nID1][nID2][slot] = getSSSFD(nID1, nID2, 10*slot);
            }
        }
    }
}

const ivec& SSSFD::operator()(const uint8_t &nID1, const uint8_t &nID2, const uint8_t &slot) const{
    return table[nID1][nID2][slot!=0];
}

/* Get Reference Signal - Downlink | PoC */
cvec getRSDL(const uint32_t &slot, const uint32_t &sym, 
            const uint32_t &nIDCell, const uint32_t &rbdl,
            const cpType &CPType){

    const uint32_t nCyclPrefix = (CPType==cpType::NORMAL); // Normal
    const uint32_t cInit = (1<<10)*(7*(slot+1)+sym+1)*(2*nIDCell+1)+2*nIDCell+nCyclPrefix;
    const ivec c = to_ivec(genPRBS(cInit, 4*N_MAX_RBDL));

    cvec rlns = (1/pow(2,0.5))*((1-2*c(utils::range(0,2,4*N_MAX_RBDL-1)))
                +J*(1-2*c(utils::range(1,2,4*N_MAX_RBDL-1))));

    cvec res = rlns(N_MAX_RBDL - rbdl, 2*rbdl + N_MAX_RBDL - rbdl - 1);

    return res;
}

double getRSDLShift(const uint8_t &slot, const uint8_t &sym, uint8_t &port, 
                    const cpType &cycPfx, const uint16_t &nIDCell){

    uint8_t nSymbDL = (cpType::NONE)? 7 : 6;

    double val = NAN;
    if((port==0) && (sym==0)){
        val = 0.0;
    } else if((port==0)&&(sym==nSymbDL-3)){
        val = 3.0; 
    } else if((port==1)&&(sym==0)){
        val = 3.0;
    } else if((port==1)&&(sym==nSymbDL-3)){
        val = 0.0;
    } else if((port==2)&&(sym==1)){
        val = 3.0*(slot & 1);
    } else if((port==3)&&(sym==1)){
        val = 3.0 + 3.0*(slot & 1);
    }

    return itpp::mod(val + nIDCell, 6);
}

RSDL::RSDL(const uint16_t& nCellID,
        const uint8_t& nDLRB,
        const cpType &CPType){
    nSymbDL = 7;
    if(CPType==cpType::EXTENDED){
        nSymbDL = 6;
    }

    table.resize(nSymbDL*20);
    shiftTable = mat(nSymbDL*20,4);
    shiftTable = NAN;
    for (uint8_t slotNum=0; slotNum<20; slotNum++){
        for (uint8_t t=0; t<3; t++){
            uint8_t symNumber = (t==2)? (nSymbDL-3):t;
            table[slotNum*nSymbDL+symNumber] = getRSDL(slotNum,symNumber,nCellID,nDLRB,CPType);
            if ((t==0) || (1==2)){
                shiftTable(slotNum*nSymbDL+symNumber,0)=getRSDLShift(slotNum,symNumber,0,CPType,nCellID);
                shiftTable(slotNum*nSymbDL+symNumber,1)=getRSDLShift(slotNum,symNumber,1,CPType,nCellID);
            } else {
                shiftTable(slotNum*nSymbDL+symNumber,2)=getRSDLShift(slotNum,symNumber,2,CPType,nCellID);
                shiftTable(slotNum*nSymbDL+symNumber,3)=getRSDLShift(slotNum,symNumber,3,CPType,nCellID);
            }
        }
    }
}

const cvec& RSDL::getRS(const uint8_t slot, const uint8_t symb) const{
    return table[slot*nSymbDL+symb]; //[DC]
}

double RSDL::getShift(const uint8_t& slot,const uint8_t& symb,const uint8_t& port) const{
    return shiftTable(slot*nSymbDL+symb,port);
}

cvec rateMatch(const cmat& d, const uint32_t& nE){
    const uint8_t nC = 32;
    const uint32_t nR = ceil((double)d.cols()/nC);

    const static int permPatternC[] = {1,17,9,25,5,21,13,29,3,19,11,27,7,23,15,31,0,16,8,24,4,20,12,28,2,18,10,26,6,22,14,30};
    const ivec permPattern(permPatternC,32);
    cmat v(3,nR*nC);

    #ifndef NDEBUG 
    v=NAN; 
    #endif

    for(uint8_t t=0; t<3; t++){
        cvec rowTMP = d.get_row(t);
        cvec nanTMP(nR*nC-d.cols());
        nanTMP = NAN;
        rowTMP = concat(nanTMP,rowTMP);
        cmat y = transpose(reshape(rowTMP,nC,nR));

        cmat permY(nR,nC);
        #ifndef NDEBUG
        permY=NAN;
        #endif

        for(uint8 k=0; k<32; k++){
            permY.set_col(k,y.get_col(permPattern(k)));
        }
        v.set_row(t,cvectorize(permY));
    }

    cvec w = cvectorize(transpose(v));

    cvec e(nE);
    #ifndef NDEBUG
    uint32_t k=0;
    uint32_t j=0;
    while(k<nE){
        if(isfinite(w(j).real())){
            e(k)=w(j);
            k++;
        }
        j=mod(j+1,3*nR*nC);
    }
    return e;
}

mat rateUnmatch(const vec& eEst, const uint32_t nC){

    mat dProbeReal = repmat(utils::range(0.0,2.0),1,nC,false);
    mat dProbeImg  = repmat(utils::range(0.0,nC-1.0),3,1,true);
    cmat dProbe = to_cmat(dProbeReal,dProbeImg);
    cvec eProbe = rateMatch(dProbe,length(eEst));

    const vec eX = eEst;
    mat dX(3,nC);
    dX = 0.0;
    imat dXCount(3,nC);
    dXCount = 0;
    for (uint32_t t=0; t<length(eEst); t++){
        uint8_t r = real(eProbe(t));
        uint32_t c = imag(eProbe(t));
        dX(r,c) += eX(t);
        dXCount(r,c)++;
    }

    for (uint8_t r=0; r<3; r++){
        for (uint32_t c=0; c<nC; c++){
            if (dXCount(r,c)>1){
                dX(r,c) = dX(r,c)/dXCount(r,c);
            }
        }
    }

    return dX;
}

/* convolutional encoding */
bmat convEncode(const bvec& c){
    Convolutional_Code coder;
    ivec gen(3);
    gen(0) = 0133;
    gen(1) = 0171;
    gen(2) = 0165;
    coder.set_generator_polynomials(gen,7);

    bvec dVec = coder.encode_tailbite(c);
    bmat d    = reshape(dVec, 3, length(c));

    return d;
}


/* convolutional decoding */
bvec convDecode(const mat& dEst){
    Convolutional_Code coder;
    ivec gen(3);
    gen(0) = 0133;
    gen(1) = 0171;
    gen(2) = 0165;
    coder.set_generator_polynomials(gen,7);

    vec  dEstV = cvectorize(dEst);
    bvec cEst  = coder.decode_tailbite(dEstV);

    return cEst;
}


/* Class holding modulation maps */
ModMap::ModMap(){
    ivec mapQAMreal("1 1 -1 -1");
    ivec mapQAMimag("1 -1 1 -1");

    ivec mapQAM16real("1 1 3 3 1 1 3 3 -1 -1 -3 -3 -1 -1 -3 -3");
    ivec mapQAM16imag("1 3 1 3 -1 -3 -1 -3 1 3 1 3 -1 -3 -1 -3");

    ivec mapQAM64real("3 3 1 1 3 3 1 1 5 5 7 7 5 5 7 7 3 3 1 1 3 3 1 1 5 5 7 7 5 5 7 7 -3 -3 -1 -1 -3 -3 -1 -1 -5 -5 -7 -7 -5 -5 -7 -7 -3 -3 -1 -1 -3 -3 -1 -1 -5 -5 -7 -7 -5 -5 -7 -7");
    ivec mapQAM64imag("3 1 3 1 5 7 5 7 3 1 3 1 5 7 5 7 -3 -1 -3 -1 -5 -7 -5 -7 -3 -1 -3 -1 -5 -7 -5 -7 3 1 3 1 5 7 5 7 3 1 3 1 5 7 5 7 -3 -1 -3 -1 -5 -7 -5 -7 -3 -1 -3 -1 -5 -7 -5 -7");

    table.set_size(3);
    table(0) = to_cvec(mapQAMreal, mapQAMimag)/sqrt(2);
    table(1) = to_cvec(mapQAM16real, mapQAM16imag)/sqrt(10);
    table(2) = to_cvec(mapQAM64real, mapQAM64imag)/sqrt(42);
}

const cvec& ModMap::operator()(const modType &mod) const {
    if(mod==modType::QAM){
        return table(0);
    } else if (mod==modType::QAM16){
        return table(1);
    } else if (mod==modType::QAM64){
        return table(2);
    }
};


cvec modBits(const bvec& bits, const modType &mod) {
    uint8_t bps;
    if(mod==modType::QAM){
        bps = 2;
    } else if (mod==modType::QAM16){
        bps = 4;
    } else if (mod==modType::QAM64){
        bps = 6;
    } else {}
    //[]

    Modulator<complex<double>> modulator( ROMTABLES.modmap(mod), utils::range(0, (1<<bps)-1));
    cvec res = modulator.modulate_bits(bits);
    return res;
}


vec demodSymbs(const cvec& symbs, vec nP, const modType &mod) {
    uint8_t bps;
    if(mod==modType::QAM){
        bps = 2;
    } else if (mod==modType::QAM16){
        bps = 4;
    } else if (modType::QAM64){
        bps = 6;
    } else {}
    //[]

    Modulator<complex<double>> Modulator(ROMTABLES.modmap(mod), utils::range(0, (1<<bps)-1));
    cvec gain = 1.0/to_cvec(sqrt(nP));
    vec res = Modulator.demodulate_soft_bits( elem_mult(symbs, gain), gain, 1);
    return res;
}


bvec getCRC(const bvec& a, const crcType crc) {
    bvec poly;
    if(crc==crcType::CRC8){
        poly = bvec("1 1 0 0 1 1 0 1 1");
    } else if (crc==crcType::CRC16){
        poly = bvec("1 0 0 0 1 0 0 0 0 0 0 1 0 0 0 0 1");
    } else if (crc==crcType::CRC24A){
        poly = bvec("1 1 0 0 0 0 1 1 0 0 1 0 0 1 1 0 0 1 1 1 1 1 0 1 1");
    } else if (crc==crcType::CRC24B){
        poly = bvec("1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 0 0 0 1 1")
    } else {}

    CRC_Code crccalc;
    crccalc.set_generator(poly);

    bvec par; crccalc.parity(a, par);
    return par;
}