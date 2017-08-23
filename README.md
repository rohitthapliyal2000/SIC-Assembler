# SIC-Assembler
C++ implementation of SIC Assembler.

Basic assembler functions :                                                                                                     
Translating mnemonic operation codes to their machine language equivalents.                                                     
Assigning machine addresses to symbolic labels.
Write the object program and the assembly listing

Assembler directives :
Assembler directives are pseudo instructions
They provide instructions to the assembler itself
They are not translated into machine operation codes
SIC assembler directive
START : specify name & starting address
END : end of source program, specify the first execution instruction
BYTE, WORD, RESB, RESW
End of record : a null char (00)
End of file : a zero-length record

Implementation includes 2 passes :
First pass: Scan the source program for label definitions and assign addresses
Second pass: Perform actual translation
