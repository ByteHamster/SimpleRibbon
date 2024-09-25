#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>
#include <iostream>

template<size_t bits, size_t coeff_bits = 64, typename result_t = uint8_t>
class SimpleRibbon {
        #define STATIC_LIBRARY_MESSAGE "This is a static library. \
                            You can only select the template arguments that are compiled into the library."
        static_assert(coeff_bits == 32 || coeff_bits == 64 || (bits == 1 && coeff_bits == 128), STATIC_LIBRARY_MESSAGE);
        static_assert((bits <= 8 && std::is_same<result_t, uint8_t>::value)
                        || (bits == 32 && coeff_bits == 64 && std::is_same<result_t, uint32_t>::value)
                        || (bits > 8 && bits <= 12 && std::is_same<result_t, uint16_t>::value), STATIC_LIBRARY_MESSAGE);
    private:
        void *ribbon;
    public:
        explicit SimpleRibbon(std::vector<std::pair<uint64_t, result_t>> &data);
        explicit SimpleRibbon(std::istream &is);
        SimpleRibbon();
        SimpleRibbon(SimpleRibbon&& obj);
        ~SimpleRibbon();
        SimpleRibbon &operator=(SimpleRibbon &other) = delete;
        SimpleRibbon &operator=(SimpleRibbon &&other);
        result_t retrieve(uint64_t key) const;
        std::size_t sizeBytes() const;
        void writeTo(std::ostream &os);
};
