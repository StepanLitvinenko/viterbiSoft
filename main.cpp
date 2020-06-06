#include <iostream>
#include <vector>

#include <cstdlib>
#include "viterbidecoder.h"
#include "mycoder.h"
using namespace std;

int main()
{

//    uint64_t a = 5;

//    char b = 1<<a;
   std::vector <string> polymy;
   polymy.push_back("5");polymy.push_back("7");
   // int stopDot;


//    MyCoder myCodec(polymy, 3);

//    std::vector <uint16_t> codedData{1, 0, 0, 0, 1};


//    myCodec.Encode(codedData);

    std::vector <int> poly;
    poly.push_back(5);poly.push_back(7);

    std::vector <uint16_t> bits2Code {0, 1, 1};

    ViterbiCodec Codec(3, poly);


   // string bits2Code = "111";

    int a = 0;

    a = 4&1;

    std::vector <uint16_t> encodedData;



    auto coded = Codec.Encode(bits2Code);

    //vector <int> myCoded{0,0,1,1,0,0,1,0,0,1,0,0};

  //  auto decoded = Codec.Decode(myCoded);

    int stopDot;
    std::cout<<stopDot;

 return 0;
}
