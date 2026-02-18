# GitIgnore Adder

add files / directories to the `.gitignore` file

## Run

```sh
gitignore-adder --help
```

or add arguments after the programm name and every argument will be created
as a new Line in the Gitignore File.

## Use as Git Alias

add the Programm to you path and then run

```sh
git config --global alias.ignore gitignore-adder
```

## Build

For Linux use the Makefile with `make build`

For Windows build with CMake / Visual Studio or use Zig with the
`build.bat` script.
