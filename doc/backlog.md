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

# Change Matrix

| Change Name                       | Type     | Priority | Status | Start Date | End Date  | Description                                                                                       |
|-----------------------------------|----------|----------|--------|------------|-----------|---------------------------------------------------------------------------------------------------|
| Preprocessor Comment              | Fix      | High     | To Do  | -          | -         | Fix Preprocessor such that it can handle comments when processing include directives.             |
| Tokenizer Line Count              | Fix      | Low      | To Do  | -          | -         | Ensure Tokenizer line count is correct after preprocessing.                                       |
| REPL                              | Feature  | Medium   | To Do  | -          | -         | Add a REPL to command line.                                                                       |
| Define Directive                  | Feature  | Low      | To Do  | -          | -         | Add a define directive to Preprocessor.                                                           |
| Test Suite                        | Addition | Medium   | To Do  | -          | -         | Add a test suite covering all aspects of Cyth.                                                    |
| Language Documentation            | Addition | Medium   | To Do  | -          | -         | Add documenation covering usage of all aspects of Cyth (e.g., writing source).                    |
| Test File Removal                 | Addition | Low      | To Do  | -          | -         | Remove unused or irrelevant test files.                                                           |
| Pragma Directive                  | Feature  | Low      | To Do  | -          | -         | Add a pragma directive to only allow inclusion of files one.                                      |
| Move Changelog                    | Revision | Medium   | Done   | 2/27/2026  | 2/27/2026 | Move changelog out of cyth-documentation.md and move to a separate file                           | 
| Main Args                         | Feature  | Low      | To Do  | -          | -         | Add a way to access optional args in main (e.g., main(args){})                                    |
| Refactor Include Directive Search | Revision | Medium   | Done   | 2/27/2026  | 2/27/2026 | When searching for files when using the include directive, a stack should be maintained.          |
| Refactor Project Layout           | Revision | Low      | Done   | 2/27/2026  | 2/27/2026 | Group related source and header files into respective folders and update the CMakeLists.txt file. | |