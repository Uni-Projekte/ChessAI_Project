# ChessAI_Project

This project is a Chess AI developed as part of a university course. It provides an efficient and powerful way of representing the state of a chess board in computer memory.

## Building the Project

### Terminal

To build the project, follow these steps:

1. Open a terminal and navigate to the root directory of the project.
2. Run the following command to generate the build files:

```bash
cmake -B cmake-build-debug
```
3. Once the build files have been generated, run the following command to build the project:
```bash
cmake --build cmake-build-debug
```

4. After the build is complete, you can find the executable files in the `cmake-build-debug/{sub-project-name}/Debug/` directory. If the executable is directly in the `src` directory, you can omit the `{sub-project-name}` part of the path.

That's it! You should now have successfully built the Chess AI project. If you encounter any issues, please double-check that you have followed the above steps correctly and that your system meets the project's dependencies.

### CLion

If the project is not already configured, left-click on the root `CMakeLists.txt` and press "Load CMake Project". The project should be loaded and can be executed.

### Visual Studio

To open the project in Visual Studio, build the project in the terminal first, then open the project in `cmake-build-debug/ChessAI_Project.sln`.


## Working on the project

If you want to implement a new feature or fix a bug, please create a new branch based on the development. To do this, run the following command:


```bash
git chechkout -b {branch-name} development
```
Once you have finished implementing your changes, you can merge your branch with the development branch. However, please ensure that you have thoroughly tested your changes, written appropriate tests, and documented your code before merging your branch.
 