# Lexxer
## Group Name: Alpha Kenny Brody
## Group Members: Cody Thompson, Tracy Tonnu, Russel Koh
Lexical Analyzer for Spring Semester 2020 CPSC 323 CSUF


________________________________________________________________________________________________________________________________

### The first assignment is to write a lexical analyzer (lexer) 

You can build your entirelexer using a FSM, Orbuild using at least FSMs for identifier,integer and real (the rest can be written ad-hoc/procedural) but YOU HAVE TO CONSTRUCT A FSM for this assignment otherwise, there will be a deduction of 2 points!

***Note**:In your documentation (design section), YOU MUST write the REs for Identifiers, Real and Integer, and also show the NFSM using Thompson.*
________________________________________________________________________________________________________________________________

## The Lexer
A major component of your assignment will be to write a procedure (Function) –lexer (),  that returns atoken when it is needed.  Your lexer() should return a record, one field for the token and another field the actual "value" of the token (lexeme), i.e. the instance of a token. 

Your main program should test the lexer i.e., your program should read a file containingthe source code given from class to generate tokens and write out the results to an output file.  Make sure that you print both, the tokens and lexemes.  

________________________________________________________________________________________________________________________________

**Basically,** your main program should work as follows: 
* while not finished (i.e. not end of the source file) do 
* call the lexer for a token 
* print the token and lexemes.
* endwhile 
________________________________________________________________________________________________________________________________

**Do at least 3 test cases and make sure that you turn in proper documentation using the documentation template.**

*A simple  test case*
*(Partial)Source code:* 

while(fahr < upper)   a = 23.00 whileend

**Output:**

Token | Lexeme
------------ | -------------
keyword | while                    
separator | (                    
identifier | fahr              
operator | <                    
identifier | upper                    
separator | )                    
identifier | a                    
operator | =
real | 23.00                    
keyword | whileend

________________________________________________________________________________________________________________________________


## Sample token list
**TOKEN** | **Example Lexemes**
------------ | -------------
**KEYWORDS** 	|	int, float, bool, true, false, if, else, then, endif, while, whileend, do, doend, for, forend, input, output, and, or, not
**IDENTIFIERS** 	|	legal identifiers must start with alphabetic character follow by digits, alpha, or $
**SEPARATORS** 	|	'(){}[],.:; sp(space)
**OPERATORS** 	|	*+-=/><%

________________________________________________________________________________________________________________________________


**Additional examples:**
* Valid IDENTIFIERS	:  	num, num1, large$, num$1, num2, num2$, a9, ab, ab2, etc...
* Valid Numbers		:	integers whole numbers (1,2,3,...) and reals floats (5.0, 0.9, 1.75, ...)
* Valid Block Comments	:	!  this is a block comment to be ignored by the Lexical Analyzer !

________________________________________________________________________________________________________________________________

## FSM Psuedo
FSM(tokenQueue)

  int state = 1, i = 0
 
 while lexeme.lenght()
    
    switch state
      case 1: Determine token[i]
              Update state
              break

      case 2: Determine token[i]
              Update state
              break

              .
              .
              .

      case 6: Determine token[i]
              Update state
              break

    end switch
    
  end while

  string token   

  switch state
  
    case 2: token = "Identifier"
            break

    case 3: token = "Integer"
            break

    case 5: token = "Real Number"
            break

    default: token = "Unknown"
    
  end switch
  
end FSM
