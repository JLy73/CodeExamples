#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

// Simple class to record the grid location. 
class loc {
public:
  loc(int r=0, int c=0) : row(r), col(c) {}
  int row, col;
};

bool operator== (const loc& lhs, const loc& rhs) { 
  return lhs.row == rhs.row && lhs.col == rhs.col; 
}

//  Prototype for the main search function
bool search_from_loc(loc position, const vector<string>& board, 
                    const string& word, vector<loc>& path, string direction);


// helper function to check if a position has already been used for this word
bool on_path(loc position, vector<loc> const& path) {
  for (unsigned int i=0; i<path.size(); ++i)
    if (position == path[i]) return true;
  return false;
}

// This recursive function will search for the remainder of the word
// starting from the current location.  Returns true if the remainder
// of the word is found, returns false if we reach a dead end.  If the
// word is found, the sequence of locations that trace out the word
// are stored in path.
//PATH MUST BE IN STRAIGHT LINE
bool search_from_loc(loc position, //  current position
                     const vector<string>& board,  
                     const string& word,  
                     vector<loc>& path,  //  path up to the current pos 
                     string direction)  // finds correct direction      
{

  // DOUBLE CHECKING OUR LOGIC: the letter at the current board
  // position should equal the next letter in the word
  assert (board[position.row][position.col] == word[path.size()]);

  // start by adding this location to the path
  path.push_back(position);

  // BASE CASE: if the path length matches the word length, we're done!
  if (path.size() == word.size()) return true;

  //  search all the places you can get to in one step
  //  checks to find what direction
  if (direction == "NO") {
    int count = 0;
    for (int i = position.row-1; i <= position.row+1; i++) {
      for (int j = position.col-1; j <= position.col+1; j++) {
        
        // don't walk off the board though!
        if (i < 0 || i >= int(board.size())) {count++; continue;}
        if (j < 0 || j >= int(board[0].size())) {count++; continue;}
        // don't consider locations already on our path
        if (on_path(loc(i,j),path)) {count++; continue;}

        // if this letter matches, recurse!
        if (word[path.size()] == board[i][j]) {
          if (count == 0) direction = "UL";
          if (count == 1) direction = "ML";
          if (count == 2) direction = "LL";
          if (count == 3) direction = "UM";
          if (count == 4) continue;
          if (count == 5) direction = "LM";
          if (count == 6) direction = "UR";
          if (count == 7) direction = "MR";
          if (count == 8) direction = "LR";
          
          // if we find the remaining substring, we're done!
          if (search_from_loc (loc(i,j),board,word,path, direction)) {
            return true;
          }
        }
        //moves to next spot so add to count
        count++;
      }
    }
  }

  //checks if path follows for the direction given
  //if path follows through retruns true
  //if not it will look for new direction (in double for loop above)
  if (direction == "UL") {

    for (int i = position.row-1; i < position.row; i++) {
      for (int j = position.col-1; j < position.col; j++) {

        // don't walk off the board though!
        if (i < 0 || i >= int(board.size())) continue;
        if (j < 0 || j >= int(board[0].size())) continue;
        // don't consider locations already on our path
        if (on_path(loc(i,j),path)) continue;

        if (word[path.size()] == board[i][j]) {
            // if we find the remaining substring, we're done!
            if (search_from_loc (loc(i,j),board,word,path, direction))
              return true;
          }
        }
      }
    }

  if (direction == "ML") {

    for (int i = position.row-1; i < position.row; i++) {
      int j = position.col;

        // don't walk off the board though!
        if (i < 0 || i >= int(board.size())) continue;
        if (j < 0 || j >= int(board[0].size())) continue;
        // don't consider locations already on our path
        if (on_path(loc(i,j),path)) continue;

        if (word[path.size()] == board[i][j]) {
            // if we find the remaining substring, we're done!
            if (search_from_loc (loc(i,j),board,word,path, direction))
              return true;
          }
      }
    }
  
  if (direction == "LL") {

    for (int i = position.row-1; i < position.row; i++) {
      for (int j = position.col+1; j < position.col+2; j++) {

        // don't walk off the board though!
        if (i < 0 || i >= int(board.size())) continue;
        if (j < 0 || j >= int(board[0].size())) continue;
        // don't consider locations already on our path
        if (on_path(loc(i,j),path)) continue;

        if (word[path.size()] == board[i][j]) {
            // if we find the remaining substring, we're done!
            if (search_from_loc (loc(i,j),board,word,path, direction))
              return true;
          }
        }
      }
    } 

  if (direction == "UM") {

      for (int j = position.col-1; j < position.col; j++) {
        int i = position.row;

        // don't walk off the board though!
        if (i < 0 || i >= int(board.size())) continue;
        if (j < 0 || j >= int(board[0].size())) continue;
        // don't consider locations already on our path
        if (on_path(loc(i,j),path)) continue;

        if (word[path.size()] == board[i][j]) {
            // if we find the remaining substring, we're done!
            if (search_from_loc (loc(i,j),board,word,path, direction))
              return true;
          }
        }
    }

  if (direction == "LM") {

      for (int j = position.col+1; j < position.col+2; j++) {
        int i = position.row;

        // don't walk off the board though!
        if (i < 0 || i >= int(board.size())) continue;
        if (j < 0 || j >= int(board[0].size())) continue;
        // don't consider locations already on our path
        if (on_path(loc(i,j),path)) continue;

        if (word[path.size()] == board[i][j]) {
            // if we find the remaining substring, we're done!
            if (search_from_loc (loc(i,j),board,word,path, direction))
              return true;
          }
        }
    }

  if (direction == "UR") {

    for (int i = position.row+1; i < position.row+2; i++) {
      for (int j = position.col-1; j < position.col; j++) {

        // don't walk off the board though!
        if (i < 0 || i >= int(board.size())) continue;
        if (j < 0 || j >= int(board[0].size())) continue;
        // don't consider locations already on our path
        if (on_path(loc(i,j),path)) continue;

        if (word[path.size()] == board[i][j]) {
            // if we find the remaining substring, we're done!
            if (search_from_loc (loc(i,j),board,word,path, direction))
              return true;
          }
        }
      }
    }

  if (direction == "MR") {

    for (int i = position.row+1; i < position.row+2; i++) {
      int j = position.col;

        // don't walk off the board though!
        if (i < 0 || i >= int(board.size())) continue;
        if (j < 0 || j >= int(board[0].size())) continue;
        // don't consider locations already on our path
        if (on_path(loc(i,j),path)) continue;

        if (word[path.size()] == board[i][j]) {
            // if we find the remaining substring, we're done!
            if (search_from_loc (loc(i,j),board,word,path, direction))
              return true;
          }
        }
    }

  if (direction == "LR") {

    for (int i = position.row+1; i < position.row+2; i++) {
      for (int j = position.col+1; j < position.col+2; j++) {

        // don't walk off the board though!
        if (i < 0 || i >= int(board.size())) continue;
        if (j < 0 || j >= int(board[0].size())) continue;
        // don't consider locations already on our path
        if (on_path(loc(i,j),path)) continue;

        if (word[path.size()] == board[i][j]) {
            // if we find the remaining substring, we're done!
            if (search_from_loc (loc(i,j),board,word,path, direction))
              return true;
          }
        }
      }
    }

  // At this point we know we have failed to find a path from the
  // current loc.  Remove the current loc from the path and end this
  // recursive call with a failure so that the search can move in a
  // different direction.
  path.pop_back();
  return false;
}

// This recursive function will search a spot given a specific direction
// starting from the current location.  Returns true if the word can be placed there
// and returns false if we reach a dead end.  If the
// word is found, the sequence of locations that trace out the word
// are stored in path.
bool search_for_loc(loc position, //  current position
                     const vector<string>& board, 
                     const string& word,  
                     vector<loc>& path,  //  path up to the current pos 
                     string& direction)  // finds correct direction      
{

  // DOUBLE CHECKING OUR LOGIC: the letter at the current board
  // position should equal the next letter in the word or an empty space
  string empty = "-----"; //allows to check if spot is "-"
  if (board[position.row][position.col] != word[path.size()] 
      && board[position.row][position.col] != empty[0]) {
    
    if (path.size() > 0) {
      path.pop_back();
      }
    return false;
  }
  // start by adding this location to the path
  path.push_back(position);

  // BASE CASE: if the path length matches the word length, we're done!
  if (path.size() == word.size()) {return true;}
  
  //checks if path follows or if empty spot is avaibalbe for the direction given
  //if path follows through retruns true
  //NOTE to grader: these directions work a bit differently than in search_from_loc
  if (direction == "UL") {

    for (int i = position.row-1; i < position.row; i++) {
      for (int j = position.col-1; j < position.col; j++) {

        // don't walk off the board though!
        if (i < 0 || i >= int(board.size())) continue;
        if (j < 0 || j >= int(board[0].size())) continue;
        // don't consider locations already on our path
        if (on_path(loc(i,j),path)) continue;

        if (word[path.size()] == board[i][j] || board[i][j] == empty[0]) {
          
            // if we find the remaining substring, we're done!
            if (search_for_loc (loc(i,j),board, word,path, direction))
              return true;
          }
        }
      }
    }

  if (direction == "ML") {

    for (int j = position.col-1; j < position.col; j++) {
      int i = position.row;

        // don't walk off the board though!
        if (i < 0 || i >= int(board.size())) continue;
        if (j < 0 || j >= int(board[0].size())) continue;
        // don't consider locations already on our path
        if (on_path(loc(i,j),path)) continue;

        if (word[path.size()] == board[i][j] || board[i][j] == empty[0]) {
          
            // if we find the remaining substring, we're done!
            if (search_for_loc (loc(i,j),board, word,path, direction))
              return true;
          }
      }
    }
  
  if (direction == "LL") {

    for (int i = position.row+1; i < position.row+2; i++) {
      for (int j = position.col-1; j < position.col; j++) {

        // don't walk off the board though!
        if (i < 0 || i >= int(board.size())) continue;
        if (j < 0 || j >= int(board[0].size())) continue;
        // don't consider locations already on our path
        if (on_path(loc(i,j),path)) continue;

        if (word[path.size()] == board[i][j] || board[i][j] == empty[0]) {
          
            // if we find the remaining substring, we're done!
            if (search_for_loc (loc(i,j),board, word,path, direction))
              return true;
          }
        }
      }
    } 

  if (direction == "UM") {

      for (int i = position.row-1; i < position.row; i++) {
        int j = position.col;

        // don't walk off the board though!
        if (i < 0 || i >= int(board.size())) continue;
        if (j < 0 || j >= int(board[0].size())) continue;
        // don't consider locations already on our path
        if (on_path(loc(i,j),path)) continue;

        if (word[path.size()] == board[i][j] || board[i][j] == empty[0]) {
          
            // if we find the remaining substring, we're done!
            if (search_for_loc (loc(i,j),board, word,path, direction))
              return true;
          }
        }
    }

  if (direction == "LM") {
      for (int i = position.row+1; i < position.row+2; i++) {
        int j = position.col;

        // don't walk off the board though!
        if (i < 0 || i >= int(board.size())) continue;
        if (j < 0 || j >= int(board[0].size())) continue;
        
        // don't consider locations already on our path
        if (on_path(loc(i,j),path)) continue;
        
        if (word[path.size()] == board[i][j] || board[i][j] == empty[0]) {
          
            // if we find the remaining substring, we're done!
            if (search_for_loc (loc(i,j),board, word,path, direction))
              return true;
          }
        }
    }

  if (direction == "UR") {

    for (int i = position.row-1; i < position.row; i++) {
      for (int j = position.col+1; j < position.col+2; j++) {

        // don't walk off the board though!
        if (i < 0 || i >= int(board.size())) continue;
        if (j < 0 || j >= int(board[0].size())) continue;
        // don't consider locations already on our path
        if (on_path(loc(i,j),path)) continue;

        if (word[path.size()] == board[i][j] || board[i][j] == empty[0]) {
          
            // if we find the remaining substring, we're done!
            if (search_for_loc (loc(i,j),board, word,path, direction))
              return true;
          }
        }
      }
    }

  if (direction == "MR") {

    for (int j = position.col+1; j < position.col+2; j++) {
      int i = position.row;

        // don't walk off the board though!
        if (i < 0 || i >= int(board.size())) continue;
        if (j < 0 || j >= int(board[0].size())) continue;
        
        // don't consider locations already on our path
        if (on_path(loc(i,j),path)) continue;
        
        if (word[path.size()] == board[i][j] || board[i][j] == empty[0]) {
            // if we find the remaining substring, we're done!
            if (search_for_loc (loc(i,j),board, word,path, direction))
              return true;
          }
        }
        
    }

  if (direction == "LR") {

    for (int i = position.row+1; i < position.row+2; i++) {
      for (int j = position.col+1; j < position.col+2; j++) {

        // don't walk off the board though!
        if (i < 0 || i >= int(board.size())) continue;
        if (j < 0 || j >= int(board[0].size())) continue;
        // don't consider locations already on our path
        if (on_path(loc(i,j),path)) continue;

        if (word[path.size()] == board[i][j] || board[i][j] == empty[0]) {
          
            // if we find the remaining substring, we're done!
            if (search_for_loc (loc(i,j),board, word,path, direction))
              return true;
          }
        }
      }
    }

  // At this point we know we have failed to find a path from the
  // current loc.  Remove the current loc from the path and end this
  // recursive call with a failure so that the search can move in a
  // different direction.
  path.pop_back();
  return false;
}

//function adds the given word to the grid 
//(called only if search_for_loc is true to avoid seg fault)
//starts from location and is told direction to goes in and
//adds each word letter by letter in that direction to the board
//by changing the location to change based on direction
void add_to_board(const string& direction, vector<string>& board, string word, loc position) {
  
  for (unsigned int i = 0; i < word.size(); ++i) {
      board[position.row][position.col] = word[i];
      if (direction == "UL") {
        position.row -= 1;
        position.col -= 1;
      }

      else if (direction == "ML") {
        position.col -= 1;
      }

      else if (direction == "LL") {
        position.row += 1;
        position.col -= 1;
      }

      else if (direction == "UM") {
        position.row -= 1;
      }

      else if (direction == "LM") {
        position.row += 1;
      }

      else if (direction == "UR") {
        position.row -= 1;
        position.col += 1;
      }

      else if (direction == "MR") {
        position.col += 1;   
      }

      else if (direction == "LR") {
        position.row += 1;
        position.col +=1;
      }
    }

  
}

//function checks the board for a given word
//by going to each location on the board and
//checking if the word path starts there in any direction
//if the word is on the board it returns true
//if word not on board it returns false
bool check_board(const vector<string>& board, string word) {

  for (unsigned int i = 0; i < board.size(); ++i) {
    for (unsigned int j = 0; j < board[i].size(); ++j) {
      vector<loc> path;
      if (board[i][j] == word[0]) {
        if (search_from_loc(loc(i,j), board, word, path, "NO")) {
          return true;
        }
      }
    }
  }
  return false;
}

//function checks if the board is a valid board by
//checking if all of the good words are on the board
//and by checking if all of the bad words are not on the board
//if both are true, it then checks if the board already exists
//as a valid board. If the board is a new valid board it adds it
//to boards, a vector of all valid boards
bool validate_boards(vector<string>& board, const vector<string>& good_words, 
                    const vector<string>& bad_words, vector<vector<string> >& boards) {

  int checks = 0;

  //checks all good words
  for (unsigned int i = 0; i < good_words.size(); ++i) {
    if (!check_board(board, good_words[i])) {return false;}
    if (i == good_words.size()-1) {
      checks++;
    }
  }

  //checks all bad words
  if (bad_words.size() == 0) {checks++;}
  for (unsigned int i = 0; i < bad_words.size(); ++i) {
    if (check_board(board, bad_words[i])) {return false;}
    if (i == bad_words.size()-1) {
      checks++;
    }
  }

  //checks if both conditions are met and that board is not already considered valid
  if (checks == 2) {
    for (unsigned int i = 0; i < boards.size(); ++i) {
      if (board == boards[i]) {
        return false;
      }
    }
    boards.push_back(board);
    return true;
  }
  
  return false;
}

//function makes all of the possible board combinations based on the good words by
//recursively calling itself until all the good words are used. once reaches a complete
//board it adds it to the vector of boards
void making_boards(vector<vector<string> >& all_boards, const vector<string>& good_words, 
                  vector<string> used_words, vector<string> aboard, vector<string> oboard, 
                  const vector<string>& bad_words) {

  string empty = "-----"; //allows to check if spot is "-"
  string alphabet = "abcdefghijklmnopqrstuvwxyz"; //allows to fill in blank spots
  string skip_word; //allows to see if word already been placed

  if (good_words.size() <= used_words.size()) {

    //all good words are used and no black spots left
    //adds to vector of boards (all_boards)
    //resets board to the board before the final word to keep checking
    if (!check_board(aboard, "-")) {
      all_boards.push_back(aboard);
      aboard = oboard;
      return;
    }
     
    //if blank spots remain, checks to see what is there is valid
    //if the non-complete board is valid, adds all possible letters
    //to the board recursively  
    else if (validate_boards(aboard, good_words, bad_words,all_boards)) {
      for (unsigned int i = 0; i < aboard.size(); ++i) {
        for (unsigned int j = 0; j < aboard[0].size(); ++j) {
          if (aboard[i][j] == empty[0]) {
            for (unsigned int k = 0; k < alphabet.size(); ++k) {
              aboard[i][j] = alphabet[k];
              making_boards(all_boards, good_words, used_words, aboard, oboard, bad_words);
            }
          }
        }
      }
    }

    //if board uses all good words but is deemed invalid, 
    //this will end its chain/will not add it
    else {return;}
    
  }

  
  //loop goes through all good words
  for (unsigned int i = 0; i < good_words.size(); ++i) {

    //checks to see if word has already been placed earlier
    for (unsigned int j = 0; j < used_words.size(); ++j) {
      if (good_words[i] == used_words[j]) {
        skip_word = "yes";
        break;
      }
    }
    if (skip_word == "yes") {skip_word = "no"; continue;}


    //checks if word already exists on board
    if (check_board(aboard, good_words[i])) {
      used_words.push_back(good_words[i]);
      vector<string> used_words_copy(used_words);
      return making_boards(all_boards, good_words, used_words_copy, aboard, oboard, bad_words);
    }
    
    //sets previous board to be all words on it so far
    oboard = aboard;

    //check each spot to see if valid placement of the word
    for (unsigned int k = 0; k < aboard.size(); ++k) {
      for (unsigned int j = 0; j < aboard[0].size(); ++j) {
        
        //starting direction
        string direction = "UL";

        //checks all directions
        while (true) {
          //checks if spot is a valid spot to add word
          vector<loc> path;
          if (search_for_loc(loc(k,j), aboard, good_words[i], path, direction)) {
            //since its a valid spot, it adds the word to the board
            add_to_board(direction, aboard, good_words[i], loc(k,j));
            //if first time adding this word to a board, adds to used words
            for (unsigned int l = 0; l < used_words.size(); ++l) {
              if (used_words[l] == good_words[i]) {break;}
              if (l == used_words.size()-1) {
                used_words.push_back(good_words[i]);
                }
            }
            making_boards(all_boards, good_words, used_words, aboard, oboard, bad_words);

            //makes current board equal previous board since all combinations of
            //the current good word is complete
            aboard = oboard;
          }
          
          if (direction == "UL") {direction = "UM";}
          else if (direction == "UM") {direction = "UR";}
          else if (direction == "UR") {direction = "ML";}
          else if (direction == "ML") {direction = "MR";}
          else if (direction == "MR") {direction = "LL";}
          else if (direction == "LL") {direction = "LM";}
          else if (direction == "LM") {direction = "LR";}
          else if (direction == "LR") {break;}
          
          
        }
      }
    }
      //no path is valid and so ends its attempt to become a board
      return;
  }
}

/******************************************************************************************/

int main(int argc, char const *argv[]) {
  
  //checks for right amount of arguments and proper arguments
  if (argc != 4) {
    cerr << "Usage: " << argv[0] << " grid-file\n";
    return 1;
  }

  ifstream istr(argv[1]);
  if (!istr) {
    cerr << "Couldn't open " << argv[1] << '\n';
    return 1;
  }

  string command = argv[3];
  if (command != "one_solution" && command != "all_solutions") {
    cerr << "Not a proper command " << command << "\n";
    return 1;
  }

  int rows;
  int cols;
  string next_line;
  vector<string> good_words;
  vector<string> bad_words;

  //opens file and parses information for rows, cols, good words and bad words
  ifstream guide;
  guide.open(argv[1]);

  guide >> rows;
  guide >> cols;

  while (guide >> next_line) {
    if (next_line == "+") {
      guide >> next_line;
      good_words.push_back(next_line);
    }

    else if (next_line == "-") {
      guide >> next_line;
      bad_words.push_back(next_line);
    }
    
    else {
      cerr << "Incorrect input " << next_line << "\n";
      return 1;
    }
  }

  vector<vector<string> > boards;
  vector<vector<string> > all_boards;
  vector<string> board;
  vector<string> used_words;
  
  //create boards
  //start with empty board
  vector<string> eboard;
  string one_line = "";
  for (int i = 0; i < cols; ++i) {
    for (int j = 0; j < rows; ++j) {
      one_line+="-";
    }
    eboard.push_back(one_line);
    one_line="";
  }
  
  //makes all board combinations
  making_boards(all_boards, good_words, used_words, eboard, eboard, bad_words);

  //adds empty space to bad words because this would make a board invalid
  bad_words.push_back("-");

  //check if each board is valid
  for (unsigned int i = 0; i < all_boards.size(); ++i) {
    validate_boards(all_boards[i], good_words, bad_words, boards);

    //stops checking if asked for only one solution
    if (boards.size() > 0 && command == "one_solution") {break;}
  }
  
  //prints out solution(s) into outfile
  ofstream myfile;
  myfile.open(argv[2]);

  if (boards.size() == 0) {
    myfile << "No solutions found" << endl;
    return 0;
  }

  if (command == "all_solutions") {
    myfile << boards.size() << " solutions(s)" << endl;
  }

  for (unsigned int i = 0; i < boards.size(); ++i) {
    myfile << "Board: " << endl;
    for (unsigned int j = 0; j < boards[i].size(); ++j) {
      myfile << "  " << boards[i][j] << endl;
      }
  }

  return 0;
}

