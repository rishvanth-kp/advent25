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

static void
get_largest_digit(string &number, size_t start_pos, size_t end_pos, 
  size_t &max_digit, size_t &max_digit_pos) {
 
  max_digit = 0;
  max_digit_pos = start_pos;
  for (size_t i = start_pos; i < end_pos; ++i) {
    size_t current_digit = number[i] - '0';
    if (current_digit > max_digit) {
      max_digit = current_digit;
      max_digit_pos = i;
    }
  }
}

int
main (int argc, char* argv[]) {
  try {
    if (argc != 2) {
      throw std::runtime_error("day3 [infile]");
    }

    // read the input
    std::ifstream in(argv[1]);
    if (!in) {
      throw std::runtime_error("Connot open file");
    }
 
 
    size_t max_joltage = 0;
    string digit;
    while (getline(in, digit)) {
      // cout << digit;
      size_t max_digit_1;
      size_t max_digit_1_pos;
      size_t max_digit_2;
      size_t max_digit_2_pos;

      get_largest_digit(digit, 0, digit.length() - 1, 
        max_digit_1, max_digit_1_pos);
      // cout << "\t" << max_digit_1 << "\t" << max_digit_1_pos;
      get_largest_digit(digit, max_digit_1_pos + 1, digit.length(), 
        max_digit_2, max_digit_2_pos);
      // cout << "\t" << max_digit_2 << "\t" << max_digit_2_pos;
     
      size_t joltage = (max_digit_1 * 10) + max_digit_2;
      // cout << "\t" << joltage;
      
      max_joltage += joltage;    
  
      // cout << endl;
       
    }

    in.close();

    cout << "Maxmimum joltage: " << max_joltage << endl; 
  }
  catch (const std::exception &e) {
    cerr << "ERROR: " << e.what() << endl;
    return EXIT_FAILURE;    
  }
  return EXIT_SUCCESS;
}
