#include <iostream>
#include <vector>
#include "viterbidecoder.h"
#include <cstdlib>
using namespace std;

int main()
{

//    uint64_t a = 5;

//    char b = 1<<a;


   // int stopDot;
    std::vector <int> poly;
    poly.push_back(5);poly.push_back(7);

    //std::vector <int> bits2Code {0, 1, 1};

    ViterbiCodec Codec(3, poly);


    string bits2Code = "01010";

    int a = 0;

    a = 1<<3;





    auto coded = Codec.Encode(bits2Code);

    //vector <int> myCoded{0,0,1,1,0,0,1,0,0,1,0,0};

  //  auto decoded = Codec.Decode(myCoded);

    int stopDot;

 return 0;
}
