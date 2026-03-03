# Changelog Overview
Welcome to the Cyth changelog. Here you can find any ***major*** updates regarding changes to the language, revisions
bug fixes, and what's new. To see upcoming features, additions, removals, and extra details
regarding changes, take a look at the Cyth [<u>**backlog**</u>](backlog.md).

# Cyth Version 0.1.4 \[3-3-2026\]
### What's new:
- _
### Changes:
- _
### Bug Fixes
- _

# Cyth Version 0.1.3 \[2-27-2026\]
### What's new:
- Main now supports arguments. You can now enclose an identifier in parentheses after main to which command line
arguments will be bound to (e.g., main(args){}); any arguments not processed by Cyth will be bound to
the identifier specified in main contained as an array of strings, if provided. Command line arguments prefixed with a dash or double-dash
shall be prefixed with a backward slash to be contained in the array of strings bound by the specified identifier - otherwise they will be ignored.
- Added ID primitive function. A call to ID returns the memory address of its input as a string.
- Integrated a FileContainer and respective functions - open, close, and readLine.
- Put, Length, and Remove operations are now supported on containers.
- Added an 8-bit width Integers type.
### Changes:
- The Preprocessor now handles include directives using a stack. It is similar to the C Preprocessor
in which it will search in the following manner: "In the directories of the currently opened include files, in the reverse order in which they were opened. The search begins in the directory of the 
parent include file and continues upward through the directories of any grandparent include files".
- Length built-in now works for strings.
- Integers are now distinguished between 64-bit and 8-bit integers; this change is reflected in the tokenizer and respective AST Expr types.
### Bug Fixes
- Interpreter visitor method visit_program now properly returns and propagates a return value. Before, it would simply
  call exit, causing a memory leak.
- Fixed Number class casting issues.

# Cyth Version 0.1.2 \[2-23-2026\]
### What's new:
- Integrated Preprocessor.
### Changes:
- Changed multi-line comments from back ticks to `/**/`.
- Reworked whitespace handling in Tokenizer.
- Added `I` flag. This flag when used will specify a directory to
  search for files using the `include` directive.
### Bug Fixes
- _

# Cyth Version 0.1.1 \[2-22-2026\]
### What's new:
- Added set data type.
- Added map data type.
- Added support for doubles.
- Added support for floats.
- Added support hex numbers.
- Added assert, length, and split primitive functions.
### Changes:
- Overhaul of Value class:
    - Integrated a Number class to serve as a proxy for numbers (i.e., the previous Cyth version defined a number
      as a 64-bit integer). This class
      will serve as a simple and elegant way to integrate new number types in future versions.
    - Integrated an AbstractContainer class to serve as a proxy for container objects (i.e., sets, arrays, map).
### Bug Fixes
- Added error handling for when trying to subscript a non-container or string.
- Fixed visit_binary_expr in Interpreter; separated number based operations from general operations (i.e., on Value class).

# Cyth Version 0.1.0 \[2-13-2026\]
### What's new:
- Added continue statement to while and for loops.
### Changes:
- _
### Bug Fixes
- _