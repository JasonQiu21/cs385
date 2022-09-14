/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Jason Qiu
 * Date        : September 21, 2022
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    cout << endl << "Number of primes found: " << num_primes_ << endl;
    cout << "Primes up to " << limit_ << ':' << endl;
    const int max_prime_width = num_digits(max_prime_), 
        primes_per_row = 80 / (max_prime_width + 1);
    int column = 0;
    for(int i=0; i<=limit_; i++){
        if(is_prime_[i]){
            // Set width only if we have multiple rows
            if(num_primes_ > primes_per_row){
                cout << setw(max_prime_width);
            }
            cout << i;
            // Start new row
            column++;
            if(column >= primes_per_row){
                cout << endl;
                column = 0;
            } else {
                // Don't print space if last character in row or last character in general
                if(i != max_prime_){cout << ' ';}
            }
        }
    }
    cout<<endl;
}

int PrimesSieve::count_num_primes() const {
    int count = 0;
    for(int i=0; i<=limit_; i++){
        if(is_prime_[i]){
            count++;
        }
    }
    return count;
}

void PrimesSieve::sieve() {
    // Set all values of is_prime_ to true
    fill(is_prime_, is_prime_+limit_+1, true);
    // 1 and 0 are not prime.
    is_prime_[0] = false;
    is_prime_[1] = false;
    // Main alg.
    for(int i=2; i<=sqrt(limit_); i++){
        if(is_prime_[i]){
            for(int j = pow(i, 2); j <= limit_; j += i){
                is_prime_[j] = false;
            }
        }
    }
    // Set prime count
    num_primes_ = count_num_primes();
    // Set max prime
    for(int i = limit_; i>=0; i--){
        if(is_prime_[i]){
            max_prime_ = i;
            break;
        }
    }
}

int PrimesSieve::num_digits(int num) {
    int count = 0;
    while(num >= 1){
        count++;
        num = num/10;
    }
    return count;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve ps(limit);
    ps.display_primes();
    return 0;
}
