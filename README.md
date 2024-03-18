# S2_Robot

## Table of Contents
- [How to compile the project](#how-to-compile-the-project)
- [How to use GIT](#how-to-use-git)
- [Getting SFML graphics to work](#getting-sfml-graphics-to-work )
- [Known Issues](#known-issues)

## How to compile the project
Open the project in your terminal. Make sure you have the correct directory opened.
After that write the following commands, one by one (without the $ of course).

```powershell
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

## How to use GIT
### How to push updates using GIT
First of all, you will want to make sure the right changes have been detected. This is done by writing
`$ git status`
After checking everything is okay here, you can continue.
Now, assuming you want to push all your edits, you will write the following line to tell GIT you want to stage all your files for a commit.
`$ git add -A`
Now that all edits have been staged, we can proceed to commit and finally push our changes.
```powershell
$ git commit -m "Your commit message here."

$ git push origin main
```
Now you have committed and pushed your update, so it's available to all others in the repository.

### How to pull updates using GIT
Pulling updates is relatively simple. Simply use these two lines, and you're done.
The "fetch" part will synchronize and see if there are any changes in the repository, compared to what you have on your PC.

```powershell
$ git fetch origin

$ git pull origin main
```

## Getting SFML graphics to work 

Install SFML to compile 
https://www.sfml-dev.org/download/sfml/2.6.1/

Compile Instructions: 

Linux GCC:

```powershell
$ g++ -c main.cpp robotics.cpp 
$ g++ main.o robotics.o -lsfml-graphics -lsfml-window -lsfml-system
$ ./a.out 
```


CMake: 
```powershell
$ mkdir build && cd build 
$ cmake .. 
```
Make sure that the exectuable is build/source-code/S2_Robotics. It needs to be near the Textures folder to run properly


Piece texture from: 
https://opengameart.org/content/chess-pieces-and-board-squares

# Known issues
### G++
G++ has some compiler differences compared to some other compilers, which will result in the code not working.
Therefore it's recommended that you use something like Clang++ instead, which can run the code.
To install Clang there are a couple of things you have to do.
1) Install Clang.
```powershell
$ sudo apt update

$ sudo apt install Clang

$ clang++ --version
```

After doing this you have to tell your compiler to use Clang instead of G++. How you do this depends on which IDE (Aka. editor) you use to code in.
For Visual Studio Code, you just need to copy the contents of [tasks.json]([URL_to_File](https://github.com/DrDarkDK/S2_Robot/blob/main/.vscode/tasks.json)https://github.com/DrDarkDK/S2_Robot/blob/main/.vscode/tasks.json) into your own file.



18/03/2024

Du vågner nok før jeg gør og ser det jeg har pushed, skal nok få skrevet mere forklaring til det men er kogt lige nu fordi at jeg valgte at semi starte over med en dumpster fire af den kode jeg sad og fyrede af før så valgte bare at få styr på at vi havde et bræt med brikkerne på som så ikke kan rykkes endnu, men det skal vi nok komme til. Dog er placeringen et Assets et problem siden den kører på min path til dem lige i øjeblikket, der skal gøres et eller andet så den kører fra folderen man befinder sig i og så bare kan tilgå assets ved den tidligere kommando Assets/{brik navn}. Vil bare sove så du må nyde det here værk som nok også er en semi dumpster fire. 