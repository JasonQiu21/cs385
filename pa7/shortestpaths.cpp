/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Jason Qiu
 * Version     : 1.0
 * Date        : 05 Dec 2022
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <vector>
#include <climits>

using namespace std;

long len(long num) {
    if(num == 0)
        return 1;
    int count = 0;
    while(num >= 1){
        count++;
        num = num/10;
    }
    return count;
}

/** 
 * Displays the matrix on the screen formatted as a table. 
 */ 
void display_table(long** const matrix, const string &label, int num_vertices, const bool use_letters = false) {
    long INF = LONG_MAX;
    cout << label << endl;
    long max_val = 0; 
    for (int i = 0; i < num_vertices; i++) { 
        for (int j = 0; j < num_vertices; j++) { 
        long cell = matrix[i][j]; 
        if (cell < INF && cell > max_val) {
            max_val = matrix[i][j]; 
        } 
        } 
    } 
    // cout << max_val << endl;
    int max_cell_width = use_letters ? len(max_val) : 
        len(max(static_cast<long>(num_vertices), max_val)); 
    cout << ' '; 
    for (int j = 0; j < num_vertices; j++) { 
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A'); 
    } 
    cout << endl; 
    for (int i = 0; i < num_vertices; i++) { 
        cout << static_cast<char>(i + 'A'); 
        for (int j = 0; j < num_vertices; j++) { 
        cout << " " << setw(max_cell_width); 
        if (matrix[i][j] == INF) { 
            cout << "-"; 
        } else if (use_letters) { 
            cout << static_cast<char>(matrix[i][j] + 'A'); 
        } else { 
            cout << matrix[i][j]; 
        } 
        } 
        cout << endl; 
    } 
    cout << endl; 
} 

void delete_array(long** distance_matrix, int vertex_count){
    for (int i = 0; i < vertex_count; i++){
        delete [] distance_matrix[i];
    }
    delete [] distance_matrix;
}

string gen_path_helper(long** through_matrix, long start, long end){
    string head = "";
    if(start == end){
        head.push_back('A' + start);
        return head;
    }
    if(through_matrix[start][end] != LONG_MAX){
        head = gen_path_helper(through_matrix, start, through_matrix[start][end]);
        string tail = gen_path_helper(through_matrix, through_matrix[start][end], end);
        head.append(" -> ");
        head.append(tail);
        return head;
    }
    head.push_back('A' + start);
    // head.append(" -> ");
    // head.push_back('A' + end);
    return head;
}

string gen_path(long** through_matrix, long start, long end){
    if(start != end){
        string res = gen_path_helper(through_matrix, start, end);
        res.append(" -> ");
        res.push_back('A' + end);
        return res;
    }
    return gen_path_helper(through_matrix, start, end);
}


int main(int argc, const char *argv[]) {
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    int vertex_count;
    long** distance_matrix;
    try {
        unsigned int line_number = 1;
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/

        // Get number of vertices
        getline(input_file, line);
        try{
            vertex_count = stoi(line);
            if(vertex_count > 26 || vertex_count < 1){
                cerr << "Error: Invalid number of vertices '" << line << "' on line 1." << endl;
                return -1;
            }
        } catch (std::invalid_argument const& err){
            cerr << "Error: Invalid number of vertices '" << line << "' on line 1." << endl;
            return -1;
        }
        line_number++;

        distance_matrix = new long*[vertex_count];
        for (int i = 0; i < vertex_count; i++){
            distance_matrix[i] = new long[vertex_count];
        }
        for(int i = 0; i < vertex_count; i++){
          for(int j = 0; j < vertex_count; j++){
            distance_matrix[i][j] = LONG_MAX;
          }
        }

        long pos;
        long distance;
        while (getline(input_file, line)) {
            vector<string> words;
            while((pos = line.find(" ")) != (long) -1){ // While we still have a space in the line
                words.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            words.push_back(line);
            line = "";
            if(words.size() != 3){
                for(size_t i = 0; i < words.size(); i++){
                    line.append(words[i]);
                    if(i != words.size() - 1)
                        line.append(" ");
                }
                cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "." << endl;
                delete_array(distance_matrix, vertex_count);
                return -1;
            }
            // Check starting vertex
            if(words[0].length() != 1 || (words[0][0] < 'A') || (words[0][0] > 'A' + vertex_count - 1)){
                cerr << "Error: Starting vertex '" << words[0] << "' on line " << line_number << " is not among valid values A-" << (char) ('A' + vertex_count - 1) << "." << endl;
                delete_array(distance_matrix, vertex_count);
                return -1;
            }
            // Check ending vertex
            if(words[1].length() != 1 || (words[1][0] < 'A') || (words[1][0] > 'A' + vertex_count - 1)){
                cerr << "Error: Ending vertex '" << words[1] << "' on line " << line_number << " is not among valid values A-" << (char) ('A' + vertex_count - 1) << "." << endl;
                delete_array(distance_matrix, vertex_count);
                return -1;
            }

            // Check length
            try{
                if(words[2].find("-") != (size_t) -1){
                    cerr << "Error: Invalid edge weight '" << words[2] << "' on line " << line_number << "." << endl;
                    delete_array(distance_matrix, vertex_count);
                    return -1;
                }
                distance = stoul(words[2]);
                if (distance < 1){
                    cerr << "Error: Invalid edge weight '" << words[2] << "' on line " << line_number << "." << endl;
                    delete_array(distance_matrix, vertex_count);
                    return -1;
                }
                distance_matrix[(int)words[0][0] - 'A'][(int)words[1][0] - 'A'] = distance;
            } catch (std::invalid_argument const& err){
                    cerr << "Error: Invalid edge weight '" << words[2] << "' on line " << line_number << "." << endl;
                    delete_array(distance_matrix, vertex_count);
                    return -1;
            }


            ++line_number;
        }
        // Don't forget to close the file.
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }

    for(int i = 0; i < vertex_count; i++){
        distance_matrix[i][i] = 0;
    }

    display_table(distance_matrix, "Distance matrix:", vertex_count);

    long** through_matrix = new long*[vertex_count];
        for (int i = 0; i < vertex_count; i++){
            through_matrix[i] = new long[vertex_count];
        }
        for(int i = 0; i < vertex_count; i++){
          for(int j = 0; j < vertex_count; j++){
            through_matrix[i][j] = LONG_MAX;
          }
        }
    for(int k = 0; k < vertex_count; k++){
        for(int i = 0; i < vertex_count; i++){
            for(int j = 0; j < vertex_count; j++){
                if(distance_matrix[i][k] != LONG_MAX && distance_matrix[k][j] != LONG_MAX){
                    if(distance_matrix[i][k] + distance_matrix[k][j] < distance_matrix[i][j]){
                        distance_matrix[i][j] = distance_matrix[i][k] + distance_matrix[k][j];
                        through_matrix[i][j] = k;
                    }
                }
            }
        }
    }
    display_table(distance_matrix, "Path lengths:", vertex_count);
    display_table(through_matrix, "Intermediate vertices:", vertex_count, true);
    string path;
    for(int i = 0; i < vertex_count; i++){
        for(int j = 0; j < vertex_count; j++){
            path = gen_path(through_matrix, i, j);
            cout << (char) ('A' + i) << " -> " << (char) ('A' + j) << ", distance: " << ((distance_matrix[i][j] != LONG_MAX) ? to_string(distance_matrix[i][j]) : "infinity") 
            << ", path: " << ((distance_matrix[i][j] != LONG_MAX) ? path : "none") << endl;
        }
    }

    delete_array(distance_matrix, vertex_count);
    delete_array(through_matrix, vertex_count);



    return 0;
}