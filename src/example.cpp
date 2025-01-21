#include <vector>
#include <iostream>
#include <SimpleRibbon.h>

int main() {
    std::vector<std::pair<uint64_t, uint8_t>> inputData = {
        {12345, 1},
        {67890, 0},
        {54321, 1}
    };

    SimpleRibbon<1> ribbon(inputData);  // 1-bit BuRR
    uint64_t hashedKey = 12345;
    uint8_t result = ribbon.retrieve(hashedKey);
    std::cout << "The result for " << hashedKey << " is " << unsigned(result) << std::endl;
    return 0;
}
