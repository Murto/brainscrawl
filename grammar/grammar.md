# Brainfuck Grammar

## Nonterminal Productions

```
PROGRAM = { COMMAND } , EOF ;
COMMAND = MOVE_LEFT | MOVE_RIGHT | INCREMENT | DECREMENT | OUTPUT | INPUT | LOOP ;
LOOP    = LOOP_BEGIN , { COMMAND } , LOOP_END ;
```


## Terminal Productions

```
MOVE_LEFT  = "<" ;
MOVE_RIGHT = ">" ;
INCREMENT  = "+" ;
DECREMENT  = "-" ;
OUTPUT     = "." ;
INPUT      = "," ;
LOOP_BEGIN = "[" ;
LOOP_END   = "]" ;
EOF        = ? End of input ? ;
```
