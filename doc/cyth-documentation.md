# Other Sections To Come ...

# Update History

## Cyth Version 0.1.2
### What's new:
- Added set data type.
- Added support for doubles.
- Added support for floats.
- Added support hex numbers.
- Added assert primitive function.
### Optimizations / Improvements:
- Refactored Value class. to_string_impl for container objects - container objects now
delegate to a container_to_string method. Similarly, a containers_are_equal method was defined to
compare containers in is_truthy method.
- Integrated a Number class to serve as a proxy for numbers (i.e., currently 64-bit integers). This class
will serve as a simple and elegant way to integrate new number types in future versions.
### Bug Fixes
- Added error handling for when trying to subscript a non-container or string.

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
