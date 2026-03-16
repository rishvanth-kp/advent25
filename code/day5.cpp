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
#include <map>

using std::map;
using std::pair;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

int
main (int argc, char* argv[]) {
  try {
    if (argc != 2) {
      throw std::runtime_error("day 5 [infile]");
    }


    // open the input file
    std::ifstream in(argv[1]);
    if (!in) {
      throw std::runtime_error("Cannot open file");
    }

    // read the fresh stock
    // Storing the first element in a binary search tree.
    // with each node containing the last element.
    map<size_t, size_t> fresh;
 
    string line;
    // read until the first empty line
    while (getline(in, line) && line.length()) {
      cout << line << endl;
      // parse the start and end ids
      size_t pos = line.find('-');
      // cout << pos << "\t";
      size_t start = std::stoi(line.substr(0, pos));
      size_t end = std::stoi(line.substr(pos + 1)); 
      // cout << start << "\t" << end << endl;

      // need to check if the new pair is contained within 
      // an already existing pair. If it is, do not add a
      // new element, just extend the existing one. 
      // This needs to be done to prevent an error when a 
      // new pair is fully contained in a old pair.      
 
      auto it = fresh.insert(pair<size_t, size_t>(start, end));
      // if the first already exists, change the end
      // if it is greater than the current value
      if (it.second == false) {
        if (it.first->second < end) {
          it.first->second = end;
        }
      }

    }

    cout << "foo" << endl;
    // get the list of available ingredients
    while (getline(in, line)) {
      cout << line << endl;
    }

    // close the file   
    in.close();

  }
  catch (const std::exception &e) {
    cerr << "ERROR: " << e.what() << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
