def Performance(index):
    perf = [1, 2, 3, 4, 5, 6]
    return perf[index]


def SPECRatio(index, reference=0):
    return Performance(index) / Performance(reference)


if __name__ == '__main__':
    print(SPECRatio(0, 1))