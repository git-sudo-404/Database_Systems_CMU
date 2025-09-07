#include <iostream>
#include <string>
#include <vector>
#include <cmath> // For std::abs in error calculation

// Make sure the path to your header is correct for your project structure
#include "hyperloglog_presto.h" 

int main() {
    // --- Setup ---
    // Use a reasonable number of bits for the index. 12 bits -> 4096 registers.
    // The more registers, the higher the accuracy (and memory usage).
    uint8_t bits = 12;
    HyperLogLog_Presto hll(bits);

    // The number of unique items we will add.
    const int actual_cardinality = 10000;

    std::cout << "Testing HyperLogLog_Presto with " << actual_cardinality << " unique elements..." << std::endl;
    std::cout << "Using b=" << static_cast<int>(bits) << " (" << (1 << bits) << " registers)." << std::endl;

    // --- Add Elements ---
    for (int i = 0; i < actual_cardinality; ++i) {
        // Generate a unique string for each element.
        std::string element = "user_id_" + std::to_string(i);
        hll.addElem(element);
    }
    
    std::cout << "Finished adding elements." << std::endl;

    // --- Get Result ---
    double estimated_cardinality = hll.GetCardinality();

    // --- Report Results ---
    double error = (std::abs(actual_cardinality - estimated_cardinality) / actual_cardinality) * 100.0;

    std::cout << "\n---------------------------------" << std::endl;
    std::cout << "Actual Cardinality:    " << actual_cardinality << std::endl;
    std::cout << "Estimated Cardinality: " << estimated_cardinality << std::endl;
    std::cout << "Percentage Error:      " << error << "%" << std::endl;
    std::cout << "---------------------------------" << std::endl;

    return 0;
}
