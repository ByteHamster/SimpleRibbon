#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>

template<size_t bits, size_t coeff_bits = 64, typename result_t = uint8_t>
class SimpleRibbon {
    private:
        void *ribbon;
    public:
        explicit SimpleRibbon(std::vector<std::pair<uint64_t, result_t>> &data);
        ~SimpleRibbon();
        result_t retrieve(uint64_t key);
        std::size_t size();
};
