#include "mycoder.h"
#include <cassert>
#include <cmath>
MyCoder::MyCoder(std::vector<std::string> polynomials, uint8_t codeRestrict)
{
    this->polynomials = polynomials;
    this->codeRestrict = codeRestrict;
    CalculatePolynomials();
    coderStates.resize(std::pow(2,(codeRestrict-1)));//ALARM
    for(auto& c :coderStates) c.resize(codeRestrict);
}
void MyCoder::Encode(const std::vector<uint8_t> &codedData){

}

std::vector <uint8_t> MyCoder::GetEncodedData(){

}

void MyCoder::CalculateStates()
{

}

void MyCoder::CalculatePolynomials()
{
    for (int i = 0; i < polynomials.size(); ++i) {
        for (size_t j = 0; j < polynomials[i].size(); ++j) {

            uint8_t num =  polynomials[i][j] - '0';
            calcPolynomials.reserve(sizeMask+calcPolynomials.size());
            auto binNum = Oct2BinVect(num);
            std::copy(binNum.begin(), binNum.end(), std::back_inserter(calcPolynomials));
            uint8_t deltaSize = calcPolynomials.size() - codeRestrict;

            if (deltaSize !=0) {
                for (int i = 0; i < deltaSize; ++i) {
                    calcPolynomials.pop_back();//ту говно получается, нужен list
                }
            }
        }

    }
}

std::vector<uint8_t> MyCoder::Oct2BinVect(uint8_t num)
{
    assert(num>=8);
    std::vector <std::vector <uint8_t>> numbers(8);
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














