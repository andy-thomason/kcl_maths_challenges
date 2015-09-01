
import math

# factorial long division
def long_div(value, num_digits):
  result = ""

  # "done" is a set of bits with '1' for each digit we have used
  # eg. 278 would be 2^2 + 2^7 + 2^8
  done = 0

  # loop over the digits doing long division with factorials
  for i in range(0, num_digits):
    # in python "//" means integer division and % means modulo
    fact = math.factorial(num_digits-i-1)
    rem = value // fact
    value %= fact

    # now we have a digit in "rem" but we may already have used that
    # digit before, so we need to skip used digits to get the answer.
    k = 0
    j = 0
    while True:
      if (done & (1<<k)) == 0:
        if j == rem:
          break
        j += 1
      k += 1

    # now the digit is k and we set the bit in the set.
    done |= (1<<k);
    result += str(k)
  return result

print("result=" + long_div(1000001, 10))
