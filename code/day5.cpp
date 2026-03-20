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
    // start with a whole range of 0
    fresh.insert(pair<size_t, size_t>(0, 0));
 
    string line;
    // read until the first empty line
    while (getline(in, line) && line.length()) {
      // cout << line << endl;
      // parse the start and end ids
      size_t pos = line.find('-');
      // cout << pos << "\t";
      size_t start = std::stol(line.substr(0, pos));
      size_t end = std::stol(line.substr(pos + 1)); 
      // cout << start << "\t" << end << endl;

      // need to check if the new pair is contained within 
      // an already existing pair. If it is, do not add a
      // new element, just extend the existing one. 
      // This needs to be done to prevent an error when a 
      // new pair is fully contained in a old pair.

      
      auto s_it = fresh.upper_bound(start);
      auto e_it = fresh.upper_bound(end);
      --s_it;
      --e_it;
      // both are pointing to the same element
      if (s_it == e_it) {
        // outider of existing elements
        if (!s_it->second && !e_it->second) {
          // fresh.insert(pair<size_t, size_t>(start, 1));
          fresh[start] = 1;
          fresh.insert(pair<size_t, size_t>(end + 1, 0));
          // fresh[end + 1] = 0;
        }
        // else contained inside an existing elements 
        // there is nothing to be done
      }
      // 
      else {
        map<size_t, size_t>::iterator erase_s_it, erase_e_it;
        if (!s_it->second && e_it->second) {
          auto it = fresh.insert(pair<size_t, size_t>(start, 1));
          fresh.erase(++it.first, ++e_it);
        }
        else if (s_it->second && !e_it->second) {
          auto it = fresh.insert(pair<size_t, size_t>(end + 1, 0));
          fresh.erase(++s_it, it.first);
        }
        else if (!s_it->second && !e_it->second) {
          auto it = fresh.insert(pair<size_t, size_t>(start, 1));
          auto jt = fresh.insert(pair<size_t, size_t>(end + 1, 0));
          fresh.erase(++it.first, jt.first);
        }
        else if (s_it->second && e_it->second) {
          fresh.erase(++s_it, ++e_it);
        }
      }
 
      /*
      auto it = fresh.insert(pair<size_t, size_t>(start, end));
      // if the first already exists, change the end
      // if it is greater than the current value
      if (it.second == false) {
        if (it.first->second < end) {
          it.first->second = end;
        }
      }
      */
    }

    /*
    cout << "All the fresh stuff" << endl;
    for(auto it = fresh.begin(); it != fresh.end(); ++it) 
      cout << it->first << " " << it->second << endl;
    cout << endl; 
    */

    // cout << "Checking for freshness" << endl;
    // get the list of available ingredients
    size_t n_fresh = 0;
    while (getline(in, line)) {
      // cout << line << endl;

      // search the fresh ingredient list
      size_t item = std::stol(line);
      auto it = fresh.upper_bound(item);
      // it points to the element larger than item, and so
      // decrement it to point to a smaller element
      --it;
      // cout << it->first << " "  << it->second << endl;
      if (it->second) {
        // cout << item << " is fresh" << endl;
        ++n_fresh;
      }
      // cout << endl;
    }

    // close the file   
    in.close();

    cout << "Number of availble fresh ingredients: " << n_fresh << endl;


    // part 2
    size_t all_fresh = 0;
    for (auto it = fresh.begin(); it != fresh.end(); ++it) {
      if (it->second) {
        auto next_it = it;
        ++next_it;
        // cout << "adding fresh: " << it->first << " " << next_it->first << endl;
        all_fresh += (next_it->first - it->first);
      }
    }    
    cout << "Number of fresh ingredients: " << all_fresh << endl;
  
  }
  catch (const std::exception &e) {
    cerr << "ERROR: " << e.what() << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
