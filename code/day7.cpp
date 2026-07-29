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
      throw std::runtime_error("day7 [infile]");
    }


    // read the first line
    std::ifstream in(argv[1]);
    if (!in) {
      throw std::runtime_error("Cannot open file");
    } 

    string line;
    getline(in, line);

    // intialse the beam
    vector<size_t> beam;
    for (const char& c : line) {
      if (c == 'S')
        beam.push_back(1);
      else 
        beam.push_back(0);
    }
 
    /* 
    for (const size_t i : beam) {
      cout << i << " ";
    }
    cout << endl;
    */
  
    // process the rest of the splitters.
    // the even lines do not need to be processed, but not over-optimizing
    size_t split_count = 0;
    while (getline(in, line)) {
      for (size_t i = 0; i < line.length(); ++i) {
        if (line[i] == '^') {
          if (beam[i]) {
            // split the beam
            beam[i - 1] += beam[i];
            beam[i + 1] += beam[i];
            // zero the current location
            beam[i] = 0;

            // increment the split count
            ++split_count;
          }
        }
      }

  
      /*
      for (const size_t i : beam) {
        cout << i << " ";
      }
      cout << endl;
      */

    }
    cout << "Number of splits: " << split_count << endl; 

    size_t timeline_count = 0;
    for(const size_t i : beam) {
      timeline_count += i;
    }
    
    cout << "Number of timelines: " << timeline_count << endl;

    // close the file
    in.close();

  }
  catch (const std::exception &e) {
    cerr << "ERROR: " << e.what() << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
