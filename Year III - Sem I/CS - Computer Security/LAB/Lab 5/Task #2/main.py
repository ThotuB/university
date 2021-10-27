from math import ceil
from decimal import Decimal, getcontext, localcontext

def bigint_sqrt(n):
    x = n
    y = (x + 1) // 2
    while y < x:
        x = y
        y = (x + n // x) // 2
    return x

def product_sum_roots(s, p):
    delta = s ** 2 - 4 * p
    sqrt_delta = bigint_sqrt(delta)

    print(f'{delta = }')
    print(f'{sqrt_delta = }')

    x1 = (s + sqrt_delta) // 2
    x2 = (s - sqrt_delta) // 2

    return x1, x2


if __name__ == '__main__':
    n = 5076313634899413540120536350051034312987619378778911504647420938544746517711031490115528420427319479274407389058253897498557110913160302801741874277608327
    e = 3
    d = 3384209089932942360080357566700689541991746252519274336431613959029831011807259226655786125050887727921274719751986104162037800807641522348207376583379547

    k = ceil((d * e - 1) / n)
    print(f'{k = }')

    coef_sum = (k * (n + 1) + 1 - d * e) // k
    coef_prod = n

    print(f'{coef_sum = }')
    print(f'{coef_prod = }')

    x1, x2 = product_sum_roots(coef_sum, coef_prod)

    print(f'\n{x1 = }\n{x2 = }')


