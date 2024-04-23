#!/bin/sh

# Clean the build directory and generate the compile_commands.json file

make clean && bear -- make
