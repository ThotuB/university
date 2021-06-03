def c2_to_int(nrC2):
    size = len(nrC2)
    nrInt = -nrC2[size-1] * 2**(size-1)

    for i in range(size-1):
        nrInt += nrC2[i] * 2**i

    print(nrInt)


if __name__ == "__main__":
    nr = '1011'

    nr = list(map(lambda x : bool(x=='1'), list(nr) ))[::-1]

    c2_to_int(nr)