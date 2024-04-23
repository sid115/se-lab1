# Basic Bash Commands and Nano Editor

This guide introduces you to some of the most basic bash commands to navigate the file system in Linux, as well as how to use the nano text editor.

## Bash Commands

Bash is a command-line shell for Unix-like operating systems. Here are some of the most commonly used bash commands:

### Listing files: `ls`

Displays the list of files and directories in the current directory.

```bash
ls
```

To list all files, including hidden files (files that begin with a `.`), use the `-a` option.

```bash
ls -a
```

### Changing directories: `cd`

Allows you to change the current directory. Replace `DIRECTORY_PATH` with the path of the directory you want to navigate into.

```bash
cd DIRECTORY_PATH
```

To naviagate to the parent directory, use `..`.

```bash
cd ..
```

To navigate to the home directory, just use `cd` without any arguments.

```bash
cd
```

### Printing current directory: `pwd`

Prints the complete path of the current directory.

```bash
pwd
```

### Making a new directory: `mkdir`

Creates a new directory. Replace `NEW_DIRECTORY` with the name of the new directory.

```bash
mkdir NEW_DIRECTORY
```

### Removing a file: `rm`

Removes a file. Replace `FILE_NAME` with the name of the file you want to remove.

```bash
rm FILE_NAME
```

To remove a directory and its contents, use the `-r` option.

```bash
rm -r DIRECTORY_NAME
```

> **Caution:** Be careful when using the `rm` command, as it permanently deletes files and directories.

## Using Nano Text Editor

**Nano** is a simple, user-friendly text editor in Linux.

To open **Nano** with a new or existing file, use the `nano` command followed by the file name.

```bash
nano FILE_NAME
```

In Nano:

- To navigate, use the arrow keys. Some terminal emulators may also support the mouse.
- To save changes, press `Ctrl+O`, then press `Enter`.
- To exit, press `Ctrl+X`.
- To search within the file, press `Ctrl+W` and enter your search query.
- To cut the entire line, press `Ctrl+K`.
- To paste the cut text, place the cursor at the desired location and press `Ctrl+U`.

## Tips

Here are some additional tips to help you work more efficiently in the terminal:

### Manual Pages

Explore `man` (manual) pages for these and other commands for more options and functionalities.

```bash
man COMMAND_NAME
```
Replace `COMMAND_NAME` with the name of the command you wish to learn more about.

### Control Keys

Inside the terminal, you can use the following control keys to perform various actions:

- `Ctrl+C`: Interrupt (kill) the current process.
- `Ctrl+Z`: Suspend the current process.
- `Ctrl+D`: Log out of the current session.
- `Ctrl+L`: Clear the screen.
- `Ctrl+A`: Move the cursor to the beginning of the line.
- `Ctrl+E`: Move the cursor to the end of the line.

The clipboard can be accessed using the following shortcuts:

- `Ctrl+Shift+C`: Copy selected text.
- `Ctrl+Shift+V`: Paste copied text.

### Tab Completion

Tab completion is a feature that allows you to complete file and directory names by pressing the `Tab` key. This can save you time and reduce typing errors.

### History

You can use the arrow keys to navigate through the command history. Press the `Up` arrow key to access previous commands.

You can also search through the command history by pressing `Ctrl+R` and typing a keyword.

### Aliases

You can create aliases for frequently used commands to save time. Add aliases to your `.bashrc` or `.bash_aliases` file.

```bash
alias SHORTCUT="COMMAND"
```

Use nano to open the `.bashrc` file:

```bash
nano ~/.bashrc
```

Add your aliases at the end of the file, for example:

```bash
alias ll="ls -Alh"
```

Source the `.bashrc` file to apply the changes:

```bash
source ~/.bashrc
```

Now, you can use `ll` instead of `ls -Alh` to list files with detailed information.
