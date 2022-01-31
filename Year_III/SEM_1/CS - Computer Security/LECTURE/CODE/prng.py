class Linear_PRNG:
    def __init__(self, seed, a, b, max_value):
        self.x = seed
        self.a = a
        self.b = b
        self.n = max_value
        
    def next(self):
        self.x = (self.a * self.x + self.b) % self.n
        return self.x

class BBS_PRNG:
    def __init__(self, seed, max_value):
        self.x = seed
        self.n = max_value
        
    def next(self):
        self.x = (self.x * self.x) % self.n
        return self.x

if __name__ == '__main__':
    prng1 = Linear_PRNG(0, 4, 7, 21)
    prng2 = BBS_PRNG(2, 21)
    
    for _ in range(10):
        print(prng1.next())
    print()
    for _ in range(10):
        print(prng2.next())