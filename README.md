# AI for TicTacToe :game_die:

## Level 1
- AI puts it`s marks randomly.
- If AI see positions similar to these, it stops player from winning:

| X | _ | _ |   | X | _ | _ |   | X | _ | _ |   | X | _ | _ |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| **X** | _ | _ |   | _ | **X** | _ |   | _ | _ | _ |   | _ | _ | _ |
| _ | _ | _ |   | _ | _ | _ |   | **X** | _ | _ |   | _ | _ | **X** |


## Level 2
- + At start AI tries to put his first mark at center of field
- + AI puts it`s next mark near his last mark.
- + AI now realize, when he need to put last mark to win, and puts it
- AI stops player from winning, if see positions discribed to Level 1

## Game mode
Includes input handling, game tick, winning check.