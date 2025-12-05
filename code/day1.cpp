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

using std::cout;
using std::cerr;
using std::endl;
using std::string;

int
main (int argc, char *argv[]) {
  try {
    if (argc != 2) {
      throw std::runtime_error("day1 [infile]");
    }
 

    // 
    int dial = 50;
    size_t zero_count = 0;
    size_t zero_cross = 0;

    // read the input
    std::ifstream in(argv[1]);
    string line;
    while (getline(in, line)) {
      // cout << line << endl;
      // parse the direction and the distance
      char dir = line[0];
      int dist;
      if (dir == 'L') {
        dist = -1 * std::stoi(line.substr(1));
      }
      else if (dir == 'R') {
        dist = std::stoi(line.substr(1));
      }
      // cout << dir << "\t" << dist << endl;

      // cout << dial << "\t";
  
      bool zero_before = (dial == 0);

      dial += dist;
      // cout << dial << "\t";

      int div_after = dial / 100;
      int mod_after = dial % 100;
      
      // cout << div_after << "\t";
      // cout << mod_after << "\t";

      if (div_after > 0) {
        zero_cross += div_after;
      }
      else if (div_after < 0) {
        zero_cross += (-div_after);
      }
      // correct for crossing a zero from the strictly positive side 
      if (!zero_before & (dial <= 0)) {
        ++zero_cross;
      }

/*
      if (dial == 0) {
       ++zero_cross;
      }
      else if (div_after > 0) {
        zero_cross += (div_after);
      }
      else if (dial < 0) {
        zero_cross += (-div_after + 1); 
      }
*/      
      // cout << zero_cross << "\t";

      dial = mod_after;
      
      dial = (dial >= 0) ? dial : 100 + dial;
      // cout << dial << endl;
      // cout << endl;

      if (!dial) {
        ++zero_count;
      }

    }
    in.close();
   
    cout << "Number of zero pointing: " << zero_count << endl;
    cout << "Number of zero crossing: " << zero_cross << endl;
  }
  catch (const std::exception &e) {
    cerr << "ERROR: " << e.what() << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
