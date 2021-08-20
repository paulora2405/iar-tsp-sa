# iar-tsp-sa

## Dependencies

- `cmake >= 3.3`
- `gcc >= 9`
- `c++ == 17`

## Configure, Build and Execute

To build and configure do:

- `$ mkdir build && cd build`
- `$ cmake ..`
- `$ make`
- `$ cd ..`

To execute, it's sugested to create a symlink to the executable on the project's root dir, for that, do:

- `$ ln -s build/src/TSP-SA.out TSP-SA.out`

Then, to execute, do:

- `$ ./TSP-SA.out`