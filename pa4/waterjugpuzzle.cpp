/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Jason Qiu and Jackey Yang
 * Date        : October 22 2022
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <queue>
#include <string>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions) : 
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

// int main() {
//     State s(0, 0, 8, "Initial state.");
//     cout << s.to_string() << endl;
//     s.a += 3;
//     s.c -= 3;
//     cout << s.to_string() << endl;
//     return 0;
// }

State pour(State start, State caps, char from, char to){
    int pourAmount, pourCapacity; 
    switch(from) {
        case 'a': // a
            pourAmount = start.a;
            break;
        case 'b': // b
            pourAmount = start.b;
            break;
        case 'c': // c
            pourAmount = start.c;
            break;
    }
    switch(to) {
        // How much we can fit into to
        case 'a': // a
            pourCapacity = caps.a - start.a;
            break;
        case 'b': // b
            pourCapacity = caps.b - start.b;
            break;
        case 'c': // c
            pourCapacity = caps.c - start.c;
            break;
    }

    // Initialize return state as fail, change if we pass the fail tests
    State s(start.a, start.b, start.c, "fail");
    if(pourCapacity <= 0){
        return s;
    }
    if(pourAmount <= 0){
        return s;
    }


    switch(from) {
        case 'a':
            s.a = pourAmount - min(pourAmount, pourCapacity);
            break;
        case 'b':
            s.b = pourAmount - min(pourAmount, pourCapacity);
            break;
        case 'c':
            s.c = pourAmount - min(pourAmount, pourCapacity);
            break;
    }

    switch(to) {
        case 'a':
            s.a = start.a + min(pourAmount, pourCapacity);
            break;
        case 'b':
            s.b = start.b + min(pourAmount, pourCapacity);
            break;
        case 'c':
            s.c = start.c + min(pourAmount, pourCapacity);
            break;
    }
    // TODO: set direction
    // s.directions = "Pour from ".push_back(from) + " to ".push_back(to);
    return s;

}

State waterjug(int* cap, int* goal){
    queue<State> q;
    State caps(cap[0], cap[1], cap[2], "Capacities");
    State s(0, 0, cap[2], "Initial state.");
    State g(goal[0], goal[1], goal[2], "Goal state.");
    if(s.a == g.a && s.b == g.b && s.c == g.c){
        return s;
    }
    s = pour(s, caps, 'c', 'a');
    return s;
    
}

int main(int argc, char * const argv[]) {
    if(argc != 7){
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return -1;
    }

    string input, type, letter;
    int tmp;
    int cap[3];
    int goal[3];
    
    for(int i = 1; i < argc; i++){
        input = argv[i];
        istringstream iss(input);
        if ( !(iss >> tmp) ) {
            type = (i < 4) ? "capacity '" : "goal '";
            if (i%3 == 1){
                letter = "A";
            } else if(i%3 == 2){
                letter = "B";
            } else {
                letter = "C";
            }

            cerr << "Error: Invalid " << type << argv[i] << "' for jug " << letter << "." << endl;
        return -1;
        }
        if(i < 4){
            cap[i-1] = tmp;
        } else {
            goal[i-4] = tmp;
        }
    }
    for(int i = 0; i < 3; i++){
        if(cap[i] < goal[i]){
            if (i == 0){
                letter = "A";
            } else if(i == 1){
                letter = "B";
            } else {
                letter = "C";
            }
            cerr << "Error: Goal cannot exceed capacity for jug " << letter << "." << endl;
            return -1;
        }
    }
    cout << waterjug(cap, goal).to_string() << endl;
    return 0;
}
