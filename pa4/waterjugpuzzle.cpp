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
#include <stack>

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

State* pour(State start, State caps, char from, char to){
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
    State* s = new State(start.a, start.b, start.c, "fail");
    if(pourCapacity <= 0 || pourAmount <= 0){
        return s;
    }
    int difference = min(pourAmount, pourCapacity);

    switch(from) {
        case 'a':
            s->a = pourAmount - difference;
            break;
        case 'b':
            s->b = pourAmount - difference;
            break;
        case 'c':
            s->c = pourAmount - difference;
            break;
    }

    switch(to) {
        case 'a':
            s->a = start.a + difference;
            break;
        case 'b':
            s->b = start.b + difference;
            break;
        case 'c':
            s->c = start.c + difference;
            break;
    }

    ostringstream oss;
    oss << "Pour " << difference << " gallons from " << (char)(from - 32) << " to " << (char)(to - 32) << ".";
    s->directions = oss.str();
    return s;

}

vector<State*> waterjug(int* cap, int* goal){
    queue<State*> q;
    vector<State*> states; // Vector of states to be deleted later on in main
    bool** explored = new bool*[cap[0] + 1];
    for(int i = 0; i < cap[0] + 1; i++){
        explored[i] = new bool[cap[1] + 1];
        fill(explored[i], explored[i] + cap[1] + 1, false);
    }
    explored[0][0] = true;
    char pours[6][2] = {{'c', 'a'}, {'b', 'a'}, {'c', 'b'}, {'a', 'b'}, {'b', 'c'}, {'a', 'c'}}; // Array of pours to check (in this order)

    // Reference STates
    State caps(cap[0], cap[1], cap[2], "Capacities");
    State g(goal[0], goal[1], goal[2], "Goal state.");

    // Initial state
    State* s = new State(0, 0, cap[2], "Initial state.");
    State* next;

    // Initialize main BFS loop
    q.push(s);
    states.push_back(s);
    while (!(q.empty())){
        s = q.front();
        // cout << "bfs" << s->to_string() << endl;
        for(int i = 0; i < 6; i++){
            next = pour(*s, caps, pours[i][0], pours[i][1]);
            // cout << next->to_string() << " " << next->directions << endl;
            if(s->directions != "fail" && !(explored[next->a][next->b])){ // If valid and non-visisted state: set parent, add to queue; if goal state, return
                next->parent = s;
                states.push_back(next);
                if(next->a == g.a && next->b == g.b && next->c == g.c){
                    for(int i = 0; i < cap[0] + 1; i++){
                        delete[] explored[i];
                    }
                    delete[] explored;
                    return states;
                }
                q.push(next);
                explored[next->a][next->b] = true;
            } else { // If invalid or already visited, delete state immediately
                delete next;
            }
        }
        q.pop();

    }
    for(int i = 0; i < cap[0] + 1; i++){
        delete[] explored[i];
    }
    delete[] explored;
    return states;
}

void printStates(State* s){
    stack<State*> toPrint;

    while(s->parent != nullptr){
        toPrint.push(s);
        s = s->parent;
    }
    while(!(toPrint.empty())){
        s = toPrint.top();
        cout << s->directions << " " << s->to_string() << endl;
        toPrint.pop();
    }
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
            if(tmp < 1){
                if (i%3 == 1){
                    letter = "A";
                } else if(i%3 == 2){
                    letter = "B";
                } else {
                    letter = "C";
                }

                cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << letter << "." << endl;
                return -1;
            }
            cap[i-1] = tmp;
        } else {
            if(tmp < 0){
                if (i%3 == 1){
                    letter = "A";
                } else if(i%3 == 2){
                    letter = "B";
                } else {
                    letter = "C";
                }
                cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << letter << "." << endl;
                return -1;
            }
            goal[i-4] = tmp;
        }
    }
    int sum_goals = 0;
    for(int i = 0; i < 3; i++){
        sum_goals+= goal[i];
        if(cap[i] < goal[i]){
            if (i == 0){
                letter = "A";
            } else if(i == 1){
                letter = "B";
            } else {
                letter = "C";
            }
            cerr << "Error: Goal cannot exceed capacity of jug " << letter << "." << endl;
            return -1;
        }
    }
    if(sum_goals != cap[2]){
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return -1;
    }
    vector<State*> states = waterjug(cap, goal);
    State* result = states.back();
    if(result->a == goal[0] && result->b == goal[1] && result->c == goal[2]){
        printStates(result);
    } else{
        cout << "No solution." << endl;
    }
    for(auto i: states){
        delete i;
    }
    return 0;
}
