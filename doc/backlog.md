# Cyth Backlog
## Type Summary
- Fix: A bug in the Cyth language or issue that needs to be resolved.
- Feature: An addition to the Cyth language (e.g., set implementation, new operators).
- Addition: An addition external to the Cyth language or project (e.g., adding a new form of documentation).
## Status Summary
- To Do: Has not been started yet.
- In Progress: Currently in progress.
- Done: Has been finished.

| Name                   | Type     | Priority | Status | Start Date | End Date  | Description                                                                           |
|------------------------|----------|----------|--------|------------|-----------|---------------------------------------------------------------------------------------|
| Preprocessor Comment   | Fix      | High     | To Do  |            |           | Fix Preprocessor such that it can handle comments when processing include directives. |
| Tokenizer Line Count   | Fix      | Low      | To Do  |            |           | Ensure Tokenizer line count is correct after preprocessing.                           |
| REPL                   | Feature  | Medium   | To Do  |            |           | Add a REPL to command line.                                                           |
| Define Directive       | Feature  | Low      | To Do  |            |           | Add a define directive to Preprocessor.                                               |
| Test Suite             | Addition | Medium   | To Do  |            |           | Add a test suite covering all aspects of Cyth.                                        |
| Language Documentation | Addition | Medium   | To Do  |            |           | Add documenation covering usage of all aspects of Cyth (e.g., writing source).        |
| Test File Removal      | Addition | Low      | To Do  |            |           | Remove unused or irrelevant test files.                                               |
| Pragma Directive       | Feature  | Low      | To Do  |            |           | Add a pragma directive to only allow inclusion of files one.                          |
| Move Changelog         | Addition | Medium   | Done   | 2/27/2026  | 2/27/2026 | Move changelog out of cyth-documentation.md and move to a separate file               | 
| Main Args              | Feature  | Low      | To Do  |            |           | Add a way to access optional args in main (e.g., main(args){})                        |