from euler_totient import phi

n = 221
e = 5

ds = [77, 66, 55, 5]

for d in ds:
    inv = e * d % phi(n)
    # if inv == 1:
    #     print(d)
    #     break
    print(f'{d} - {inv}')