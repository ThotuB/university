#include <iostream>
#include <set>
#include <crypt.h>

using namespace std;
    
#define MAX_LEN 10

// tom:$6$SvT3dVpN$lwb3GViLl0J0ntNk5BAWe2WtkbjSBMXtSkDCtZUkVhVPiz5X37WflWL4k3ZUusdoyh7IOUlSXE1jUHxIrg29p.:16471:0:99999:7:::

bool check_password(string password, string salt, string hash){
    string hash_password = crypt(password.c_str(), salt.c_str());
    return (hash_password == hash);
}

// Permutations with Repetition
void generate_passwords_1(string password, string salt, string hash, int max_len, bool sign_flag, bool *found_flag){
    if ( *found_flag ) return; // return after first found password

    int len = password.length();
    if ( len >= max_len ){ // check if password is long enough
        if ( check_password(password, salt, hash) ){ // check if password is correct
            cout << "Password: " << password << endl;
            cout << "Salt: " << salt << endl;
            cout << "Hash: " << hash << endl;

            (*found_flag) = true;
        }
        return; // if not correct, return
    }

    char alphanum[] = {'a', 'b', 'c', '1', '2'};
    char signs[] = {'!', '@', '#'};

    if ( !sign_flag ){ // if no sign flag, then also check alphanumeric characters
        for (char c : alphanum){
            password.push_back(c);
            generate_passwords_1(password, salt, hash, max_len, false, found_flag);
            password.pop_back();
        }
    }
    for (char c : signs){ // check sign characters
        password.push_back(c);
        generate_passwords_1(password, salt, hash, max_len, true, found_flag);
        password.pop_back();
    }
}

void exhaustive_search_1(string salt, string hash){
    string password = "";
    int len = 1;
    bool sign_flag = false;
    bool found_flag = false;

    while ( len <= MAX_LEN && !found_flag ){
        cout << "Trying length: " << len << endl;
        generate_passwords_1(password, salt, hash, len, sign_flag, &found_flag);
        len++;
    }
}

// Permutations 
void generate_passwords_2(string password, string salt, string hash, set<char> alphanums, set<char> signs, int max_len, bool sign_flag, bool *found_flag){
    if ( *found_flag ) return; // return after first found password

    int len = password.length();
    if ( len >= max_len ){ // check if password is long enough
        if ( check_password(password, salt, hash) ){ // check if password is correct
            cout << "Password: " << password << endl;
            cout << "Salt: " << salt << endl;
            cout << "Hash: " << hash << endl;

            (*found_flag) = true;
        }
        return; // if not correct, return
    }
    
    set<char> new_alphanums = alphanums;
    set<char> new_signs = signs;

    if ( !sign_flag ){ // if no sign flag, then also check alphanumeric characters
        for (char c : alphanums){
            password.push_back(c);
            new_alphanums.erase(c); // remove the character from the set

            generate_passwords_2(password, salt, hash, new_alphanums, signs, max_len, false, found_flag);

            new_alphanums.insert(c); // add the character back to the set
            password.pop_back();
        }
    }
    for (char c : signs){ // check sign characters
        password.push_back(c);
        new_signs.erase(c); // remove the character from the set

        generate_passwords_2(password, salt, hash, alphanums, new_signs, max_len, true, found_flag);

        new_signs.insert(c); // add the character back to the set
        password.pop_back();
    }
}

void exhaustive_search_2(string salt, string hash){
    string password = "";
    set<char> alphanums = {'a', 'b', 'c', '1', '2'};
    set<char> signs = {'!', '@', '#'};
    int len = 1;
    bool sign_flag = false;
    bool found_flag = false;

    while ( len <= MAX_LEN && !found_flag ){
        cout << "Trying length: " << len << endl;
        generate_passwords_2(password, salt, hash, alphanums, signs, len, sign_flag, &found_flag);
        len++;
    }
}

int main() {
    string salt = "$6$SvT3dVpN$";
    string hash = "$6$SvT3dVpN$lwb3GViLl0J0ntNk5BAWe2WtkbjSBMXtSkDCtZUkVhVPiz5X37WflWL4k3ZUusdoyh7IOUlSXE1jUHxIrg29p.";

    exhaustive_search_1(salt, hash);

    //! Found Password: a1cb2@#!

    return 0;
}