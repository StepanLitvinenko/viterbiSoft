#ifndef FILEREADER_H
#define FILEREADER_H

#include <ostream>
#include <string>
#include <utility>
#include <vector>



inline std::vector <uint8_t> ReadFile (std::string fileName){

    std::ifstream in( fileName, std::ifstream::binary );

    assert( in.is_open( ) );
    in.seekg( 0, in.end );
    int32_t actualLength = in.tellg( ) / sizeof( uint8_t);
    in.seekg( 0, in.beg );

    std::vector <uint8_t> dataRead(actualLength);
    in.read( reinterpret_cast<char*>(dataRead.data()), actualLength*sizeof(uint8_t));

    return dataRead;

}












#endif // FILEREADER_H
