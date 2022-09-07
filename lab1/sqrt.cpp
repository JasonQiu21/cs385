/*******************************************************************************
 * Filename: sqrt.cpp
 * Author  : Jason Qiu
 * Version : 1.0
 * Date    : September 14, 2022
 * Description: Function for square root for doubles using Newton's Method.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <ios>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
using namespace std;

double sqrt(double num, double epsilon=1e-7){
    if(num < 0){return numeric_limits<double>::quiet_NaN();}
    else if(num == 0 || num == 1){return num;}
    else{
        double last_guess = 1.0;
        double next_guess = (last_guess + num/last_guess) / 2;
        while(abs(next_guess - last_guess) > epsilon){
            last_guess = next_guess;
            next_guess = (last_guess + num/last_guess) / 2;
        }
        return next_guess;
    }
}

int main(int argc, char* argv[]) {
    double value, epsilon;
    epsilon = -1;
    istringstream iss;
    if(argc != 3 && argc != 2){
        cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
        return -1;
    }
    iss.str(argv[1]);
    if(!(iss >> value)){
        cerr << "Error: Value argument must be a double." << endl;
        return -1;
    }
    iss.clear();
    if(argc == 3){
        iss.str(argv[2]);
        if(!(iss >> epsilon)){
            cerr << "Error: Epsilon argument must be a positive double." << endl;
            return -1;
        } else if(epsilon <= 0){
            cerr << "Error: Epsilon argument must be a positive double." << endl;
            return -1;
        }
    }
    cout << fixed << setprecision(8);
    cout << ((epsilon > 0) ? sqrt(value, epsilon) : sqrt(value)) << endl;
    return 0;
}