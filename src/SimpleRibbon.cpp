#include "SimpleRibbon.h"
#include "ribbon.hpp"

template<size_t coeff_bits, size_t result_bits>
struct RetrievalConfig : public ribbon::RConfig<coeff_bits, result_bits,
        /* threshold mode */ (result_bits >= 64) ? ribbon::ThreshMode::twobit : ribbon::ThreshMode::onebit,
        /* sparse */ false, /* interleaved */ true, /* cls */ false, /* bucket_sh */ 0, /* key type */ uint64_t> {
    static constexpr bool log = false;
    static constexpr bool kIsFilter = false;
    static constexpr bool kUseMHC = false;
};

template<size_t bits, size_t coeff_bits, typename result_t>
SimpleRibbon<bits, coeff_bits, result_t>::SimpleRibbon(std::vector<std::pair<uint64_t, result_t>> &data) {
    using Config = RetrievalConfig<coeff_bits, /*result_bits*/ bits>;
    using RibbonT = ribbon::ribbon_filter</*depth*/ 2, Config>;

    using namespace ribbon;
    IMPORT_RIBBON_CONFIG(Config);

    ribbon = new ribbon::ribbon_filter</*depth*/ 2, Config>(data.size(), 0.965, 42);
    static_cast<RibbonT*>(ribbon)->AddRange(data.begin(), data.end());
    static_cast<RibbonT*>(ribbon)->BackSubst();
}

template<size_t bits, size_t coeff_bits, typename result_t>
SimpleRibbon<bits, coeff_bits, result_t>::SimpleRibbon(std::istream &is) {
    using Config = RetrievalConfig<coeff_bits, /*result_bits*/ bits>;
    using RibbonT = ribbon::ribbon_filter</*depth*/ 2, Config>;

    using namespace ribbon;
    IMPORT_RIBBON_CONFIG(Config);

    ribbon = new ribbon::ribbon_filter</*depth*/ 2, Config>();
    static_cast<RibbonT*>(ribbon)->Deserialize(is);
}

template<size_t bits, size_t coeff_bits, typename result_t>
SimpleRibbon<bits, coeff_bits, result_t>::SimpleRibbon() {
    ribbon = nullptr;
}

template<size_t bits, size_t coeff_bits, typename result_t>
SimpleRibbon<bits, coeff_bits, result_t>::SimpleRibbon (SimpleRibbon&& obj) {
    ribbon = obj.ribbon;
    obj.ribbon = nullptr;
}

template<size_t bits, size_t coeff_bits, typename result_t>
SimpleRibbon<bits, coeff_bits, result_t>::~SimpleRibbon() {
    using Config = RetrievalConfig<coeff_bits, /*result_bits*/ bits>;
    using RibbonT = ribbon::ribbon_filter</*depth*/ 2, Config>;

    if (ribbon != nullptr) {
        delete static_cast<RibbonT*>(ribbon);
    }
}

template<size_t bits, size_t coeff_bits, typename result_t>
SimpleRibbon<bits, coeff_bits, result_t>&
        SimpleRibbon<bits, coeff_bits, result_t>::operator=(SimpleRibbon<bits, coeff_bits, result_t> &&other) {
    using Config = RetrievalConfig<coeff_bits, /*result_bits*/ bits>;
    using RibbonT = ribbon::ribbon_filter</*depth*/ 2, Config>;
    if (ribbon != nullptr) {
        delete static_cast<RibbonT*>(ribbon);
    }
    ribbon = other.ribbon;
    other.ribbon = nullptr;
    return *this;
}

template<size_t bits, size_t coeff_bits, typename result_t>
result_t SimpleRibbon<bits, coeff_bits, result_t>::retrieve(uint64_t key) const {
    using Config = RetrievalConfig<coeff_bits, /*result_bits*/ bits>;
    using RibbonT = ribbon::ribbon_filter</*depth*/ 2, Config>;

    assert(ribbon != nullptr);
    return static_cast<RibbonT*>(ribbon)->QueryRetrieval(key);
}

template<size_t bits, size_t coeff_bits, typename result_t>
std::size_t SimpleRibbon<bits, coeff_bits, result_t>::sizeBytes() const {
    using Config = RetrievalConfig<coeff_bits, /*result_bits*/ bits>;
    using RibbonT = ribbon::ribbon_filter</*depth*/ 2, Config>;

    assert(ribbon != nullptr);
    assert(static_cast<RibbonT*>(ribbon)->Size() > 0);
    return static_cast<RibbonT*>(ribbon)->Size();
}

template<size_t bits, size_t coeff_bits, typename result_t>
void SimpleRibbon<bits, coeff_bits, result_t>::writeTo(std::ostream &os) {
    using Config = RetrievalConfig<coeff_bits, /*result_bits*/ bits>;
    using RibbonT = ribbon::ribbon_filter</*depth*/ 2, Config>;

    using namespace ribbon;
    IMPORT_RIBBON_CONFIG(Config);

    static_cast<RibbonT*>(ribbon)->Serialize(os);
}

template class SimpleRibbon<1, 32>;
template class SimpleRibbon<2, 32>;
template class SimpleRibbon<3, 32>;
template class SimpleRibbon<4, 32>;
template class SimpleRibbon<5, 32>;
template class SimpleRibbon<6, 32>;
template class SimpleRibbon<7, 32>;
template class SimpleRibbon<8, 32>;
template class SimpleRibbon<9, 32, uint16_t>;
template class SimpleRibbon<10, 32, uint16_t>;
template class SimpleRibbon<11, 32, uint16_t>;
template class SimpleRibbon<12, 32, uint16_t>;

template class SimpleRibbon<1, 64>;
template class SimpleRibbon<2, 64>;
template class SimpleRibbon<3, 64>;
template class SimpleRibbon<4, 64>;
template class SimpleRibbon<5, 64>;
template class SimpleRibbon<6, 64>;
template class SimpleRibbon<7, 64>;
template class SimpleRibbon<8, 64>;
template class SimpleRibbon<9, 64, uint16_t>;
template class SimpleRibbon<10, 64, uint16_t>;
template class SimpleRibbon<11, 64, uint16_t>;
template class SimpleRibbon<12, 64, uint16_t>;

template class SimpleRibbon<1, 128>;

template class SimpleRibbon<32, 64, uint32_t>;
template class SimpleRibbon<48, 64, uint64_t>;
