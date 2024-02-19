# EBNF to Graph Parser

The EBNF to Graph Parser is a tool designed to transform Extended Backus-Naur Form (EBNF) expressions into graphical representations, providing a visual representation of the syntactic structure defined by the [EBNF grammar](https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_form).

## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [How it Works](#how-it-works)
- [Use cases](#use-cases)
- [Installation](#installation)
- [Usage](#usage)
- [License](#license)



## Project Overview

Parsing and visualizing EBNF expressions is a crucial aspect of understanding and designing programming languages or domain-specific languages. This parser takes one EBNF expression as input and generates graphical representations, typically in the form of a syntax tree or a diagram, which can be further analyzed and visualized.

## Features

- **EBNF Parsing:** Parse EBNF expression to extract grammar rules and syntactic structures.
- **Graphical Representation:** Generate visual representations, such as syntax trees or diagram, from the parsed EBNF.


## How It Works

1. **Input EBNF:** Users input a EBNF expression representing the grammar of a language.
2. **Parsing:** The parser processes the EBNF expression and extracts grammar rules and structure based on this EBNF definfition :  
    > Production : Identifier ‘=’ Expression ‘ ; ‘  
    Expression :  term {"|" term}  
    Term : {factor }  
    Factor : identifier | Literal| "(" expression ")" | "[" expression "]" | "{" expression "}"  
    
3. **Graph Generation:** The extracted information is used to generate a graphical representation, offering a visual overview of the language's syntax.

## Use Cases

- **Language Design:** Aid in the design and understanding of programming languages or DSLs.
- **Education:** Facilitate the learning process of formal grammars and language specifications.
- **Syntax Analysis:** Assist in identifying syntactic patterns and rules in existing languages.

## Installation

```bash
# installation commands for windows
$ git clone https://github.com/oumaimaoys/EBNF_to_graphics_parser.git
$ cd EBNF_to_graphics_parser
$ mingw32-make
$ cd build
$ main.exe
```

## Usage
![test in command prompt](/assets/test.png)  

when 2 is inputed, the SDL window pops up  

![generated diagram](/assets/sdlwindow.png)

## License

This project is licensed under the [MIT License](LICENSE). Feel free to explore, use, and contribute to the project under the terms of this license.
