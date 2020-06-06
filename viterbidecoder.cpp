// Implementation of ViterbiCodec.
//
// Author: Min Xu <xukmin@gmail.com>
// Date: 01/30/2015

#include "viterbidecoder.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <vector>
#include <cmath>

namespace {

int HammingDistance(const std::string& x, const std::string& y) {
    assert(x.size() == y.size());
    int distance = 0;
    for (size_t i = 0; i < x.size(); i++) {
        distance += x[i] != y[i];
    }
    return distance;
}

}  // namespace

std::ostream& operator <<(std::ostream& os, const ViterbiCodec& codec) {
    os << "ViterbiCodec(" << codec.constraint() << ", {";
    const std::vector<int>& polynomials = codec.polynomials();
    assert(!polynomials.empty());
    os << polynomials.front();
    for (size_t i = 1; i < polynomials.size(); i++) {
        os << ", " << polynomials[i];
    }
    return os << "})";
}

int ReverseBits(int num_bits, int input) {
    assert(input < (1 << num_bits));
    int output = 0;
    while (num_bits-- > 0) {
        output = (output << 1) + (input & 1);
        input >>= 1;
    }
    return output;
}

ViterbiCodec::ViterbiCodec(int constraint, const std::vector<int>& polynomials)
    : constraint_(constraint), polynomials_(polynomials) {
    assert(!polynomials_.empty());
    for (size_t i = 0; i < polynomials_.size(); i++) {
        assert(polynomials_[i] > 0);
        assert(polynomials_[i] < (1 << constraint_));
    }
    InitializeOutputs();

}

int ViterbiCodec::num_parity_bits() const {
    return static_cast<int>(polynomials_.size());
}

int ViterbiCodec::NextState(int current_state, int input) const {
    return (current_state >> 1) | (input << (constraint_ - 2));
}




std::vector< uint16_t> ViterbiCodec::Output(int current_state, int input)  {
     //outputs_vector.at(current_state | (input << (constraint_ - 1)));

   // std::copy(tempForCopy.begin(), tempForCopy.end(), back_inserter(encodedData));


    //return outputs_.at(current_state | (input << (constraint_ - 1)));
    return outputs_vector.at(current_state | (input << (constraint_ - 1)));

}

std::vector< uint16_t> ViterbiCodec::Encode(std::vector< uint16_t>& bits)  {
   std::vector< uint16_t>  encoded;
    int state = 0;


    // Encode the message bits.
    for (size_t i = 0; i < bits.size(); i++) {
        uint16_t input = bits[i];
        assert(input == 0 || input == 1);

        auto temp = Output(state, input);
        std::copy(temp.begin(), temp.end(), back_inserter(encoded));
        //encoded += Output(state, input);
        state = NextState(state, input);
    }

    // Encode (constaint_ - 1) flushing bits.
    for (int i = 0; i < constraint_ - 1; i++) {
         auto temp = Output(state, 0);
        std::copy(temp.begin(), temp.end(), back_inserter(encoded));
        //encoded += Output(state, 0);
        state = NextState(state, 0);
    }
std::cout<<5;
    return encoded;
}

void ViterbiCodec::InitializeOutputs() {
    outputs_.resize(1 << constraint_);//аутпутс_ - строка, изменяем ее размер в соответствии с 2 в степени кодового ограничения
    outputs_vector.resize(pow(2,constraint_));
    for (auto &a:outputs_vector) a.resize(polynomials_.size());
    //auto a = outputs_;
    // num_parity_bits()
    for (size_t i = 0; i < outputs_.size(); i++) {//цикл бежит по размеру строки
        for (int j = 0; j < num_parity_bits(); j++) {//внутренний бежит по полиномам
            // Reverse polynomial bits to make the convolution code simpler.
            int polynomial = ReverseBits(constraint_, polynomials_[j]);//биты, которые полиномом представляются - реверсируются
            auto input = i;//номер иттерации
            auto output = 0;//выход, который инициализируется
            for (int k = 0; k < constraint_; k++) {//цикл бежит по длине кодового ограничения
                output ^= (input & 1)/*побитовое И, т.е.порядок входного полинома побитово берется*/ & (polynomial & 1);//побитовое И, значение полинома
                //проверяется на//нечётность
                polynomial >>= 1;
                input >>= 1;
            }
            outputs_[i] += output ? "1" : "0";
            outputs_vector[i][j] = output;

            //uint8_t output2 = outputs_[i] - '0';
            //outputs_vector.push_back(output);
        }
    }
}

//int ViterbiCodec::BranchMetric(const std::string& bits,
//                               int source_state,
//                               int target_state)  {
//    assert(bits.size() == num_parity_bits());
//    assert((target_state & ((1 << (constraint_ - 2)) - 1)) == source_state >> 1);
//    const std::string output =
//            Output(source_state, target_state >> (constraint_ - 2));

//    return HammingDistance(bits, output);
//}

//std::pair<int, int> ViterbiCodec::PathMetric(
//        const std::string& bits,
//        const std::vector<int>& prev_path_metrics,
//        int state)  {
//    int s = (state & ((1 << (constraint_ - 2)) - 1)) << 1;
//    auto source_state1 = s | 0;
//    auto source_state2 = s | 1;

//    int pm1 = prev_path_metrics[source_state1];
//    if (pm1 < std::numeric_limits<int>::max()) {
//        pm1 += BranchMetric(bits, source_state1, state);
//    }
//    int pm2 = prev_path_metrics[source_state2];
//    if (pm2 < std::numeric_limits<int>::max()) {
//        pm2 += BranchMetric(bits, source_state2, state);
//    }

//    if (pm1 <= pm2) {
//        return std::make_pair(pm1, source_state1);
//    } else {
//        return std::make_pair(pm2, source_state2);
//    }
//}

//void ViterbiCodec::UpdatePathMetrics(const std::string& bits,
//                                     std::vector<int>* path_metrics,
//                                     Trellis* trellis)  {
//    std::vector<int> new_path_metrics(path_metrics->size());
//    std::vector<int> new_trellis_column(1 << (constraint_ - 1));
//    for (size_t i = 0; i < path_metrics->size(); i++) {
//        std::pair<int, int> p = PathMetric(bits, *path_metrics, static_cast<int>(i));
//        new_path_metrics[i] = p.first;
//        new_trellis_column[i] = p.second;
//    }

//    *path_metrics = new_path_metrics;
//    trellis->push_back(new_trellis_column);
//}

//std::string ViterbiCodec::Decode(const std::string& bits)  {
//    // Compute path metrics and generate trellis.
//    Trellis trellis;
//    std::vector<int> path_metrics(1 << (constraint_ - 1),
//                                  std::numeric_limits<int>::max());
//    path_metrics.front() = 0;
//    for (int i = 0; i < static_cast<int>(bits.size()); i += num_parity_bits()) {
//        std::string current_bits(bits, i, num_parity_bits());
//        // If some bits are missing, fill with trailing zeros.
//        // This is not ideal but it is the best we can do.
//        if (current_bits.size() < static_cast<size_t>(num_parity_bits())) {
//            current_bits.append(
//                        std::string(static_cast<size_t>(num_parity_bits()) - current_bits.size(), '0'));
//        }
//        UpdatePathMetrics(current_bits, &path_metrics, &trellis);
//    }

//    // Traceback.
//    std::string decoded;
//    int state = std::min_element(path_metrics.begin(), path_metrics.end()) -
//            path_metrics.begin();
//    for (int i = trellis.size() - 1; i >= 0; i--) {
//        decoded += state >> (constraint_ - 2) ? "1" : "0";
//        state = trellis[i][state];
//    }
//    std::reverse(decoded.begin(), decoded.end());

//    // Remove (constraint_ - 1) flushing bits.
//    return decoded.substr(0, decoded.size() - constraint_ + 1);
//}
