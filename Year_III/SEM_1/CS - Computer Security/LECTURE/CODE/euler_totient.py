def phi(n):
    prime_numbers = [
        2, 3, 5, 7,  11,  13,  17,  19,  23,  29,  31,  37,  41,  43,  47,  53,  59,  61,  67,  71,  73,  79,  83,  89,  97
    ]

    prime_factors = []
    for prime_num in prime_numbers:
        if n % prime_num == 0:
            prime_factors.append(prime_num)

    print(prime_factors)

    phi = n
    for factor in prime_factors:
        phi *= (factor - 1) / factor
        
    return int(phi)


if __name__ == "__main__":
    n = 221

    print(phi(n))