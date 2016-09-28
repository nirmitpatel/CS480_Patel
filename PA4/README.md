#PA4: Model Loading
In this assignment, I have created a box in blender and created an obj file which is included in src folder. I have created a function called load_obj which opens and file, looks for v and f and put them in vertex or stores as unsigned int. The function is called in Object constructor.

I had to hard code the file path for obj file and vertex and fragment shader files because of some issues but it will definitely be fixed first thing before the next assignment is due. 

When the object is shown on the screen, it looks weird. I couldn't figure out the reason for it. File is being read correctly as I have tested it several different times in both load_obj function and Object constructor. 

I have attemted to do EXTRA CREDIT by giving it color. However the object is, it still has some color in it. 

I tried dragon.obj file but it gives me segfault and I am assuming it is becaise of the memory problem. 

To compile, follow the same steps described below.

#PA3: Adding Moon
In PA3, moon was added which orbits around the planet cube. 

I have updated keyboard functions in engine.cpp so that now the planet stops orbiting when pressed DELETE and moon spins reverse when TAB is pressed. When TAB is pressed and moon spin direction is reversed it almost looks like the moon is not orbitting around the planet, it actually is. The reasion it looks that way is because planet and moon is spinnig in different direction that's why they are cancelling each other out to normal eyes. 

I have added a new model matrix for moon which uses model matrix to get updated value of planet and orbit arounds it. Everything else is the same as described in previous PA. 

DELETE -> stops orbit 

TAB -> reverse moon orbit

To compile, follow the same steps described below.

#PA2: Implementing Keyboard and Mosue Interactions
PA2 takes SPACEBAR, RIGHT ALT, and RIGHT CTRL keys to pause, reverse rotation and stop rotation and continue spin respectively. 

I have updated Keyboard function in engine.cpp so that now we pass int keystroke, bool toggle, bool unpause, and bool orbit. The function checks if the keyboard input is SPACEBAR then it will set unpause to false and return 1 as keystroke, if RIGHT ALT then set toggle to false and return 2 as keystroke and if RIGHT ALT then sets orbit to false and returns 3 as keystroke. Also, I included mouse left to toggle and right to orbit as described above. 

Also, I updates the parametrs of Update function so now it also takes keystoke and mouseclick as integers. In object.cpp file, I am checking for the numbers for keystroke and mouseclicks and making object do different things. 

Everything is else is the same as PA1.

SPACE -> pause/unpause

RIGHT ALT or LEFT CLICK -> reverse/unreverse 

RIGHT CTRL or RIGHT CLICK -> stop/start rotation while orbit is still continuing

To compile, follow the same steps described below.

# PA1: Spinning Cube

PA1 will spin the cube in circles, both to the axis and orbit. There are some changes made to src/sharder.cpp file where I moved the shader code into two separate glsl files called vertexShader.glsl and fragmentShader.glsl. I put those files in PA1/shaders folder.

The file names are hard coded which has the path to it. However, according to where the person who is cloning puts it, the modification might be required to the path.

I have already included the command in cmakefile as described below so cmake should work just fine so please follow the build instructions and then use cmake and/or make to run the program as defined below.

# Dependencies, Building, and Running

## Dependency Instructions
For both of the operating systems to run this project installation of these three programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), and [SDL2](https://wiki.libsdl.org/Tutorials).

This project uses OpenGL 3.3. Some computers, such as virtual machines in the ECC, can not run this version. In in order to run OpenGL 2.7 follow the instructions at [Using OpenGL 2.7](https://github.com/HPC-Vis/computer-graphics/wiki/Using-OpenGL-2.7)

### Ubuntu/Linux
```bash
sudo apt-get install libglew-dev libglm-dev libsdl2-dev
```

### Mac OSX
Installation of brew is suggested to easily install the libs. Ensure that the latest version of the Developer Tools is installed.
```bash
brew install glew glm sdl2
```

## Building and Running
To build this project there are two options. One is to use CMake which makes including new libraries easier, and handles new files added automatically to the src and include directory. CMake is a small new learning curve but makes things easier in the future.
The second option is to use the provided Makefile which is used as usual.

Running the make in a separate directory will allow easy cleanup of the build data, and an easy way to prevent unnecessary data to be added to the git repository.  

### CMake Instructions
The building of the project is done using CMake, installation with apt-get or brew may be necessary. Later use with CMake and Shader files will be require the copy of a directory where those files are stored (ex. shaders). To do this in the ```add_custom_target``` function place 
```cmake
COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/shaders/ ${CMAKE_CURRENT_BINARY_DIR}/shaders
```

```bash
mkdir build
cd build
cmake ..
make
./Tutorial
```

### Makefile Instructions 
The makefile works as expected and must be updated with new files added in.

```bash
mkdir build
cd build
cp ../makefile .
make
./Tutorial
```

## Ubuntu.cse.unr.edu
OpenGL 3.3 will run on the [ubuntu.cse.unr.edu](https://ubuntu.cse.unr.edu/) website. To do so follow the build instructions, but when running the Tutorial executable use this line to execute.
```bash
/usr/NX/scripts/vgl/vglrun ./Tutorial
```
