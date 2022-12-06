/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Jason Qiu and Jackey Yang
 * Version     : 1.0
 * Date        : 05 Dec 2022
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

void delete_array(size_t** distance_matrix, int vertex_count){
    for (int i = 0; i < vertex_count; i++){
        delete [] distance_matrix[i];
    }
    delete [] distance_matrix;
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
    size_t** distance_matrix;
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

        distance_matrix = new size_t*[vertex_count];
        for (int i = 0; i < vertex_count; i++){
            distance_matrix[i] = new size_t[vertex_count];
        }

        size_t pos;
        size_t distance;
        while (getline(input_file, line)) {
            vector<string> words;
            while((pos = line.find(" ")) != (size_t) -1){ // While we still have a space in the line
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
                distance_matrix[(int)words[0][0] - 'A'][(int)words[1][0] - 'A'] = distance;
                }
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



    return 0;
}