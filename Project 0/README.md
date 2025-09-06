## HyperLogLog ( A prababilitic Data Structure )

- TLDR : Used to count the number of distinct elements in a large dataset

### Why HyperLogLog ?

Let's say my website is getting traffic from various devices (laptops,phones,etc.,) from all over the world. Now i want to find the number of users
logged in (or) connected to my servers. I know their UserID's are unique. But how do i find the number of unique user ID's ?

###### Compare

- Checking every UserId with every other UserId takes a lot of Time and Space.

###### Sort / Set

- Sorting them by UserId's and counting the unique vals alone (or) using a set takes O(nlogn) Time Complexity.

###### Hashing

- Hashing the UserID's is a good way to optimize the Time Complexity , but let's say there are 100 Million Users , then the Space Complexity just
  for counting this is Huge!!

* ###### _This is where HyperLogLog comes in_

### How does it work ?

- It takes the UserID's and hashes it , and gives a binary number.
- (i.e) UserId ==> f(UserID) ==> 1...101000.
- We call the number of continuous 0's at the end a run.
- 10101010000 is a run of 4. It has 4 continuous 0's at the end / LSB.
- Based on the run of the number that was produced after hashing we get the result.
- A longer run means , the algorithm has been running for a longer time.
- ###### But how?
- Consider the analogy of flipping coins to get x number of heads in a row. If i get 5 heads in a row it means i have been flipping coins for let's say
  an hour or so. But if i get 20 then it means i have been flipping them for weeks.
- Now compare that coin flipping to the trailing 0's.
- ###### But what if the random results produced by the hashing function produces 20 for the first UserID , then won't it result in inaccuracy ?

* That's why we use scorecards, They are nothing but doing the above process let's say 4 times (for 4 scorecards) and storing the results in scorecards
* To which scorecard the result to go to is determined by the MSB's.
* Then we take the Harmonic Mean of them all.
* We can control the precision by varying the number of scorecards used.

### Resources

- [YouTube Video by Breaking Tap](https://www.youtube.com/watch?v=lJYufx0bfpw)

* [YouTube Video by Gaurav Sen](https://www.youtube.com/watch?v=eV1haPUt0NU)
