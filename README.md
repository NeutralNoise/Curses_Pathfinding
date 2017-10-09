# Curses_Pathfinding
A* Path finding using ncurses to display to terminal.

# Compiling
Currently only compiles on linux based systems.

Download and compile bakefile.
http://bakefile.org

Run bakefile on bake.bkl.

This will generate a makefile called GNUmakefile.

You also need to have ncurses5 libs installed.

To compile with debuging:
make config=Debug

# Known bugs
Actors seems to ingore the cost of moving to a tile that another Actor has died on.

# Usage
Hit Enter to tick the actors.
