## Presto's Implementation of HLL

- The previous algorithm used 8-bit unsigned integer for storing p(0 - 255).
- But Presto's algorithm optimizes space by using 4-bit integers and overflow buckets.
- Since, most often the p-value is lesser and can be stored in a 4-bit unsigned integer, the registers\_ are 4-bits.
- What if the p-value is larger than a 4-bit int can hold? This is where overflow buckers come in.
- The MSB's that overflow the 4-bits are stored in a map, saving space.

#### Space Optimization

- The Algorithm assumes that the registers\_ can store only 4-bit integers.
- But this is not possible in C++, Since the smallest number is of 8-bits.
- So the registers\_ conceptually stores 4-bit numbers and we use overflow bucket for the overflowing p-vals.

##### _But why 4-bits?_

- It is bcoz 4-bits(0-15), p-valuse exceed 15 very rarely.
