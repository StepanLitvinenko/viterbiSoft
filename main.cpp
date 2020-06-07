#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include "viterbiSoft/viterbidecoder.h"
#include "filereader.h"
#include <string>
using namespace std;

int main()
{
    std::string fileNameSource = "/home/stepan/viterbi_my/supportFiles/data.dat";
    std::string fileNameCoded = "/home/stepan/viterbi_my/supportFiles/codedData.dat";

    auto sourceData = ReadFile(fileNameSource);
    auto encodedData = ReadFile(fileNameCoded);

    int codeRestrict = 3;//кодовое ограничение, длина выходного слова на ед. меньше кодового ограничения
    std::vector <int> poly {5, 7};//полиномы в шестнадцатиричной системе, необходимо чтобы совпадали с матлабом

    ViterbiCodec Codec(codeRestrict, poly);

    encodedData[5] = 5;
    encodedData[11] = 3;
    encodedData[15] = 0;
    encodedData[30] = 1;
     encodedData[35] = 2;

    auto decoded = Codec.Decode(encodedData);

    vector <int> delta(decoded.size());

    for (int i = 0; i < sourceData.size(); ++i) delta[i] = sourceData[i] - decoded[i];/*вектор
                                                                              с неисправлеными ошибками*/
    return 0;
}
