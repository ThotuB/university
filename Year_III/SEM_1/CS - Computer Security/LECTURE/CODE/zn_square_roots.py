for n in range(20):
    squares = [0 for _ in range(n)]

    for i in range(n):
        squares[i ** 2 % n] += 1

    print(f'{n:2} - {squares}')
