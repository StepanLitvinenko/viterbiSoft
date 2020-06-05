#ifndef MYCODER_H
#define MYCODER_H

#include <ostream>
#include <string>
#include <utility>
#include <vector>


class MyCoder
{
public:
    MyCoder(std::vector<std::string> polynomials, uint8_t codeRestrict);

    void Encode(const std::vector <uint8_t> &codedData);

    std::vector <uint8_t> GetEncodedData();

private:

    struct CoderStates
    {
        std::vector <uint8_t> state;
        std::vector <uint8_t> encodedBits;

    };

    const uint8_t sizeMask = 3;

    uint8_t codeRestrict;
    std::vector<std::string> polynomials;
    std::vector <uint8_t> calcPolynomials;

    std::vector <vector <CoderStates>> coderStates;


    std::vector <uint8_t> encodedData;

    void CalculateStates();
    void CalculatePolynomials();

    std::vector <uint8_t>  Oct2BinVect(uint8_t num);





};

#endif // MYCODER_H
