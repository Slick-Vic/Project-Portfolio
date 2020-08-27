import secrets
import math

def gcd(a,b):
    while b > 0:
        a,b = b, a % b
    return a

def lcm(a,b):
        return (a*b)//gcd(a,b)

def invMod(a,m):
    a = math.fmod(a, m); 
    for x in range(1, m) : 
        if ((a * x) % m == 1) : 
            return x 
    return 1

def mul_mod(a,b,n):
    res = 0
    a = math.fmod(a,n)
  
    while (b): 
        if (b & 1): 
            res = (res + a) %n
        a = math.fmod( 2*a, n)
        b >>= 1
    return res

def pow_mod(x,y,p):
    res = 1;
    x = math.fmod(x,p);  
  
    while (y > 0):
        if (y & 1): 
            res = math.fmod(res * x,p); 
        y = y >> 1;
        x = math.fmod(x*x,p); 
    return res;

def prime(n) : 
    if (n <= 1) : 
        return False
    if (n <= 3) : 
        return True

    if (n % 2 == 0 or n % 3 == 0) : 
        return False
  
    i = 5
    while(i * i <= n) : 
        if (n % i == 0 or n % (i + 2) == 0) : 
            return False
        i = i + 6
  
    return True
            
class Paillier:
    def __init__(self):
        [self.pubKey, self.__prKey__] = self.__gen__()

    def __gen__(self):
        p = secrets.randbelow(32)
        q = secrets.randbelow(32)
        
        while (prime(p) == False) or (prime(q) == False):
            p = secrets.randbelow(32)
            q = secrets.randbelow(32)
        
        n = p*q
        
        xi = lcm(p-1,q-1)

        g = secrets.randbelow(n)
        L = (pow_mod(g,xi,n*n) - 1)//n
        Lgcd = gcd(int(L),int(n))
        while (Lgcd != 1) or (L < 1) or (gcd(g,n*n) != 1):
            g = secrets.randbelow(n)
            L = (pow_mod(g,xi,n*n) - 1)//n
            Lgcd = gcd(int(L),int(n))
        
        mu = invMod(L,n)
        pubKey = [n, g]
        prKey = [(p,q), xi]
        return pubKey, prKey

    def __L__(self, g, xi):
        return (pow_mod(g,xi,self.pubKey[0]*self.pubKey[0]) - 1)//self.pubKey[0]

    def enc(self):
        m = int(input("m (m < n): "))
        while m > self.pubKey[0]:
            m = int(input("Try again. m (m < n): "))
    
        r = secrets.randbelow(self.pubKey[0] - 1)
        while (gcd(r,self.pubKey[0]) != 1):
            r = secrets.randbelow(self.pubKey[0])

        c1 = self.pubKey[1]**m
        c2 = r**self.pubKey[0]
        return mul_mod(c1,c2,self.pubKey[0]*self.pubKey[0])

    def dec(self, c):
        L1 = self.__L__(c,self.__prKey__[1])
        L2 = self.__L__(self.pubKey[1],self.__prKey__[1])
        return mul_mod(L1, invMod(L2, self.pubKey[0]), self.pubKey[0])

    def getKey(self):
        print("Public Keys: n =", self.pubKey[0], "| g =", self.pubKey[1])

def main():
    pal = Paillier()
    pal.getKey()
    print(pal.dec(pal.enc()))

main()
