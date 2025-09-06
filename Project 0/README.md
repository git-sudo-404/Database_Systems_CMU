## HyperLogLog ( A prababilitic Data Structure )

- TLDR : Used to count the number of distinct elements in a large dataset.

* Assumptions : The elements(here, UserID's) are uniformly distributed and random.

### Why HyperLogLog ?

Let's say my website is getting traffic from various devices (laptops,phones,etc.,) from all over the world. Now i want to find the number of users
logged in (or) connected to my servers. I know their UserID's are unique. But how do i find the number of unique user ID's ?

#### Compare

- Checking every UserId with every other UserId takes a lot of Time and Space.

#### Sort / Set

- Sorting them by UserId's and counting the unique vals alone (or) using a set takes O(nlogn) Time Complexity.

#### Hashing

- Hashing the UserID's is a good way to optimize the Time Complexity , but let's say there are 100 Million Users , then the Space Complexity just
  for counting this is Huge!!

* ##### _This is where HyperLogLog comes in_

### How does it work ?

- It takes the UserID's and hashes it , and gives a binary number.
- (i.e) UserId ==> f(UserID) ==> 1...101000 (This is where the randomness comes in).
- We call the number of continuous 0's at the end a run.
- 10101010000 is a run of 4. It has 4 continuous 0's at the end / LSB.
- Based on the run of the number that was produced after hashing we get the result.
- A longer run means , the algorithm has been running for a longer time.

* We take the maximum run of all (say x), then the final result is 2^x.

#### But how?

- Consider the analogy of flipping coins to get x number of heads in a row. If i get 5 heads in a row it means i have been flipping coins for let's say
  an hour or so. But if i get 20 then it means i have been flipping them for weeks.
- Now compare that coin flipping to the trailing 0's.

* (i.e) The probabilty of getting x continuous 0's at the end
* 1-zero 1110 --> (1/2) chances
* 2-zero 1100 --> (1/2 x 1/2) chances
* ...
* x-zeroes 11000..00 (1/2 x 1/2 x ..... x 1/2) chances
* (i.e) (1/2^x) chances.

#### But what if the random results produced by the hashing function produces a run of 20 for the first UserID , then won't it result in inaccuracy ?

- That's why we use scorecards, They are nothing but doing the above process let's say 4 times (for 4 scorecards) and storing the results in scorecards
- To which scorecard the result to go to is determined by the MSB's.
- Then we take the Harmonic Mean of them all.
- We can control the precision by varying the number of scorecards used.

#### Distributed Systems

- Another simple way is to constantly maintain a seperate table that keeps the UserID whenever the users is active ( adds it to the table when the
  connection is made) and remove it when the connection is closed.
- But do you see the problem here? What if my server is not only one node (i.e) there are multiple servers a user can connect to , one from laptop
  and another from phone could get connected to different server.
- That's why hyperloglog is used.
- The results can be calculated in a distributed manner and can be merged together.

#### Why is it called hyperLOGLOG ?

- The maximum UserID that could be represented by a number is 2 power 64 (2^64).
- This maximum number could at max have a run of 64.
- this can be represented by 7 bits.
- (i.e) 2^64 users , a maximum of 64 runs possible , can be stored in 7 bits.
- log(2^64) = 64 ==> log (64) ==> 7.
- log(log(2^64)) == 7. _Therefore hyperLOGLOG_

### Resources

- [YouTube Video by Breaking Tap](https://www.youtube.com/watch?v=lJYufx0bfpw)

* [YouTube Video by Gaurav Sen](https://www.youtube.com/watch?v=eV1haPUt0NU)

- [Youtube Video by Victo Sancehs](https://www.youtube.com/watch?v=2PlrMCiUN_s)
