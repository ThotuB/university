def big_modexp(x, y, m):
    """
    Return x^y mod m.
    """
    result = 1
    while y > 0:
        if y & 1:
            result = (result * x) % m
        y >>= 1
        x = (x * x) % m
    return result


def big_modinv(x, m):
    """
    Return the inverse of x mod n.
    """
    t, newt = 0, 1
    r, newr = m, x

    while newr != 0:
        quotient = r // newr
        t, newt = newt, t - quotient * newt
        r, newr = newr, r - quotient * newr

    if r > 1:
        return 0

    if t < 0:
       return t + m

    return t


def big_sqrt(n):
    """
    Return the integer square root of n.
    """
    x = n
    y = (x + 1) // 2
    while y < x:
        x = y
        y = (x + n // x) // 2
    return x
    

def big_gcd(a, b):
    """
    Return the greatest common divisor of a and b.
    """
    while b != 0:
        a, b = b, a % b
    return a


class Unballanced_RSA:
    def __init__(self, p, q, e):
        self.p = p
        self.q = q
        self.e = e
        self.n = p * q
        self.phi = (p - 1) * (q - 1)
        self.d = big_modinv(e, p - 1)

    def encrypt(self, m):
        return big_modexp(m, self.e, self.n)

    def decrypt(self, c):
        return big_modexp(c, self.d, self.p)


def rsa_challenge():
    n1 = 1847699703211741474306835620200164403018549338663410171471785774910651696711161249859337684305435744585616061544571794052229717732524660960646946071249623720442022269756756687378427562389508764678440933285157496578843415088475528298186726451339863364931908084671990431874381283363502795470282653297802934916155811881049844908319545009848393775227257052578591944993870073695755688436933812779613089230392569695253261620823676490316036551371447913932347169566988069
    n2 = 25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784406918290641249515082189298559149176184502808489120072844992687392807287776735971418347270261896375014971824691165077613379859095700097330459748808428401797429100642458691817195118746121515172654632282216869987549182422433637259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133844143603833904414952634432190114657544454178424020924616515723350778707749817125772467962926386356373289912154831438167899885040445364023527381951378636564391212010397122822120720357

    # c1 = m^2 mod n1
    # c2 = m^2 mod n2
    c1 = 1720824975522517857539467309146518060382842270514896093391979291030656292239729144665403513685944626690514052214759764494443164349805757586202347941324566382604120964935386258122499988803617571634095970180011900017447474052409657500820140866171389821089899978493473235156488326073675749875367732149010528924410410906444433597348845088236450378514333879924861416351842847760894046996788495712068878608786899270756395075310915351872142911403786029148987183447449947
    c2 = 4561642280956381246774642331705575104523442518306294887033201504008906454855887855514597265790895675977553974797919773779776892655441870273897525131894871022585204433581044093255080732213955457653190810418341335699127548110113873635190699932165850542152382657518899992710162713201334532551245793969597202669219115740003607047862007490749311954754246585281919237018449235669417865766985783275606492993022230240362330772342072322881876285807865893832282346294300028016342171410187938861009812975635715641457865781951720724292241356964611155195796118428665614605770428732914664423921593531374184814778240252956844983980

    # inv_n1 = n1^-1 mod n2
    # inv_n2 = n2^-1 mod n1
    inv_n1 = big_modinv(n1, n2)
    inv_n2 = big_modinv(n2, n1)

    # m^2 = ((c1 * n2 * inv_n2) + (c2 * n1 * inv_n1)) mod n1 * n2
    m2 = ((c1 * n2 * inv_n2 ) + (c2 * n1 * inv_n1)) % (n1 * n2)
    
    # m = sqrt(m^2)
    m = big_sqrt(m2)

    return m


def unbalanced_rsa_encrypt_decrypt(message):
    rsa = Unballanced_RSA(541, 104729, 7)

    c = rsa.encrypt(message)
    m = rsa.decrypt(c)

    return c, m


def cca2(message):
    rsa = Unballanced_RSA(541, 104729, 7)

    c = rsa.encrypt(message)
    m = rsa.decrypt(c)

    p = big_gcd(message - m, rsa.n)
    q = rsa.n // p

    return p, q


if __name__ == '__main__':
    # m = rsa_challenge()

    # print('RSA CHALLENGE')
    # print(f'{m = }')

    # c, m = unbalanced_rsa(300)

    # print('UNBALLANCED RSA')
    # print(f'{c = }')
    # print(f'{m = }')

    # p, q = cca2(1000)

    # print('CCA2')
    # print(f'{p = }')
    # print(f'{q = }')

    p = 23
    q = 11
    n = p * q
    x = 8
    print(f'{n = }')
    xn = big_modexp(x, n, n)
    xpq = big_modexp(x, p + q, n)
    xp = big_modexp(x, p , n)
    xq = big_modexp(x, q, n)

    print((xp + xq )% n)