# How to use Git on the command line

This is a quick guide to using Git from the command line on Unix-like systems. This manual is intended for use with this repository and does not necessarily contain general information.

> Before you start, I recommend you to read about 'What is Git and GitHub?' and 'Basic Git terminology' in my GitHub Tutorial [here](https://github.com/sid115/GitHubTutorial).

All commands are to be run in the terminal. If you are using Windows, you can use the terminal inside Visual Studio Code while being connected to [WSL](https://learn.microsoft.com/en-us/windows/wsl/install) (Windows Subsystem for Linux). You need the [WSL extension](https://learn.microsoft.com/en-us/windows/wsl/tutorials/wsl-vscode) for this.

## Install Git

How to install Git depends on your operating system. Some common package managers are listed below.

### Ubuntu / Debian

```bash
sudo apt-get update
sudo apt-get install git
```

### Arch Linux

```bash
sudo pacman -Syy git
```

## Initial configuration

Set your name and email address:

```bash
git config --global user.name "Your Name"
git config --global user.email "your_mail@example.com"
```

> These values are used in the commit messages. They can be arbitrary.

Verify the configuration:

```bash
git config --list
```

## Clone this repository

This will pull the repository to your local machine and create a directory called `se-lab1`. Make sure you are in a directory where you want to clone the repository.

```bash
git clone https://github.com/sid115/se-lab1.git
```

Now, you can navigate to the repository directory and make changes as needed. 

```bash
cd se-lab1
```

Before you start making changes, it's a good idea to pull the latest changes from the remote repository:

```bash
git pull
```

## Committing and Syncing changes

Once you have made changes to the files in the repository, you can commit them to the repository. Start by navigating into the repository directory.

### Stage files

You have the option to stage specific files for a commit:

```bash
git add file1 file2
```

Or stage all modified files:

```bash
git add .
```

To remove files from the staging area, use:

```bash
git reset file1 file2
```

> This does not remove the files from your working directory, only from the staging area.

Always verify the status of your files:

```bash
git status
```

### Commit staged changes

After reviewing your staged changes and you're satisfied, it's time to commit them:

```bash
git commit -m "Commit message"
```

> The commit message should be a succinct, clear summary of the changes you've made.

### Pull latest changes

Before pushing your local commits, it's a best practice to pull the latest changes from the remote repository. This helps to avoid any merge conflicts on the remote repository:

```bash
git pull
```

### Push committed changes

With all local commits up-to-date with the remote repository, you can now push your changes:

```bash
git push
```

This pushes the commits to the master branch of the remote repository.

Your changes are now synced with the remote repository, and you can view them on GitHub.

## Tips

Below are some tips to make your life easier when using Git. This section is optional.

### Aliases

Typing the full command every time can be tedious. You can use aliases to make it easier. First, open your `.bashrc` file:

```bash
nano ~/.bashrc
```

Add the following lines to your `~/.bashrc`.

```bash
alias ga='git add'
alias gb='git branch'
alias gc='git commit -m'
alias gcl='git clone'
alias gco='git checkout'
alias gd='git diff'
alias gl='git log'
alias gm='git merge'
alias gp='git push'
alias gpl='git pull'
alias gr='git reset'
alias gs='git status'
```

Save the file by pressing `Ctrl + O` and then `Enter`. Exit the editor by pressing `Ctrl + X`.

Source the file to apply the changes:

```bash
source ~/.bashrc
```

Now, you can use the aliases to run the commands. For example:

```bash
ga file1 file2
gc "Commit message"
gp
```
