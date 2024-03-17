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
Now you have committed and pushed your update, so it's available to all others in the repository.

### How to pull updates using GIT
Pulling updates is relatively simple. Simply use these two lines, and you're done.
The "fetch" part will synchronize and see if there are any changes in the repository, compared to what you have on your PC.

```
$ git fetch origin

$ git pull origin main

```

## Known issues
### G++
G++ has some compiler differences compared to some other compilers, which will result in the code not working.
Therefore it's recommended that you use something like Clang++ instead, which can run the code.
To install Clang there are a couple of things you have to do.
1) Install Clang.
```
$ sudo apt update

$ sudo apt install Clang

$ clang++ --version
```

After doing this you have to tell your compiler to use Clang instead of G++. How you do this depends on which IDE (Aka. editor) you use to code in.
For Visual Studio Code, you just need to copy the contents of [tasks.json]([URL_to_File](https://github.com/DrDarkDK/S2_Robot/blob/main/.vscode/tasks.json)https://github.com/DrDarkDK/S2_Robot/blob/main/.vscode/tasks.json) into your own file.
