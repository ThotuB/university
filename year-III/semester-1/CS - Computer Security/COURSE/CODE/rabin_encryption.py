class Rabin_Crypto:
    def __init__(self, p, q):
        self.n = p * q
        self.e = 2
        
    def encrypt(self, m):
        return pow(m, self.e, self.n)
    
    def decrypt(self, c):
        return pow(c, 1/self.e, self.n)

if __name__ == '__main__':
    rabin = Rabin_Crypto(17, 13)
    
    m = 134
    
    c = rabin.encrypt(m)
    print(c)