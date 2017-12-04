# AI for TicTacToe :game_die:

### AI_TicTacToe        - Console demonstration of AI 
### Oxygine_TicTacToe   - 2D TicTacToe game build in Oxygine Game Engine
###  :warning: In order to play --> Run *TicTacToe.exe* in *Oxygine_TicTacToe/data/* :warning:

###  :warning: If you whant to build project by yourself, 
### you need to have *oxygine-framework* source code :warning:

## Level 1
- AI puts it`s marks randomly.


## Level 2
- \+ At start AI tries to put his first mark at center of field
- \+ AI puts it`s next mark near his last mark.
- \+ AI now realize, when he need to put last mark to win, and puts it
- \+ If AI see positions similar to these, it stops player from winning:

| X | _ | _ |   | X | _ | _ |   | X | _ | _ |   | X | _ | _ |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| **X** | _ | _ |   | _ | **X** | _ |   | _ | _ | _ |   | _ | _ | _ |
| _ | _ | _ |   | _ | _ | _ |   | **X** | _ | _ |   | _ | _ | **X** |


## Level 3 TICTACTOE_GOD
- \+ FIRST TURN:
 At start AI tries to put his first mark at center of field, 
 if it is occupated by player, AI marks corner to force draw

| _ | _ | _ |   | _ | _ | _ | 
|---|---|---|---|---|---|---|
| _ | **X** | _ | **OR** | _ | **O** | _ |
| _ | _ | _ |   | _ | _ | **X** |

- \+SECOND TURN: 
 if we own the center cell there already can be:
 a) 2 opponent marks on the field
 b) 1 opponent marks on the field
 in b situation we dominate (have to consider b1 situation), in a situation we need to consider this two situations :

(O - AI, X - Player)

A1 SITUATION

1)
| _ | _ | _ |               | **X** | _ | _ |           | **X** | _ | **X** |
|---|---|---|            ---|---|---|---|            ---|---|---|---|
| _ | **O** | _ |  -------> | _ | **O** | _ | ------->  | _ | **O** | _ |
| _ | _ | **X** |           | **O** | _ | **X** |       | **O** | _ | **X** |

A2 SITUATION

2)
| _ | _ | _ |               | _ | _ | **O** |                | _ | _ | **O** | 
|---|---|---|            ---|---|---|---|                 ---|---|---|---|  
| _ | **O** | _ |  -------> |  **X** | **O** | _ | ------->  |  **X** | **O** | _ |
| _ | **X** | _ |           | _ | **X** | _ |                | **X** | **X** | **O** |

B1 SITUATION

1)
| _ | _ | _ |               | **X** | _ | _ |                | **X** | _ | **X** | 
|---|---|---|            ---|---|---|---|                 ---|---|---|---|  
| _ | **X** | _ |  -------> | _ | **X** | **O** | ------->  | _ | **X** | **O** |
| _ | _ | **O** |           | _ | _ | **O** |                | _ | _ | **O** |

 All this situations are considered in MakeSecondMark() function!

- Includes all functionality from level 2


## Game mode
Includes input handling, game tick, winning check.
