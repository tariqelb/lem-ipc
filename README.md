# lem-ipc
The goal of the project is to make two processes communicate and interact.

# System V IPC:
System V IPC is a set of inter-process communication mechanisms (shared memory, semaphores, and message queues) that allow unrelated processes to exchange data through kernel-managed objects.

# Shared memory
Shared memory is a memory shared between two or more processes. However, why do we need to share memory or some other means of communication?
To reiterate, each process has its own address space, if any process wants to communicate with some information from its own address space to other processes, then it is only possible with IPC (inter process communication) techniques. As we are already aware, communication can be between related or unrelated processes.
Usually, inter-related process communication is performed using Pipes or Named Pipes. Unrelated processes (say one process running in one terminal and another process in another terminal) communication can be performed using Named Pipes or through popular IPC techniques of Shared Memory and Message Queues.
We have seen the IPC techniques of Pipes and Named pipes and now it is time to know the remaining IPC techniques viz., Shared Memory, Message Queues, Semaphores, Signals, and Memory Mapping.
In this chapter, we will know all about shared memory.

source : https://iies.in/blog/understanding-shared-memory-in-linux-ipc/

# Message queue
In a multitasking Linux environment, multiple processes often need to exchange data and coordinate their actions. While shared memory offers fast access, it can become complex when synchronization is required, especially with frequent read/write operations or when only selective processes need to communicate. This is where System V Message Queues come into play—a structured and reliable form of Interprocess Communication (IPC).

Message queues allow processes to send and receive messages in a FIFO (First-In, First-Out) manner, ensuring orderly and isolated data transfer without the need for shared memory space. They support multiple message types, enabling targeted communication between specific processes. Ideal for applications dealing with small, discrete data packets, message queues simplify process interaction with built-in message categorization and queue control.

source : https://iies.in/blog/exploring-system-v-message-queues-in-linux/

# Semaphore
A semaphore is a synchronization mechanism that controls access to a shared resource by allowing only a limited number of processes or threads to enter a critical section at the same time.


# The game
  The game is a 2D board when players (process) from diffent team attack each other by surrending player from two sides to kill him and last team remain in the board win.
  [0][0][7][7][0][0]
  [0][0][5][0][0][0]
  [0][0][0][0][3][0]
  [0][0][0][0][2][0]
  [0][0][0][0][7][0]


  ## Rules
    -  Players access the board from sides (Board exist in Shared memory)
    -  Game start after at less two player from team N exist and 1 player from team m
    -  Player after get into board scan it and chose a target team to attack
    -  Players exchange between them two type of messages (message queue) 
        -  type 0 where just x and y position of attacked enemy and that enemy no surrouned from any side from any there player
        -  type 4 where an enemy already surrended from one side and other team member should attack the opposide side
    -  In subject rules , player considered as surrounded and died if two player from the same team surround him like ex in player 5
    -  The rules i work with (set RANDOM define to 0 in lemipc.h to play with that rule) player consider died/surouneded if 
        -  two player from any other team surround him from two sides either (top and bottom) or (left and right) like player two

  ## Game logic
    -  Player first check if there is a best move or best position to do for surround an enemy before check message queue or scan the board to announce an attack
    -  Best move is a move where you can surround an enemy by one move
    -  Best position is where player do a move that make him closer to surround an enemy
    -  Best move/position act when an enemy is already surrounded from one side
    -  When a player surround an enemy from one side its announce an attack type 4 for other team member to move
    -  Player do not move if surround player from one side and announce a message, wait till other team member surround enemy from otherside
    -  With a team member suround enemy from one side other player move even if they maybe surround enemy (player 1 from my team surround enemy other do not try to surround other enemy and block in its position)
    -  Every player when get Semaphore check the board if a player died, if yes , they just stop till the surrounded player leave the board
    -  Player check after get Semaphore (access) if he died/ surrouned from two opposide side from other team, in this case just leave the board
    -  Player after check that there is no best move/position to do , check message queue or calculate new attack, them go close to enemy selected (The one close to center)
    -  If player block from two side (top and right) and can not go closer to player exist in top right of his position , then use find path resuresion to go the positon
    -  Find path try to find path to a position player want to go to , with minimum steps
    -  Find path do not use last position to not go back to the some position mutiple time
    
  ## Some explaination of best move and best position:

I think the game is about go closer, and handle 8 side of a player , make the best move if an enemy prisent in one of your sides,
othersiwe just go closer to selected enemy team and find path to position if player block

[0][0][P][0]
[0][0][E][0]
[0][0][0][0]
[0][0][p][0]
[0][0][0][0]

in this case make best move to top

[0][P][0][0]
[P][E][0][0]
[0][0][p][0]
[0][0][0][0]
[0][0][0][0]

in this case make second best move to left or top


[0][P][0][0]
[0][E][p][0]
[0][0][0][0]
[0][0][0][0]
[0][0][0][0]


in this case move to best position bottom


[0][0][0][0]
[0][0][E][0]
[0][0][p][0]
[0][0][0][0]
[0][0][0][0]

in this case just stay in your position and announce an attack


[0][0][0][0].
[0][E][P][0].
[0][0][p][0].
[0][0][0][0].
[0][0][0][0].

in this case player move left

### set up
  ```make ; make clean```
  
  ```./lemipc 1```
  
  ```./lemipc 2```
  
  ```./lemipc 1```
  
  ```.....other players ```
