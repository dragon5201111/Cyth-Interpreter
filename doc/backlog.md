# Cyth Backlog Overview
Working repository as of ***2-27-2026*** for any and all key in-flight changes. Below you can find a
change matrix and a summary of some of the key columns. The purpose of this document is to provide
more granular support / project history to the changelog - which provides major changes.

### Type Summary
- Fix: A bug in the Cyth language or issue that needs to be resolved.
- Feature: An addition to the Cyth language (e.g., set implementation, new operators).
- Addition: An addition external to the Cyth language or project (e.g., adding a new form of documentation).
- Revision: A revision to be made to the Cyth project such as an optimization, project structure overhaul or code refactor.

### Status Summary
- To Do: Has not been started yet.
- In Progress: Currently in progress.
- Aborted: Change is not to be implemented or was decided against.
- Done: Has been finished.

### Date Summary
- Start Date: Marks the start date for a particular change.
- End Date: Marks the end date for a particular change.

### Scale Summary
- Low: Change is of a low size.
- Medium: Change is of a medium size.
- High: Change is of a substantial size.

### Dependency Numbers
- This indicates change numbers that must occur before a particular change can be implemented or a linking between two or more changes.

# Change Matrix

| Change # | Dependency #'s | Change Name                               | Type     | Priority | Scale  | Status | Start Date | End Date  | Description                                                                                                            |
|----------|----------------|-------------------------------------------|----------|----------|--------|--------|------------|-----------|------------------------------------------------------------------------------------------------------------------------|
| 1        | -              | Preprocessor Comment                      | Fix      | High     | Medium | To Do  | -          | -         | Fix Preprocessor such that it can handle comments when processing include directives.                                  |
| 2        | -              | Tokenizer Line Count                      | Fix      | Low      | Medium | To Do  | -          | -         | Ensure Tokenizer line count is correct after preprocessing.                                                            |
| 3        | -              | REPL                                      | Feature  | Medium   | High   | To Do  | -          | -         | Add a REPL to command line.                                                                                            |
| 4        | -              | Define Directive                          | Feature  | Low      | Low    | To Do  | -          | -         | Add a define directive to Preprocessor.                                                                                |
| 5        | -              | Test Suite                                | Addition | Medium   | High   | To Do  | -          | -         | Add a test suite covering all aspects of Cyth.                                                                         |
| 6        | -              | Language Documentation                    | Addition | Medium   | High   | To Do  | -          | -         | Add documenation covering usage of all aspects of Cyth (e.g., writing source).                                         |
| 7        | -              | Test File Removal                         | Addition | Low      | Low    | To Do  | -          | -         | Remove unused or irrelevant test files.                                                                                |
| 8        | -              | Pragma Once Directive                     | Feature  | Low      | Low    | To Do  | -          | -         | Add a pragma directive to only allow inclusion of files one.                                                           |
| 9        | -              | Move Changelog                            | Revision | Medium   | Low    | Done   | 2/27/2026  | 2/27/2026 | Move changelog out of cyth-documentation.md and move to a separate file                                                | 
| 10       | -              | Main Args                                 | Feature  | Low      | Medium | Done   | 3/2/2026   | 3/2/2026  | Add a way to access optional args in main (e.g., main(args){})                                                         |
| 11       | -              | Refactor Include Directive Search         | Revision | Medium   | Low    | Done   | 2/27/2026  | 2/27/2026 | When searching for files when using the include directive, a stack should be maintained.                               |
| 12       | -              | Refactor Project Layout                   | Revision | Low      | Low    | Done   | 2/27/2026  | 2/27/2026 | Group related source and header files into respective folders and update the CMakeLists.txt file.                      |
| 13       | -              | Basic Container Operations                | Feature  | Medium   | Medium | To Do  | -          | -         | Add primitive container operations such as append / insert, remove, etc.                                               |
| 14       | -              | Assignment Operators                      | Feature  | Low      | Medium | To Do  | -          | -         | Add assignment operators for all binary operators (e.g., +=, *=, etc.).                                                |
| 15       | -              | Basic File Operations (IO Implementation) | Feature  | High     | High   | Done   | 3/3/2026   | 3/3/2026  | Expose file operations with primitive functions such as open, close, read, etc.                                        |
| 16       | -              | ID Primitive Function                     | Feature  | Low      | Low    | Done   | 3/3/2026   | 3/3/2026  | Expose a unique identifer for each Value (e.g., present the virtual address) object.                                   |
| 17       | -              | Heap Container                            | Feature  | Low      | Medium | To Do  | -          | -         | Add the heap datastructure.                                                                                            |
| 18       | 22             | Container Initializer                     | Feature  | Medium   | Low    | To Do  | -          | -         | Allow containers to be initialized with a specific number of elements (e.g., (\[0\] * 3) -> \[0,0,0\]).                |
| 19       | -              | Pointers                                  | Feature  | Low      | Medium | To Do  | -          | -         | Add a pointer type to Value.                                                                                           |
| 21       | -              | Tokenizer Overhaul                        | Revision | Medium   | High   | To Do  | -          | -         | Refactor the tokenizer to allow backtracking while maintaining the current functionality.                              |
| 22       | -              | Value Copy Constructor                    | Revision | Low      | Medium | To Do  | -          | -         | Add a copy constructor to the Value class.                                                                             |
| 23       | 15             | Enhanced File Operations                  | Feature  | High     | High   | To Do  | -          | -         | Add additional file operations such as seek, read n bytes / characters, etc.                                           |
| 24       | -              | Include Environment Variable              | Feature  | Low      | Low    | Done   | 3/4/2026   | 3/4/2026  | In addition to the current include directive search methods, search for files in the INCLUDE environment variable.     |