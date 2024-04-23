# SE Lab 1: Coffee Machine

This repository contains the source code for the first lab of the Software Engineering for Automation course. The lab is about software analysis, synthesis and refactoring of a coffee machine.

> [!TIP]
> Check out [this](https://guides.github.com/features/mastering-markdown/) guide about basic Markdown writing and formatting syntax. You can use [this](https://dillinger.io/) online editor to preview your Markdown files. Also, you might want to have a look at my GitHub tutorial [here](https://github.com/sid115/GitHubTutorial).

## Description 

Let's consider a typical fully automatic coffee machine for home and office use. Obviously, it's a mere emulation of a fully automatic coffee machine, in other words, all the processing of the Hardware components is strongly simplified, e.g. the processing of the brewing group or the grinder. For instance, we assume, that either the estimated result or a typical error occurs after a typical processing period has passed. In case you modify the software system, you have to ensure to adapt or rather expand the emulation of the hardware component's processing.

## Tasks

1. Software Analysis via Visual Paradigm
    - Select `src` as the source directory under `Tools` $\rightarrow$ `Code` $\rightarrow$ `Reverse C++ Code`.
    - Under `Class Repository` (left screen bar), press right mouse button on `C++ Round-trip` and select `Reverse Ressources to` $\rightarrow$ `New Class Diagram` .
    - Interpret the class diagram and debug the source code.
    - Roughly describe software system's functionality through a use case diagram and by associating meaningful activity diagrams.
1. Software Synthesis
    > "The customer should be able to choose between two sorts of coffee beans. Therefor we assume, that the coffee machine has two electromechanical slots, each of which can be loaded with a storage vessel for coffee beans. Consider, that any number of additional storage vessels for coffee beans can be stored outside the coffee machine, so that the maintenance staff could change them on customer's demand. Remove a plugged-in storage vessel first, if there is no free slot available. Outside of the coffee machine, the storage vessels are sealed for aroma protection and only the coffee machine can unlock their lid clip for refilling. Each slot has a weighing device to determine the mass of the contained coffee beans. Bear in mind, that the storage vessels could be used on other coffee machines in the office, which are identical in construction. In other words, the filling of a storage vessel and the extraction of coffee does not mandatorily happen in this coffee machine considered. Expand the software system to the extent that the user can choose between the currently available coffee beans for each brewing operation and that the coffee bean's sorts are displayed correctly after any exchange of a storage vessel."
1. Refactoring
    1. Consider a split of the brewing system class into at least two useful entities and adapt your model accordingly. 
    1. Generate your refactored software system and add missing source code. 
    1. Use Visual Studio debugger to prove that the refactored software system behaves correctly. 

## Development

The following instructions require a Unix-like environment.

### Cloning

Clone this repository to your local machine using:
```bash
git clone https://github.com/sid115/se-lab1.git
```

### Compiling

Compile this project using the included build script:
```bash
cd se-lab1
build.sh
```

> [!IMPORTANT]
> `build.sh` uses `bear` to generate the `compile_commands.json` file. Make sure to have `bear` installed on your system. If you don't have `bear` installed, you can compile the project manually using `make`:
> ```bash
> cd se-lab1
> make
> ```
> Please note that clangd requires the `compile_commands.json` file to work properly.

### Running

Run the compiled program using:
```bash
./output/main
```
