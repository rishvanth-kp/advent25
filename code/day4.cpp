/*
* Copyright (C) 2025 Rishvanth Prabakar
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

int
main (int argc, char* argv[]) {
  try {
    if (argc != 2) {
      throw std::runtime_error("day4 [infile]");
    }  
 
    // read the input
    std::ifstream in(argv[1]);
    if (!in) {
      throw std::runtime_error("Cannot open file");
    }

    // read the matrix
    string line;
    vector<vector<char>> stock;
    while (getline(in, line)) {
      stock.push_back(vector<char>{});
      // cout << line << endl;
      for (size_t i = 0; i < line.length(); ++i) {
        stock.back().push_back(line[i]);
      }
    }

    in.close();

    size_t rolls = 0;
    constexpr int window = 1;
    constexpr size_t max_adj = 4;
    for (size_t i = 0; i < stock.size(); ++i) {
      for (size_t j = 0; j < stock[i].size(); ++j) {
        // cout << i << "\t" << j;
        // cout << stock[i][j] << "\t";

        size_t adj_count = 0;
        bool has_paper = false;
        // need to check only if there is a roll
        
        if (stock[i][j] == '@') {
          has_paper = true;
          for (int k = -window; k <= window; ++k){
            for (int l = -window; l <= window; ++l) {
              if ((i + k >= 0) & (i + k < stock.size()) &
                  (j + l >= 0) & (j + l < stock[i].size()) &
                  (k || l)) {
                // cout << "\t\t" << k << "\t" << l; 
                if (stock[i + k][j + l] == '@') {
                  ++adj_count;
                }
              } 
            }
          }
        }
        // cout << "\t" << has_paper << "\t" << adj_count;
        if (has_paper && (adj_count < max_adj)) {
          ++rolls;
        }
        // cout << endl;
      }
      // cout << endl;
    }
    
    cout << "Total rolls to move: " << rolls << endl;
    

  } 
  catch (const std::exception &e) {
    cerr << "ERROR: " << e.what() << endl;
    return EXIT_FAILURE;
  } 
  return EXIT_SUCCESS;
}
