/*******************************************************************************
 * Name        : fastmult.cpp
 * Author      : Jason Qiu
 * Version     : 1.9
 * Date        : 10 Nov 2022
 * Description : Karatsuba Algorithm
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
 
#include <endian.h>
#include <ios>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

int usage(string x){
    cerr << "Usage: " << x << " <integer m> <integer n>" << endl;
    return -1;
}

string add(string a, string b){
    // Returns a + b
    while(a.length() < b.length())
        a.insert(0, "0");
    while(b.length() < a.length())
        b.insert(0, "0");
    string res = "\0";
    char carry = 0, res_digit, sum_digits;
    for(int i = a.length() - 1; i >= 0; i--){
        sum_digits = (a[i]-48) + (b[i]-48) + carry;
        if(sum_digits > 9){
            carry = 1;
            res_digit = sum_digits + 38;
        } else {
            carry = 0;
            res_digit = sum_digits + 48;
        }
        res.insert(res.begin(), res_digit);
    }
    if(carry != 0){
        res.insert(res.begin(), '1');
    }
    return res;
}

string subtract(string a, string b){
    // Returns a - b
    string res = "\0";
    while(a.length() < b.length())
        a.insert(0, "0");
    while(b.length() < a.length())
        b.insert(0, "0");

    char carry = 0, sub_digit, res_digit;
    for(int i = a.length()-1; i >= 0; i--){
        sub_digit = a[i] - b[i] - carry;
        if(sub_digit < 0){
            carry = 1;
            res_digit = sub_digit + 58;
        } else {
            carry = 0;
            res_digit = sub_digit + 48;
        }
        res.insert(res.begin(), res_digit);
    }
    return res;
}

string multiply(string a, string b){
    // Returna a * b;
    // cout << a << ", " << b << endl;
    while(a.length() < b.length())
        a.insert(0, "0");
    while(b.length() < a.length())
        b.insert(0, "0");
    while((a.length() & (a.length()-1)) != 0){
        a.insert(0, "0");
        b.insert(0, "0");
    }
    string res = "\0";
    if(a.length() == 1 || b.length() == 1){
        res.insert(0, to_string((a[0]-48) * (b[0]-48)));
        return res;
    }
    string front_a, front_b, back_a, back_b, c0, c1, c2;
    front_a = a.substr(0, a.length()/2);
    back_a = a.substr(a.length()/2, a.length()/2);
    front_b = b.substr(0, b.length()/2);
    back_b = b.substr(b.length()/2, b.length()/2);
    c0 = multiply(back_a, back_b);
    c2 = multiply(front_a, front_b);
    c1 = subtract(subtract(multiply(add(front_a, back_a), add(front_b, back_b)), c0), c2);
    // cout << c0 << " " << c1 << " " << c2 << endl;
    for(unsigned i = 0; i < front_a.length(); i++){
        c2.append("0");
        c2.append("0");
        c1.append("0");
    }
    // cout << "c0: " << c0 << " ";
    // cout << "c1: " << c1 << " ";
    // cout << "c2: " << c2 << endl;
    // cout << a << " * " << b << " = " <<add(add(c2, c1), c0) << endl;
    return add(add(c2, c1), c0);
}
int main(int argc, char* argv[]) {
    if(argc != 3) return usage(argv[0]);
    string a = argv[1], b = argv[2];
    for(char i:a)
        if(i < 48 || i > 57) return usage(argv[0]);
    for(char i:b)
        if(i < 48 || i > 57) return usage(argv[0]);
    while(a.length() < b.length())
        a.insert(0, "0");
    while(b.length() < a.length())
        b.insert(0, "0");
    string result = multiply(a, b);
    while(result[0] == '0'){
        result = result.substr(1);
    }
    cout << result << endl;
    // cout << add(a, b) << endl;
    // cout << subtract(a, b) << endl;
    return 0;
}