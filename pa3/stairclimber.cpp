/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Jason Qiu
 * Date        : 07 October 2022
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    vector<vector<int>> ways;
    vector<vector<int>> result;
    vector<int> v;
    int s;
    if(num_stairs <= 0){
        ways.push_back(v);
        return ways;
    } // Base case; return [[]]
    for(int i = 1; i<4; i++){
        if(num_stairs >= i){// Only add to the result if we can make the step
            result = get_ways(num_stairs - i);
            s = result.size();
            for(int j = 0; j < s; j++){
                v.clear();
                v.reserve(result[j].size() + 1);
                v.insert(v.begin(), i);
                v.insert(v.end(), result[j].begin(), result[j].end());
                ways.push_back(v);
            }
        }
    }
    return ways;

}

// From sieve.cpp (pa1)
int num_digits(int num) {
    int count = 0;
    while(num >= 1){
        count++;
        num = num/10;
    }
    return count;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    int max = ways.size();
    int s;
    // Get number of steps, becasue we're not given that in function call
    int width = num_digits(max);
    for(int i = 0; i < max; i++){
        cout << setw(width) << i+1 << ". [" << setw(0);
        s = ways[i].size();
        for(int j = 0; j < s; j++){
            if(j+1 == s){
                cout << ways[i][j] << "]" << endl;
            } else {
                cout << ways[i][j] << ", ";
            }
        }
    }
}

int main(int argc, char * const argv[]) {
    if(argc != 2){
        cerr << "Usage: ./stairclimber <number of stairs>" << endl;
        return -1;
    }
    //  Convert input into usable int
    string input = argv[1];
    int num_stairs;
    istringstream iss(input);

    // Check for error.
    if ( !(iss >> num_stairs) ) {
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return -1;
    }
    if (num_stairs < 1){
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return -1;
    }
    // Print message (don't use plurals if only 1 stair)
    vector<vector<int>> ways = get_ways(num_stairs);
    cout << ways.size() << " way";
    if(num_stairs != 1){cout << "s";}
    cout <<" to climb " << num_stairs << " stair";
    if(num_stairs != 1){cout << "s";}
    cout << "." << endl;

    // Print ways
    display_ways(ways);
}
