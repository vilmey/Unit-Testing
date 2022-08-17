# [Introduction](#introduction)

This repository is dedicated to the **Shell** component. This component is responsible for implementing a command prompt used on debugging, engineering tests and functional tests.
The goal of this repository is to make this component, **Shell**, easily available for use in different platforms.

# [Includded features](#includded-features)

1. A *WelcomeMessage* is shown when the program starts;
2. A prompt `> ` is shown whenever the system is waiting for user input;
3. The **Shell** executes the parsing of the arguments;
4. The **Shell** has a help menu, accesed by the command `help` or its shortcut `?`;
5. Support for command shortcuts;
6. Support for autocompletion with the `tab`;
7. Has history of commands, accessed with *arrow up* and *arrow down*;
8. The help for each command is accessed with the sintax *command + ?* Eg: `command ?`;
9. The status of any feature is accessed by typing the name of the feature with no arguments Ex: `led`;

# [Use](#use)

The goal of this component is to be hardware independent.
This project was tested on a NXP MIMXRT1020 using the MCUXpresso IDE, as well as on a regular PC.

This project can be directly imported on the MCUXpresso platform and run without many changes, as for running on a PC refer to [Build and Run on PC](#build-and-run-on-pc).

## [Folder structure](#folder-structure)

The main structure
```
project
.
├── Binaries (All the binary and executable files)
├── CMSIS
├── Objects  (Objects created by the Makefile)
├── Project  (Project configuration: MCUXpresso and Host)
├── Sources  (Source code)
└── Tests    (Unit test source code - Ceedling)
```

All the necessary code for the **Shell** is contained under `Sources/App/Device/Components`.
The *main* file `Sources/main.c`, contains an usage example for the component.

```
.
├── Common
│   └── Types.h             (Common definitions - uint8_t, int16_t)
├── Device
│   ├── Components
│   │   └── Shell           ( Shell Component )
│   │       ├── Commands    (Definition of the commands and Help menu)
│   │       │   ├── shellCommands.c
│   │       │   └── shellCommands.h
│   │       ├── Middleware  (Business rules for the Shell)
│   │       │   ├── shell.c
│   │       │   └── shell.h
│   │       └── Utils       (Autocomplete, Parsing, Command Comparison )
│   │           ├── shellUtils.c
│   │           └── shellUtils.h
│   ├── Peripherals
│   └── Tasks
├── Utils
└── main.c                  (Usage Example)
```


## [Build and Run on PC](#build-and-run-on-pc)

To build the application for a PC, run the command `make all` from the root directory, where the *Makefile* resides.
The executable is located at `/Binaries/Host/output`.

## [Portability](#portability)

The peaces of coded needed are present under the directory `Sources/App/Device/Components/Shell`.
All the other files included in the repository are needed to compile the code for the controller NXP MIMXRT1020.

Porting checklist:
- Get the code from `Sources/App/Device/Components/Shell`;
- Make sure there are definitions for the common types (uint8_t, int16_t etc);
- Update the `Shell/Commands/shellCommands.c` with the needed commands;
- Update the definition **SHELL_COMMANDS_NUM** whenever a command is added;
- Use the command `Shell_getChar( your-char-here )` to send the characters to the component.

## [Test](#test)

The tests for this component were written under the directory `Tests`, using the testing framework (Unity + Ceedling).
You can run the tests from the root directory with the command `ceedling test:all`.

The dependencies needed to run these tests are [*Ruby Install*](https://www.ruby-lang.org/en/documentation/installation/) and [*Ceedling Install*](http://www.throwtheswitch.org/ceedling).