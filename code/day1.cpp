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

      dial += dist;
      dial %= 100;
      // cout << dial << "\t";
      dial = (dial >= 0) ? dial : 100 + dial;
 
      // cout << dial << endl;

      // cout << endl;

      if (!dial) {
        ++zero_count;
      }

    }
    in.close();
   
    cout << zero_count << endl;
  }
  catch (const std::exception &e) {
    cerr << "ERROR: " << e.what() << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
