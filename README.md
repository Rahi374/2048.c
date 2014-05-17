2048.c
======

![screenshot](http://amanokami.net/img/2048-c.png)

2048 for the terminal.

### Gameplay

Same as the original, as you should know. Allowed movement is up, down, left, and right to move all the tiles in said directions.
The keys to move in those directions can either be:

- Up/Down/Left/Right
- WASD
- hjkl (Which correspond to left, down, up, right, in case you didn't know.)

'q' to quit, and 'n' to start a new game.
Press y to confirm your choice of those two, and any other key will cancel.

In the case of a Game Over, again, 'q' to quit or 'n' so start a new game.

### Requirements

- C compiler
- ncurses library (aside from the standards C libraries)

### Installation

1. Download/obtain the project however you want.
2. make

Then again, I think I left the binary in the project folder as well.
You could just run that and you wouldn't need to compile.

I'll be asking a few friends to see if I can get a compiled version for Windows and OSX.
My cross-compiler doesn't want to work.

Detailed installation instructions (for n00bs) follow:

First download (presumaby as a zip)
```shell
cd Downloads
unzip 2048.c-master.zip
cd 2048.c-master
gcc -o 2048 2048.c -lncurses || make
./2048
```

### Comments

Well, my first legitimate git project? And it's in C. That's not my first language.
Anyway, I apologize for the very messy (and probably inefficient) code, and I didn't actually bother to write contructive comments. (I was going to, but... well...)

As usual, I prefer my one-file programs, so as you can see I completely skipped a header file. (Partly because I don't know how to do header files)
I also tried out autoscan, autoheader, and autoconf, but that cluttered up my project directory and I really didn't feel like cleaning it up.

Also, I didn't actually realize that people had already remade 2048 for the terminal/console.
Anyway I never looked at any other 2048.c during development of this one. (In fact, I didn't find out about the existence of other 2048.c until after I finished the first version)

Enjoy!

### TODOs

- Save file (resume game after quitting)
- Color... maybe?
- Highscore file

### License

The MIT License (MIT)

Copyright (c) 2014 Paul Elder
