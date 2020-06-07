#ifndef FILEREADER_H
#define FILEREADER_H

#include <ostream>
#include <string>
#include <utility>
#include <vector>



inline std::vector <float> ReadFile (std::string fileName){

    std::ifstream in( fileName, std::ifstream::binary );

    assert( in.is_open( ) );
    in.seekg( 0, in.end );
    int32_t actualLength = in.tellg( ) / sizeof( float);
    in.seekg( 0, in.beg );

    std::vector <float> dataRead(actualLength);
    in.read( reinterpret_cast<char*>(dataRead.data()), actualLength*sizeof(float));

    return dataRead;

}












#endif // FILEREADER_H
