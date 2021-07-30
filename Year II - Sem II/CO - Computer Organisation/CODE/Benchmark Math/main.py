reference = 0

def Performance(x, perf = [1, 2, 3, 4, 5, 6]):
    return perf[x]


def SPECRatio(x):
    return Performance(x) / Performance(reference)


if __name__ == '__main__':
    