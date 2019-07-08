# Test file for Lab3_BitManipulation


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n
#1
test "PINA: 0x00 => PORTC: 0x07"
setPINA 0x00
continue 5
expectPORTC 0x07
checkResult
#2
test "PINA: 0x01 => PORTC: 0x08"
setPINA 0x01
continue 1
expectPORTC 0x08
checkResult
#3
test "PINA: 0x01 => PORTC: 0x09"
setPINA 0x01
continue 1
expectPORTC 0x09
checkResult
#4
test "PINA: 0x01 => PORTC: 0x09"
setPINA 0x01
continue 1
expectPORTC 0x09
checkResult
#5
test "PINA: 0x02 => PORTC: 0x08"
setPINA 0x02
continue 1
expectPORTC 0x08
checkResult
#6
test "PINA: 0x02 => PORTC: 0x07"
setPINA 0x02
continue 1
expectPORTC 0x07
checkResult
#7
test "PINA: 0x02 => PORTC: 0x06"
setPINA 0x02
continue 1
expectPORTC 0x06
checkResult
#8
test "PINA: 0x02 => PORTC: 0x05"
setPINA 0x02
continue 1
expectPORTC 0x05
checkResult
#9
test "PINA: 0x02 => PORTC: 0x04"
setPINA 0x02
continue 1
expectPORTC 0x04
checkResult
#10
test "PINA: 0x02 => PORTC: 0x03"
setPINA 0x02
continue 1
expectPORTC 0x03
checkResult
#11
test "PINA: 0x02 => PORTC: 0x02"
setPINA 0x02
continue 1
expectPORTC 0x02
checkResult
#12
test "PINA: 0x02 => PORTC: 0x01"
setPINA 0x02
continue 1
expectPORTC 0x01
checkResult
#13
test "PINA: 0x02 => PORTC: 0x00"
setPINA 0x02
continue 1
expectPORTC 0x00
checkResult
#14
test "PINA: 0x02 => PORTC: 0x00"
setPINA 0x02
continue 1
expectPORTC 0x00
checkResult
#15
test "PINA: 0x03 => PORTC: 0x07"
setPINA 0x03
continue 1
expectPORTC 0x07
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
