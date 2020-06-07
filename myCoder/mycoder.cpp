#include "mycoder.h"
#include <cassert>
#include <cmath>
MyCoder::MyCoder(std::vector<std::string> polynomials, uint8_t codeRestrict)
{
    this->polynomials = polynomials;
    this->codeRestrict = codeRestrict;
    calcPolynomials.resize(polynomials.size());
    CalculatePolynomials();
    for (int i = 0; i < codeRestrict; ++i) {
        shiftRegister.push_back(0);
    }
//    coderStates.resize(std::pow(2,(codeRestrict-1)));//ALARM
//    for(auto& c :coderStates) c.resize(codeRestrict);
}
void MyCoder::Encode(const std::vector<uint16_t> &codedData){

    for (int i = 0; i < codedData.size() + codeRestrict+1; ++i) {


        if (i>codedData.size()) shiftRegister.push_back(0);
        else             shiftRegister.push_back(codedData[i]);

        shiftRegister.pop_front();



        for (int j = 0; j < calcPolynomials.size(); ++j) {
            uint16_t codedSymb = Conv(shiftRegister, calcPolynomials[j]);
            encodedData.push_back(codedSymb);
            int a;

        }



    }
}

std::vector<uint16_t> MyCoder::GetEncodedData(){

}

void MyCoder::CalculateStates()
{

}

void MyCoder::CalculatePolynomials()
{
    for (int i = 0; i < polynomials.size(); ++i) {
        for (size_t j = 0; j < polynomials[i].size(); ++j) {

            uint16_t num =  polynomials[i][j] - '0';

            //calcPolynomials[i].resize(sizeMask);

            auto binNum = Oct2BinVect(num);

            std::copy(binNum.begin(), binNum.end(), std::back_inserter(calcPolynomials[i]));
            uint16_t deltaSize = calcPolynomials[i].size() - codeRestrict;

            if (deltaSize !=0) {
                for (int i = 0; i < deltaSize; ++i) {
                    calcPolynomials.pop_back();//ту говно получается, нужен list
                }
            }
        }

    }
}

uint16_t MyCoder::Conv(std::deque <uint16_t>& memState, std::vector <uint16_t>& polynome)
{   uint16_t sum;
    for (int i = 0; i < memState.size()
         ; ++i) {

        sum = (memState[i] + polynome[i])&1;
    }
    return sum;
}

std::vector<uint16_t> MyCoder::Oct2BinVect(uint8_t num)
{
    //assert(!num>=8);
    std::vector <std::vector <uint16_t>> numbers(8);
    numbers[0] = {0,0,0};
    numbers[1] = {0,0,1};
    numbers[2] = {0,1,0};
    numbers[3] = {0,1,1};
    numbers[4] = {1,0,0};
    numbers[5] = {1,0,1};
    numbers[6] = {1,1,0};
    numbers[7] = {1,1,1};

    return numbers[num];
}














