## General
```
<program> := <function-declaration>* ("main" { <statement>+ })+
<identifier> := <letter>(<letter>|<digit>)*
<letter> := "a" | "b" | ... | "z" | "A" | "B" | ... | "Z"
<digit> := "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
```

## Expressions
```
<expression> := <binary> | <unary> | <primary> | <postfix>
<primary> := <bool> 
    | <number> 
    | <string> 
    | <identifier> 
    | <function-call> 
    | <array-literal>    
    | <set-literal> 
    | <map-literal>
    | "(" <expression> ")" 
    | "nil"
<postfix> := <primary> | <postfix> [ <expression> ]
<array-literal> := "[" <expression-list>? "]"
<set-literal> := "{" <expression-list>? "}"
<map-literal> := "{{" <map-expression-list>? "}}"
<map-expression-list> := <expression> ":" <expression> ("," <map-expression-list>)?
<unary> := ("!" | "-") <expression>
<binary> := "(" <expression> <op> <expression> ")"
<bool> := "true" | "false"
<number> := <integer> | <double> | <float> | <hex>
<integer> := <digit>+
<float> := <double> ("f" | "F")
<double> := <digit>+ "." <digit>*
<hex> := "0" ("x" | "X") ("0-9" | "a-f" | "A-F")*
<string> := "\"" <char>* "\""
<char> := any printable character except '"'
<op> := "+" 
    | "-" 
    | "*" 
    | "/"  
    | "==" 
    | "!=" 
    | "%" 
    | "<=" 
    | "<" 
    | ">=" 
    | ">" 
    | "&" 
    | "&&" 
    | "|" 
    | "||" 
    | "<<" 
    | ">>"

<function-call> := "call" <identifier> "(" <expression-list>? ")"
<expression-list> := <expression> ("," <expression>)*
```
## Statements
```
<statement> := <declaration> 
    | <assignment> 
    | <return> 
    | <while> 
    | <if> 
    | <function-call-stmnt> 
    | break
    | continue
    
<declaration> := decl <identifier> ("=" <expression>)?
<assignment> := (<identifier> |  <postfix>) "=" <expression>
<for> := for ((<declaration> | <assignment>)?,<expression>?,<assignment>?) { <statement>+ }
<while> := while (<expression>) { <statement>+ }
<if> := if (<expression>) { <statement>+ } (else { <statement>+ })?
<return> := return <expression>
<function-call-stmnt> := <function-call>
<break> := break
<continue> := break
```

## Declarations
```
<function-declaration> := func <identifier>(<param-list>?) { <statement>+ }
<param-list> := <identifier> ("," <identifier>)*
```