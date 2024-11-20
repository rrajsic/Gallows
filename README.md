# Gallows
## Introduction
This simple C project allows user to play a game of gallows against a computer. Words are extracted from a preconfigured `randomWords.txt` file.
Scores for usernames are stored so users can come back and stack points.

I made this when I was a freshman in college.

## How to use
1. Open `Gallows.exe`
2. Type a username, if it exists you will continue your past progress
3. Follow the instructions in the console

## Admin Settings
Password for Admin settings (Press A on maim menu) is **kundak**

### Options for Admin settings:
1. Random Words Managment:
   - View list of random words
   - Sort and view words by alphabet
   - Sort and view words by word size
   - Add a word
   - Find a word
  
2. Ranking System Managment
   - View list of usernames
   - View list of forbidden usernames (These are forbidden because Windows forbis some names of files. For every new username a new file is created which keeps track of score)
   - Sort and view usernames by alphabet
   - Check out someones score
   - Add a forbidden username
   - View all users and scores (Linked list)

> For developing/debugging build project with cmake for the C++ engine (in build/) `cmake .` and `cmake --build .`

## Example of console output
### Gallows game start
![Console_game_start](https://github.com/user-attachments/assets/bf184871-44b8-418b-9683-db6cbb2028b5)
### Gallows game end (win)
![Console_game_end](https://github.com/user-attachments/assets/0e3d6912-e080-4218-8106-16bfe39debcd)


