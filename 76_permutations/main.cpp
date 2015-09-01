

#include <iostream>
#include <fstream>
#include <chrono>

// The following problem is taken with thanks from Project Euler, where it appears as Problem 24.
// 
// A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation
// of the digits 1, 2, 3 and 4. If all of the permutations are listed numerically or alphabetically,
// we call it lexicographic order. The lexicographic permutations of 0, 1 and 2 are:
//
// 012   021   102   120   201   210
// What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?
//

void generate(std::ostream &out, char digits[], int num_digits, unsigned used, int &sequence) {
  if (num_digits == 10) {
    digits[num_digits] = 0;
    if (sequence <= 1000000) out << sequence << " " << digits << "\n";
    //if (sequence % 362880 == 1) std::cout << sequence << " " << digits << "\n";
    //if (sequence == 1000000) std::cout << digits << "\n";
    sequence++;
  } else {
    for (int i = 0; i != 10; ++i) {
      if ( !(used & (1 << i) ) ) {
        digits[num_digits] = '0' + i;
        generate(out, digits, num_digits+1, used | (1 << i), sequence);
      }
    }
  }
}

long long factorial(int n) {
  long long result = 1;
  while (n) {
    result *= n;
    --n;
  }
  return result;
}

void long_div(char digits[], int num_digits, long long value) {
  int done = 0;
  value++;
  for (int i = 0; i != num_digits; ++i) {
    long long fact = factorial(num_digits-i-1);
    long long rem = value / fact;
    value %= fact;
    long long j = 0, k = 0;
    for (; ; ++k ) {
      if (!(done & (1<<k))) {
        if (j++ == rem) break;
      }
    }
    done |= (1<<k);
    digits[i] = '0' + (char)k;
  }
}


int main() {
  char digits[10+1];
  using namespace std::chrono;
  auto start = high_resolution_clock::now();

  if (0) {
    int sequence = 1;
    auto file = std::ofstream("/tmp/1.txt");
    generate(file, digits, 0, 0u, sequence);
  } else {
    long_div(digits, 10, 1000000);
    digits[10] = 0;
    std::cout << digits << "\n";
  }

  auto end = high_resolution_clock::now();
  std::cout << duration_cast<milliseconds>(end - start).count() << "\n";
}
