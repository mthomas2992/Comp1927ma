#/bin/bash

printf "Question a\n"
./mkwords 1000000 | ./words - 85711

printf "  As seen above, The maximum chain length for 857144 words\n  with a hash table size of 85711 is 27\n\n"
printf "  The distribution appears to be approximately normal\n"

printf "  Examining the distributions of sorting the same words into hash tables of size 100000, 214283, 400000, 400837, 857144, 857137, we find that those corresponding to 214283, 400837 and 857137 are more spread, i.e. have higher numbers at higher lengths than the others, and that the others typically show a higher density of low length chains, particularly chains of length - and 1 However, as the hash table size increases towards the number of items, these differences become less significant.\n"

printf "  Below are results demonstrating this:\n\n"

./mkwords 1000000 | ./words - 100000 
printf "\n\n"
./mkwords 1000000 | ./words - 214283
printf "\n\n"
./mkwords 1000000 | ./words - 400000
printf "\n\n"
./mkwords 1000000 | ./words - 400837
printf "\n\n"
./mkwords 1000000 | ./words - 857144
printf "\n\n"
./mkwords 1000000 | ./words - 857137
printf "\n\n"

printf "Question b\n"
printf "  Yes, as seen above the prime numbers seem to result in chain distributions that resemble a normal distribution, and the max chain length for the primes, 15, 11 and 8 respectively, compared to 39, 15 and 9 respectively. Again however, this difference is less noticed for hash table slot sizes approaching the total number of items (i.e. the tests fr 857144 and 857137 hash table sizes.\n\n"

printf "Question c\n"
printf " Using trial and error on prime numbers between 500000 and 600000, seeking a prime that contains chain lengths of length 9, we find that the prim 651029, obtained from a list of prime numbers, produces the following output:\n\n"

./mkwords 1000000 | ./words - 651029
printf "\n\n  which uses more than 2/3rds of the slots, and has most chains of length 1 or 2, and has a max chain length of 9\n\n"

printf "Quesion d\n"
printf "  running words on places with a hash table size of 1048576 results in chains up to length 4479, yet with a hash table size of 1048573, results in chains of length 20. gprof profiles for 1048576 show most time spent (7.34 seconds) in ListSearch, with 2nd most time 1.87 seconds in hash. Comparing this with hash table size 1048573, we see time spent in hash tops the list with 2.34 seconds, followed by 2.02 seconds in ListSearch. From this, we conclude that the list table search function has very poor performance when the hash function is sub-optimal.\n\n"

printf "  INCLUDE THE GPROF TABLES"

printf "Question e\n"
printf "  After running ./mkwords 1000000 | ./words - N on a variety of prime numbers between 0 and 1000000, we condlucde the functions that are most costly in terms of time are by far, hash and ListSearch. Some gprof tables are shown below\n\n\n"

printf "  INCLUDE THE GPROF TABLES"

printf "Question f\n"


