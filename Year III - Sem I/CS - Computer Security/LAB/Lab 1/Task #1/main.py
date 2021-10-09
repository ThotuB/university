'''
    Python Implementation
    * C's crypt() function is slow, unlike Python's hashlib.sha512()
'''
from hashlib import sha512

def check_password(salt: str, password: str, hash: str):
    return sha512(salt.encode() + password.encode()).hexdigest() == hash

def search_password(salt: str, hash: str):
    password = ""
    found_password = False

    def generate_passwords(max_len: int, sgn_flag: bool):
        nonlocal found_password, password

        if found_password:
            return

        length = len(password)
        if length == max_len:
            if check_password(salt, password, hash):
                found_password = True
                print(f'Password: {password}')
                print(f'Hash: {sha512(salt.encode() + password.encode()).hexdigest()}')
            return

        
        alphanum_list = ['a', 'b', 'c', '1', '2']
        sign_list = ['!', '@', '#']

        if not sgn_flag:
            for c in alphanum_list:
                password += c

                generate_passwords(max_len, False)

                password = password[:-1]

        for c in sign_list:
            password += c

            generate_passwords(max_len, True)

            password = password[:-1]

    for i in range(8):
        print(f'Trying length: {i}')
        generate_passwords(i, False)
        

if __name__ == '__main__':
    salt = "SvT3dVpN"
    hash = "ed613876dd4637c160163d64561ef73699f5cc6cd9769c24c39083496f2a7e35e74fca390fbb3dac2ce6d6a1684cdde579dbd714f770875c0ca5af19813e66a6"

    search_password(salt, hash)