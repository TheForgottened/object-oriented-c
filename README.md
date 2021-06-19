# Object-oriented C

Small CLI game written in object-oriented C.

This game was inspired by the final assignment for the OOP class I attended during my degree in Computer Science & Engineering at ISEC. You can check the original project [here](https://github.com/JOSEALM3IDA/Material-ISEC/tree/main/POO-2020/Trabalho) (it's all in portuguese).

I don't know any standards on object-oriented like programming in C, so it probably violates some of them (I'd love to learn them, feel free to recommend some good literature).

Feel free to contribute.

# Table of Contents

- [Object-oriented C](#object-oriented-c)
- [Table of Contents](#table-of-contents)
- [Learn More](#learn-more)
- [ISEC Total War](#isec-total-war)
  - [Phases](#phases)
  - [Input](#input)
  - [Territories](#territories)
  - [Final Score](#final-score)
- [Compiling](#compiling)
- [License](#license)

# Learn More

You can learn more about the subject [here](LEARNMORE.md).

# ISEC Total War

ISEC Total War is the name of the implemented game. It's a Total War like game, hence the name, where you can conquer territories, buy technologies and become the world's supreme emperor!

You are limited to 12 rounds which are equivalent to 24 months (each round is theoretically 2 months long).

## Phases

| Phase | Description |
| :---: | --- |
| Setup | Where you can configure the world you'll play in |
| Conquest | Where you can conquer territories |
| Gathering | Where you'll receive goodies (gold and product) from your territories so you can buy technologies or improve your military later |
| Shop | Where you'll be able to purchase technologies or upgrade your military |
| Event | Where some random event will happen |

During the setup phase you can also run commands from a file using the `load` command.

## Input

Everytime you get asked for input the game tells you which commands are available. You can use the command `info` to learn about what a command does, using the syntax `info <command name>`.

## Territories

You have different types of territories and different types of terrain:

- Continent: you can conquer any territory inside the continent from the beginning;
- Island: you need the technology "Teleguided Missiles" to conquer it.

The amount of gold / product you receive from each territory will change during the game.

## Final Score

Your score is defined by everything your empire possesses: territories and technologies.

If you conquered every territory available you'll get the "supreme emperor" bonus and, if you have every technology available, you'll also get the "scientific" bonus.

# Compiling

If you wish to play the game without any debugging options just change the line `#define DEBUG true` to `#define DEBUG false` in the file `src/Codes.h`.

Also, if you're a Windows user you can't have `$(DEBUG)` in the `CFLAGS` variable inside the `makefile`.

# License

Licensed under the [GPLv3](LICENSE) license.