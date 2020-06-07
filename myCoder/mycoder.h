#ifndef MYCODER_H
#define MYCODER_H

#include <ostream>
#include <string>
#include <utility>
#include <vector>
#include <deque>

class MyCoder
{
public:
    MyCoder(std::vector<std::string> polynomials, uint8_t codeRestrict);

    void Encode(const std::vector<uint16_t> &codedData);

    std::vector <uint16_t> GetEncodedData();

private:

    struct CoderStates
    {
        std::vector <uint8_t> state;
        std::vector <uint8_t> encodedBits;

    };

    const uint8_t sizeMask = 3;

    uint8_t codeRestrict;
    std::vector<std::string> polynomials;
    std::vector <std::vector <uint16_t>> calcPolynomials;

    std::deque <uint16_t> shiftRegister;

    std::vector <uint16_t> encodedData;

    //std::vector <std::vector <CoderStates>> coderStates;


    //std::vector <uint16_t> encodedData;

    void CalculateStates();
    void CalculatePolynomials();

    uint16_t Conv(std::deque<uint16_t> &memState, std::vector<uint16_t> &polynome);

    std::vector<uint16_t> Oct2BinVect(uint8_t num);





};

#endif // MYCODER_H
