# Other Sections In Progress...

# Language Grammar
The update-to-date grammar of Cyth can be found [<u>**here**</u>](language-spec.md).

# Update History

## Cyth Version 0.1.2
### What's new:
- Added set data type.
- Added map data type.
- Added support for doubles.
- Added support for floats.
- Added support hex numbers.
- Added assert, length, and split primitive functions.
### Optimizations / Improvements:
- Overhaul of Value class:
  - Integrated a Number class to serve as a proxy for numbers (i.e., the previous Cyth version defined a number
  as a 64-bit integer). This class
  will serve as a simple and elegant way to integrate new number types in future versions.
  - Integrated an AbstractContainer class to serve as a proxy for container objects (i.e., sets, arrays, map).
### Bug Fixes
- Added error handling for when trying to subscript a non-container or string.
- Fixed visit_binary_expr in Interpreter; separated number based operations from general operations (i.e., on Value class). 
## Cyth Version 0.1.1
### What's new:
- Added continue statement to while and for loops.
### Optimizations / Improvements:
- _
### Bug Fixes
- _

## Cyth Version 0.1.0
### What's new:
- Added support for indexing strings.
### Optimizations / Improvements:
- Refactored indexing implementation in interpreter; indexing for arrays is faster.
### Bug Fixes
- _
