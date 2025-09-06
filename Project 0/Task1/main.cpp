#include <iostream>
#include "hyperloglog.h" // Use the path to your header file

int main() {
    std::cout << "Starting HyperLogLog Cardinality Estimation..." << std::endl;

    // Create an HLL instance with b=10, which means m = 2^10 = 1024 registers.
    HyperLogLog hll(10);

    // Add some data to it.
    hll.addElement("apple");
    hll.addElement("orange");
    hll.addElement("banana");
    hll.addElement("grape");
    hll.addElement("apple"); // This is a duplicate and should not increase the count.
    hll.addElement("banana"); // This is also a duplicate.

    // Let's add many more unique items to see it work.
    for (int i = 0; i < 1000; ++i) {
        hll.addElement("user_" + std::to_string(i));
    }

    // We added 4 fruit + 1000 users = 1004 unique items.
    // The estimate should be close to this number.
    double cardinality = hll.getCardinality();

    std::cout << "---------------------------------" << std::endl;
    std::cout << "Actual unique elements: 1004" << std::endl;
    std::cout << "HLL estimated cardinality: " << cardinality << std::endl;
    std::cout << "---------------------------------" << std::endl;

    return 0;
}
