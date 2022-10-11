class Fiestel_Network:
    def __init__(self, key, func):
        self.key = key
        self.func = func
        
    def encrypt(self, left, right, rounds):
        l, r = left, right
        for _ in range(rounds):
            l, r = r, l ^ self.func(r, self.key)
        return l, r


if __name__ == '__main__':
    fiestel = Fiestel_Network(0xff, lambda x, k: x & k)
    
    left, right = 0xf0, 0x0f
    l, r = fiestel.encrypt(left, right, 1)
    print(f'L = {l:02X} R = {r:02X}')