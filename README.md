Most of the boilerplate needed to set up a window and the raylib and imgui library should already be setup enough to be able to start writing code to develop a game.

File architecture is separated from platform specific code (window drawing, imgui/raylib setup, input handling) and game code (player movement, physics, etc).
Files will be placed in "src/platform" and "src/gameLayer" respectively.

Any headers should be included in "src/platform", "src/gameLayer", and "include" folders, since CMake will only look here.

"gameMain" already includes functions "initGame()", "updateGame()", and "closeGame()" that covers the basics needed to run a game.
