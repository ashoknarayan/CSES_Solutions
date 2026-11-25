import sys

def sieve(n):
    """
    Generates a boolean list 'is_prime' of size n+1.
    is_prime[i] is True if i is prime, False otherwise.
    Uses the Sieve of Eratosthenes algorithm.
    """
    is_prime = [True] * (n + 1)
    is_prime[0] = is_prime[1] = False
    for i in range(2, int(n**0.5) + 1):
        if is_prime[i]:
            for multiple in range(i * i, n + 1, i):
                is_prime[multiple] = False
    return is_prime

def find_permutations(n, is_prime):
    """
    Finds two permutations a and b of size n such that a[i] + b[i] is prime.
    """
    # The 'f' dictionary will store the pairing: f[i] = j means i is paired with j.
    f = {}
    
    # Separate numbers into odd and even sets.
    all_nums = set(range(1, n + 1))
    odds = {i for i in all_nums if i % 2 != 0}
    evens = {i for i in all_nums if i % 2 == 0}

    # The main strategy is to pair odd numbers with even numbers.
    # For odd n, the number 1 is a special case and is paired with itself.
    if n % 2 != 0:
        f[1] = 1
        odds.remove(1)

    # We try to match remaining odds with evens.
    # A robust strategy is to find a large prime 'p' and try to pair 'i' with 'p-i'.
    # Find the smallest prime p > n
    p = n + 1
    while True:
        if p < len(is_prime) and is_prime[p]:
            break
        p += 1

    # Greedily match odds with evens using the prime p
    unmatched_evens = set(evens)
    for o in sorted(list(odds), reverse=True):
        e = p - o
        if e in unmatched_evens:
            f[o] = e
            f[e] = o
            unmatched_evens.remove(e)

    # The numbers that couldn't be paired using 'p' are leftover.
    # We match them greedily. This works because the number of leftovers is small.
    unmatched_odds = {o for o in odds if o not in f}

    for o in sorted(list(unmatched_odds), reverse=True):
        # Find an even partner for the odd number 'o'
        found_match = False
        for e in sorted(list(unmatched_evens), reverse=True):
            if is_prime[o + e]:
                f[o] = e
                f[e] = o
                unmatched_evens.remove(e)
                found_match = True
                break
        if not found_match:
            # This case should ideally not be reached given the problem constraints
            # and the properties of prime numbers.
            return None, None

    # Construct the permutations from the final pairing dictionary 'f'
    a = list(range(1, n + 1))
    b = [f[i] for i in a]
    
    return a, b

def main():
    """
    Main function to read input, run the solver, and print the output.
    """
    try:
        n_str = sys.stdin.readline()
        if not n_str: return
        n = int(n_str)
        
        # Pre-compute primes up to 2*n for efficiency
        is_prime = sieve(2 * n)
        
        a, b = find_permutations(n, is_prime)
        
        if a:
            print(*a)
            print(*b)
        else:
            print("IMPOSSIBLE")

    except (IOError, ValueError):
        # Handle potential empty input or invalid format
        pass

if __name__ == "__main__":
    main()
