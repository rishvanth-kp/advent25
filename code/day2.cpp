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

size_t
get_n_digits (size_t in) {
  size_t n_digits = 0;
  while (in) {
    in /= 10;
    ++n_digits;
  }
  return n_digits;
}

size_t
pow (size_t base, size_t exp) {
  size_t out = 1;
  while (exp) {
    out = out * base;
    --exp;
  }
  return out;
}

static void
split_string (const string &in, vector<string> &tokens,
              const char delim = ':') {

  tokens.clear();
  size_t start = 0;
  size_t end = in.find(delim);
  while (end != string::npos) {
    tokens.push_back(in.substr(start, end - start));
    start = ++end;
    end = in.find(delim, start);
  }
  tokens.push_back(in.substr(start));
}

int
main (int argc, char* argv[]) {
  try {
    if (argc != 2) {
      throw std::runtime_error("day2 [infile]");
    }

    // read and parse the input file
    std::ifstream in(argv[1]);
    if (!in)
      throw std::runtime_error("cannot open file");

    string line;
    getline(in, line);
    vector<string> ranges;
    split_string(line, ranges, ',');
    in.close();   
 
    size_t sum_invalid = 0;
    size_t sum_invalid_p2 = 0;

    // process each range
    for (auto it = ranges.cbegin(); it != ranges.cend(); ++it) {
      // cout << *it << endl;
      // parse the range
      vector<string> from_to;
      split_string(*it, from_to, '-');
      size_t range_from = std::stol(from_to[0]);
      size_t range_to = std::stol(from_to[1]);
      // cout << range_from << "\t" << range_to << "\t"  
      //      << (range_to - range_from + 1) << endl;


      /************************************************************************/
      // part 1
      /************************************************************************/

      // get the number of digits
      size_t n_digits = get_n_digits(range_from);
      bool is_even = !(n_digits % 2);
  
      size_t pow_n = pow(10, n_digits);
      size_t pow_n_by_2 = pow(10, n_digits / 2);

      // cout << range_from << "\t" << n_digits << "\t" 
      //      << is_even << "\t" << pow_n << "\t" << pow_n_by_2 << endl; 

      for (size_t i = range_from; i <= range_to; ++i) {
        // check if the current number of digits changed
        if (i / pow_n) {
          ++n_digits;
          is_even = !is_even;
          pow_n = pow(10, n_digits);
          pow_n_by_2 = pow(10, n_digits / 2);
          // cout << i << "\t" << n_digits << "\t" 
          //     << is_even << "\t" << pow_n << "\t" << pow_n_by_2 << endl; 
        }

        // need to process only if the number of digits is even
        if (is_even) {
          // check the the lower half of the number matches the upper half
          // get the upper half
          size_t upper_half = i / pow_n_by_2;

          // get the lower helf
          size_t lower_half = i % pow_n_by_2;

          // check if they match
          if (upper_half == lower_half) {
            // cout << "match: " << i << endl;
            sum_invalid += i;
          }
        }
 

        // part 2

        bool match_found = false;
        size_t repeat_size = 1;
        while (!match_found && (repeat_size <= (n_digits / 2))) {
          // cout << i << "\t" << repeat_size << endl;
          // need to check only if j is divisible by the number of digits
          if (!(n_digits % repeat_size)) {
         
            bool match = true;
            size_t check_digit = i;
            size_t pow_j = pow(10, repeat_size);
            size_t reminder = check_digit % pow_j;
            while (match && (check_digit >= pow_j)) {
              check_digit /= pow_j;
              if (reminder != (check_digit % pow_j)) {
                match = false;
              }
            }

            if (match) {
              match_found = true;
              sum_invalid_p2 += i;
              // cout << i << endl;
            }
  
          } 
          ++repeat_size;
        }


 
      } 


    }

    cout << "Sum of invalid IDs (part 1): " << sum_invalid << endl;
    cout << "Sum of invalid IDs (part 2): " << sum_invalid_p2 << endl;

      
  }
  catch (const std::exception &e) {
    cerr << "ERROR: " << e.what() << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
