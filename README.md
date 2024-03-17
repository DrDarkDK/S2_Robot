# S2_Robot

## How to compile the project
Open the project in your terminal. Make sure you have the correct directory opened.
After that write the following commands, one by one (without the $ of course).

```
$ sudo apt-get update
$ sudo apt-get install -y cmake build-essential

$ mkdir build
$ cd build
$ cmake ..
$ make

$ ./Output
```

After having done this once, the two last lines are all you will need to compile in the future.
Writing "make" will compile the code, and "./Output" will run the executable file.

## GIT
### How to push updates using GIT
First of all, you will want to make sure the right changes have been detected. This is done by writing
`$ git status`
After checking everything is okay here, you can continue.
Now, assuming you want to push all your edits, you will write the following line to tell GIT you want to stage all your files for a commit.
`$ git add -A`
Now that all edits have been staged, we can proceed to commit and finally push our changes.
```
$ git commit -m "Your commit message here."

$ git push origin main
```
Now you have commited and pushed your update, so it's available to all others in the repository.

### How to pull updates using GIT
Pulling updates is relatively simple. Simply use these two lines, and you're done.
The "fetch" part will syncronize and see if there are any changes in the repository, compared to what you have on your PC.

```
$ git fetch origin

$ git pull origin main
```

### Getting SFML graphics to work 

Install SFML to compile 
https://www.sfml-dev.org/download/sfml/2.6.1/

Compile Instructions: 

Linux GCC:

1) g++ -c main.cpp robotics.cpp 
2) g++ main.o robotics.o -lsfml-graphics -lsfml-window -lsfml-system
3) ./a.out 


CMake: 
1) mkdir build && cd build 
2) cmake .. 
Make sure that the exectuable is build/source-code/S2_Robotics. It needs to be near the Textures folder to run properly


Piece texture from: 
https://opengameart.org/content/chess-pieces-and-board-squares