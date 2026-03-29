/*
* Copyright (C) 2026 Rishvanth Prabakar
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
      throw std::runtime_error("day6 [infile]");
    }
 
    // open the input file
    std::ifstream in(argv[1]);
    if (!in) {
      throw std::runtime_error("Cannot open file");
    }

    // read the last new line
    size_t pos = 2;
    // find the last newline
    while (in.peek() != '\n') {
      in.seekg(-pos, in.end);
      // char c = in.peek();
      // cout << pos << " " << c << endl;
      ++pos;
    }

    // read the last line
    in.get();
    string line;
    getline(in, line);
    // cout << line << endl;

    // parse the last line
    vector<size_t> op;
    for(auto it = line.begin(); it != line.end(); ++it) {
      if (*it == '*') {
        op.push_back(1);
      }
      else if (*it == '+') {
        op.push_back(0);
      }
    }
   
    /*
    cout << op.size() << endl;
    for (auto it = op.begin(); it != op.end(); ++it) {
      cout << *it << " ";
    } 
    cout << endl;
    */     

    vector<size_t> result = op;

    // go back to the start of the file
    in.seekg(0, in.beg);
    while(getline(in, line)) {
      // add a tailing space to avoid corner cases later
      line += ' ';

      // cout << line << endl;
      string num;
      vector<size_t> values;
      for (auto it = line.begin(); it != line.end(); ++it) {
        if (*it != ' ') {
          num += *it;
        }
        else if (num.length()) {
          if (num[0] != '*' && num[0] != '+') {
            values.push_back(std::stoi(num));
          }
          num.clear();
        }
      }

      /*
      cout << values.size() << endl;
      for (auto it = values.begin(); it != values.end(); ++it) {
        cout << *it << " ";
      } 
      cout << endl;
      */      

      if (values.size() == op.size()) {
        for (size_t i = 0; i < op.size(); ++i) {
          if (op[i]) {
            result[i] *= values[i];
          }
          else {
            result[i] += values[i];
          }
        }
      } 

    }

    // close the input file
    in.close();
    
    size_t result_sum = 0;
    for (auto it = result.begin(); it != result.end(); ++it) {
      // cout << *it << " ";
      result_sum += *it; 
    }
    // cout << endl;
    cout << "sum of problems: " << result_sum << endl;
  }
  catch (const std::exception &e) {
    cerr << "ERROR: " << e.what() << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
