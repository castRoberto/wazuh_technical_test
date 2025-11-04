# wazuh_technical_test
Wazuh technical test solution for the C++ software engineer position

# Wazuh Serializer

This project implements a **C++ command-line tool** for configurable text **serialization** and **deserialization**.
It supports customizable delimiters, reversible escaping of special characters (`\n`, `,`, `\\`), and a robust argument parser for flexible usage.

---

## ⚙️ Compilation

### Prerequisites
- `make` (GNU Make) must be installed.
- A C++17 (or newer) compliant compiler (e.g., `g++`).

### Instructions
From the project root, run:

```bash
make
```
This will generate the binaries in:
```bash
build/debug/serializer
build/release/serializer
```

# Implementation Overview

## 🧩 Argument Parser

The ArgParser class analyzes and validates the command-line arguments provided to the program.
It checks that all required parameters are present and valid before execution.
Additionally, it provides a help mode (--help or -h) that displays usage information when arguments are missing or invalid.

| Argument      | Alias | Required   | Type / Values                | Description                                                     |
| ------------- | ----- | ---------- | ---------------------------- | --------------------------------------------------------------- |
| `--mode`      | `-m`  | ✅ Required | `serialize` or `deserialize` | Defines the operating mode.                                     |
| `--delimiter` | `-d`  | ❌ Optional | Single character             | Specifies the field delimiter. Defaults to `,` if not provided. |
| `--help`      | `-h`  | ❌ Optional | —                            | Displays program help and usage information.                    |

Incorrect or missing arguments cause the parser to throw an exception, which must be caught in the main program logic.

## 🔄 Serializer

The `DelimitedSerializer` class implements the `ISerializer` interface, and is responsible for performing the process of:

- Serialization: Reads multiple lines of text, escapes special characters, and combines them into a single line separated by a configurable delimiter.

- Deserialization: Splits the serialized line back into its original fields, correctly unescaping special characters.

The class operates on input/output streams (`std::istream` and `std::ostream`), allowing integration with:

- Standard input/output (`stdin` / `stdout`),

- Files (`cat`, redirections, etc.),

- Shell pipes (`|`), for chaining with other commands or scripts.

## 🏗️ Makefile
A `Makefile` is included to automate the build process.
It provides two build configurations:
- Debug — unoptimized, includes debugging symbols.
- Release — optimized build for final distribution.

Run the `make` command to compile the entire project

## Usage
The program can be used interactively or as part of a script using pipes or file redirection.

⚠️ When entering data manually from the terminal, you must signal EOF using Ctrl + D (Linux/macOS) or Ctrl + Z (Windows) to end the input.

## Example Using Files
Two example files are included in the project root:
- input.txt
- serialized.txt

### Serialize
```bash
cat input.txt | ./build/release/serializer -m serialize -d ','
```
Input (`input.txt`):
```bash
wazuh agent,
The\\open\n source\
security, platform\\n\
```
Serialized Output:
```bash
wazuh agent\,,The\\\\open\\n source\\,security\, platform\\\\n\\
```
### Deserialize
```bash
cat serialized.txt | ./build/release/serializer --mode deserialize -d ','
```
Input (`serialized.txt`):
```bash
wazuh agent\,,The\\\\open\\n source\\,security\, platform\\\\n\\
```
Deserialized Output:
```bash
wazuh agent,
The\\open\n source\
security, platform\\n\
```

## Example from Command Line
Serialize
```bash
./build/release/serializer --mode serialize -d ','
```
Deserialize
```bash
./build/release/serializer -m deserialize -d ','
```

# ✍️ Author
Roberto Enrique Castro Beltrán

