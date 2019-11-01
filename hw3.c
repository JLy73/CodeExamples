/* hw3.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define CHILDMAX 128

/* Globals */
int m; // rows
int n; // column
int x; // min values in dead end board solution
int max_squares;

/* Struct for all the info for each board*/
struct board_stats {
  char** the_board;
  int num_visited;
  int curr_row;
  int curr_col;
};

/* Struct for storing which moves are valid */
struct valid_moves {
  int num_moves;
  int good_moves[8];
};

/* Struct for holding all dead end boards */
struct all_boards {
  struct board_stats* current;
  struct all_boards* rest;
};

/* Struct for arguments for new threads */
struct args {
  int move;
  struct board_stats* board;
  struct all_boards* solutions;
};

/* Function frees the board */
void free_board(struct board_stats* board) {
  for (int i = 0; i < m; ++i) {
      free(board->the_board[i]);
  }
  free(board->the_board);
  free(board);
}

/* Name move_Sonny for child_Sonny */
void move_Sonny(struct board_stats* board, struct all_boards* solutions);


/* Function copies the board */
struct board_stats * copy_board(struct board_stats* board) {
  struct board_stats* new_board = calloc(1, sizeof(struct board_stats));
  new_board->num_visited = board->num_visited;
  new_board->curr_row = board->curr_row;
  new_board->curr_col = board->curr_col;
  new_board->the_board = calloc(m, sizeof(char*));
  for (int i = 0; i < m; ++i) {
    new_board->the_board[i] = calloc(n, sizeof(char));
    for (int j = 0; j < n; ++j) {
      new_board->the_board[i][j] = board->the_board[i][j];
    }
  }
  return new_board;
}


/* Function updates the board */
void update_board(struct board_stats* board, int move) {
    // Get current location
    int x = board->curr_row;
    int y = board->curr_col;

    // Find move to update
    if (move == 0) {
      board->the_board[x-1][y-2] = 'S';
      board->curr_row=x-1;
      board->curr_col=y-2;
    } else if (move == 1) {
      board->the_board[x+1][y-2] = 'S';
      board->curr_row=x+1;
      board->curr_col=y-2;
    } else if (move == 2) {
      board->the_board[x-1][y+2] = 'S';
      board->curr_row=x-1;
      board->curr_col=y+2;
    } else if (move == 3) {
      board->the_board[x+1][y+2] = 'S';
      board->curr_row=x+1;
      board->curr_col=y+2;
    } else if (move == 4) {
      board->the_board[x-2][y-1] = 'S';
      board->curr_row=x-2;
      board->curr_col=y-1;
    } else if (move == 5) {
      board->the_board[x-2][y+1] = 'S';
      board->curr_row=x-2;
      board->curr_col=y+1;
    } else if (move == 6) {
      board->the_board[x+2][y-1] = 'S';
      board->curr_row=x+2;
      board->curr_col=y-1;
    } else if (move == 7) {
      board->the_board[x+2][y+1] = 'S';
      board->curr_row=x+2;
      board->curr_col=y+1;
    }

    // Update moves
    board->num_visited++;
}


/* Function prints the board */
void print_board(struct board_stats* board) {
  printf("THREAD %ld: > ", pthread_self());
  for (int i = 0; i < m; ++i) {
      if (i != 0) {
          printf("THREAD %ld:   ", pthread_self());
      }
      for (int j = 0; j < n; ++j) {
          printf("%c", board->the_board[i][j]);
      }
      printf("\n");
  }
}

/* Function checks each of the valid spots on the board and sees if
   Sonny can move there or not */
struct valid_moves* check_moves(struct board_stats* board){
  // Setting valid moves to 0
  struct valid_moves* moves = calloc(1, sizeof(struct valid_moves));
  moves->num_moves = 0;

  // Get current location
  int x = board->curr_row;
  int y = board->curr_col;

  // Check each potential for in range or already visited
  // Check if can move up on board
  if (y-2 >= 0) {
    // Check if can move right on board
    if (x -1 >= 0) {
      // Check if spot if filled
      if (board->the_board[x-1][y-2] == '.') {
        moves->good_moves[moves->num_moves] = 0;
        moves->num_moves++;
      }
    }
    // Check if can move left on board
    if (x +1 < m) {
      // Check if spot if filled
      if (board->the_board[x+1][y-2] == '.') {
        moves->good_moves[moves->num_moves] = 1;
        moves->num_moves++;
      }
    }
  }
  // Check if can move down on board
  if (y+2 < n) {
    // Check if can move right on board
    if (x -1 >= 0) {
      // Check if spot if filled
      if (board->the_board[x-1][y+2] == '.') {
        moves->good_moves[moves->num_moves] = 2;
        moves->num_moves++;
      }
    }
    // Check if can move left on board
    if (x +1 < m) {
      // Check if spot if filled
      if (board->the_board[x+1][y+2] == '.') {
        moves->good_moves[moves->num_moves] = 3;
        moves->num_moves++;
      }
    }
  }
    // Check if can move left on board
  if (x-2 >= 0) {
    // Check if can move up on board
    if (y -1 >= 0) {
      // Check if spot if filled
      if (board->the_board[x-2][y-1] == '.') {
        moves->good_moves[moves->num_moves] = 4;
        moves->num_moves++;
      }
    }
    // Check if can move down on board
    if (y +1 < n) {
      // Check if spot if filled
      if (board->the_board[x-2][y+1] == '.') {
        moves->good_moves[moves->num_moves] = 5;
        moves->num_moves++;
      }
    }
  }
  // Check if can move right on board
  if (x+2 < m) {
    // Check if can move right on board
    if (y -1 >= 0) {
      // Check if spot if filled
      if (board->the_board[x+2][y-1] == '.') {
        moves->good_moves[moves->num_moves] = 6;
        moves->num_moves++;
      }
    }
    // Check if can move left on board
    if (y +1 < n) {
      // Check if spot if filled
      if (board->the_board[x+2][y+1] == '.') {
        moves->good_moves[moves->num_moves] = 7;
        moves->num_moves++;
      }
    }
  }

  // Return moves
  return moves;
}


/* Function updates then sends into the next move for new thread */
void * child_Sonny(void* to_child) {
  struct args * child = (struct args *) to_child;
  struct board_stats* board = child->board;
  int move = child->move;
  struct all_boards* solutions = child->solutions;
  update_board(board, move);
  move_Sonny(board, solutions);
  //free_board(board);
  free(child);
  return NULL;
}


/* Functions implements Sonny's moves until he can move no more */
void move_Sonny(struct board_stats* board, struct all_boards* solutions) {
  // Check the number of valid moves possible
  struct valid_moves* moves;
  moves = check_moves(board);

  // No moves to make, reached dead-end
  if (moves->num_moves == 0) {
    // Check to see if most moves made
    if (board->num_visited > max_squares) {
      max_squares = board->num_visited;
    }
    // Add board to solutions
    if (solutions->current == NULL) {
      // First time
      solutions->current = board;
    } else {
      while(solutions->rest != NULL) {
        solutions = solutions->rest;
      }
      struct all_boards* next = calloc(1, sizeof(struct all_boards));
      next->current = board;
      next->rest = NULL;
      solutions->rest = next;
    }

    // Print that is dead end
    printf("THREAD %ld: Dead end after move #%d\n", pthread_self(), board->num_visited);
    
    // Free moves
    free(moves);

  } else if (moves->num_moves == 1) {
    // Get move, update, and continue
    int move = moves->good_moves[0];
    update_board(board, move);
    free(moves);
    move_Sonny(board, solutions);
  } else {
    // Make new threads
    printf("THREAD %ld: %d moves possible after move #%d; creating threads...\n", pthread_self(), moves->num_moves, board->num_visited+1);
  
    //make new threads
    pthread_t tid[moves->num_moves];

    for(int i = 0; i < moves->num_moves; ++i) {
      // Get arguments
      struct args* to_child = calloc(1, sizeof(struct args));
      to_child->board = copy_board(board);
      to_child->move = moves->good_moves[i];
      to_child->solutions = solutions;

      // Make Thread
      int rc = pthread_create(&tid[i], NULL, child_Sonny, (void *) to_child);
      if (rc != 0) {
        perror("ERROR: pthread_create() failed move_Sonny()\n");
        exit(EXIT_FAILURE);
      }
    }

    // Join threads
    for (int i = 0; i < moves->num_moves; ++i) {
      int rc = pthread_join(tid[i], NULL);
      if (rc != 0) {
        perror("ERROR: pthread_join() failed in move_Sonny()\n");
        exit(EXIT_FAILURE);
      }
      printf("THREAD %ld: Thread %ld joined (returned %d)\n", pthread_self(), pthread_self(), board->num_visited);
    }

    // Free moves
    free(moves);
  }
}


/* Function executes the program */
int main ( int argc, char * argv[] ) {

  // For Submitty (buffer)
  setvbuf( stdout, NULL, _IONBF, 0 );

  // Check number of arguments and if the arguments are valid
  if (argc == 3 || argc == 4) {
      m = atoi(argv[1]);
      n = atoi(argv[2]);
      // Check if board large enough
      if (m <= 2 || n <= 2) {
          fprintf(stderr, "ERROR: Invalid argument(s)\nUSAGE: a.out <%d> <%d> [<x>]\n", m,n);
          return EXIT_FAILURE;
        }
      if (argc == 4) {
          x = atoi(argv[3]);
          if (x <= 0 || x > m*n) {
              fprintf(stderr, "ERROR: Invalid argument(s)\nUSAGE: a.out <%d> <%d> [<%d>]\n",m,n,x);
              return EXIT_FAILURE;
          }
      } else {
          x = 0;
      }
  } else {
      fprintf(stderr, "ERROR: Invalid argument(s)\nUSAGE: a.out <m> <n> [<x>]\n");
      return EXIT_FAILURE;
  }

  // Set max_squares
  max_squares = 0;

  // Make Initial Board
  struct board_stats* board0 = calloc(1, sizeof(struct board_stats));
  board0->num_visited = 1;
  board0->curr_row = 0;
  board0->curr_col = 0;
  board0->the_board = calloc(m, sizeof(char*));
  for (int i = 0; i < m; ++i) {
    board0->the_board[i] = calloc(n, sizeof(char));
    for (int j = 0; j < n; ++j) {
       board0->the_board[i][j] = '.';
    }
  }
  board0->the_board[0][0] = 'S';

  // Print solving line
  printf("THREAD %ld: Solving Sonny's knight's tour problem for a %dx%d board\n", pthread_self(), m, n);
  
  // Make possible moves
  struct all_boards* solutions = calloc(1, sizeof(struct all_boards));
  move_Sonny(board0, solutions);

  // All boards are executed, print results
  printf("THREAD %ld: Best solution found visits %d squares (out of %d)\n", pthread_self(), max_squares, m*n);
  printf("THREAD %ld: Dead end boards:\n", pthread_self());

  // Print all boards
  struct all_boards* temp  = solutions;
  while (temp->current != NULL) {
      // make sure large enough to visit
      if (temp->current->num_visited >= x) {
        print_board(temp->current);
      }
      if (temp->rest == NULL) { break; }
      temp = temp->rest;
  }

  // Free all boards
  free_board(board0);
  free(solutions);
}
