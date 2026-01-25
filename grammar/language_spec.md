## General
```
<program> := <function-declaration>* <statement>+ | empty
<identifier> := <letter>(<letter>|<digit>)*
<letter> := "a" | "b" | ... | "z" | "A" | "B" | ... | "Z"
<digit> := "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
```

## Expressions
```
<expression> := <binary> | <unary> | <primary>
<primary> := <bool> | <number> | <string> | <identifier> | <function-call> | <array-literal> | <array-access> | "(" <expression> ")" | "nil"
<array-literal> := "[" <expression-list>? "]"
<array-access> := <identifier> "[" <expression> "]"
<unary> := "!" <expression>
<binary> := "(" <expression> <op> <expression> ")"
<bool> := "true" | "false"
<number> := <digit>+
<string> := "\"" <char>* "\""
<char> := any printable character except '"'
<op> := "+" | "-" | "*" | "/"  | "==" | "!=" | "%" | "<=" | "<" | ">=" | ">" | "&" | "&&" | "|" | "||"
<function-call> := "call" <identifier> "(" <expression-list>? ")"
<expression-list> := <expression> ("," <expression>)*
```
## Statements
```
<statement> := <variable-declaration> | <variable-assignment> | <return> | <print> | <while> | <if>
<variable-declaration> := decl <identifier> ("=" <expression>)?
<variable-assignment> := <identifier> = <expression> | <array-access> = <expression>
<while> := while (<expression>) { <statement>+ }
<if> := if (<expression>) { <statement>+ } (else { <statement>+ })?
<return> := return <expression>
<print> := print(<expression>)
```

## Declarations
```
<function-declaration> := func <identifier>(<param-list>?) { <statement>+ }
<param-list> := <identifier> ("," <identifier>)*
```
