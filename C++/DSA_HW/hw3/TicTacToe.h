#ifndef _TIC_TAC_TOE_H
#define _TIC_TAC_TOE_H

// Switch alpha-beta pruning on or off
#define AB_PRUNE 1

#include <iostream>
#include <cstdint>

// Represents a tic-tac-toe game state including the history,
// i.e. a node in the game tree.
class TicTacToe {
public:
    typedef int_fast8_t smallint;
    static const smallint MAX = 1, MIN = -1, ZERO = 0,
                          INF = 64, N_POS = 9;

    // For statistical purpose
    static int win_counter[],
               lose_counter[],
               draw_counter,
               leaf_counter,
               node_counter;

    // Construct the root node and its descendants (i.e. the complete game tree)
    TicTacToe();

    // Destroy the (sub)tree recursively
    ~TicTacToe();

    // It is MAX's or MIN's turn.
    // For empty board, turn is MAX.
    const smallint turn;

    // The latest move (0 ~ 8) that led to the current state
    // (meaningless for root node)
    const smallint move;

    // Depth of the node in the tree (0 ~ 9)
    const smallint depth;

    // Current MAX's payoff
    // (1) X wins
    //     MAX * (10 - depth)
    // (2) O wins
    //     MIN * (10 - depth)
    // (3) Draw
    //     ZERO
    smallint v;

    smallint alpha, beta;

    // game condition in this state
    // The stone at each board position is MAX, MIN, or ZERO.
    smallint s[N_POS];

    // The previous TicTacToe state (parent node)
    // For the empty board (root node), parent is nullptr
    const TicTacToe *parent;

    // Array containing pointers to the child nodes, indexed by the move (0 ~ 8).
    // nullptr indicates a nonexistent (invalid) child node.
    TicTacToe *children[N_POS] = {};

    TicTacToe *get_child(smallint move);

    // Check if the last player has just won the game
    bool is_win() const;

    // Perform minimax search while constructing child nodes
    // This is called during construction if necessary.
    void search();

private:
    // Construct a non-root node and its descendants,
    // given its parent node and the move (0 ~ 8) from the parent state to the current state
    TicTacToe(const TicTacToe *parent, smallint move, smallint alpha, smallint beta);
};

// Print the current TicTacToe board to ostream
std::ostream &operator<<(std::ostream &out, const TicTacToe &ttt);

#endif

