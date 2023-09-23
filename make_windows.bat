@ECHO OFF
REM Variables relevant to the compilation of the program.
SET CC=gcc
SET COBJS=smile.c
SET EDCFLAGS=-I ./include/ -I ./ -I "C:\Users\locsst\anaconda3\include" -Wall %CFLAGS%
SET EDLDFLAGS= -s -shared -static-libgcc %LDFLAGS%
SET TARGET=test_c.dll

REM This runs a command-prompt command to compile using GCC.
CMD /c "%CC% %EDCFLAGS% %COBJS% -o %TARGET% %EDLDFLAGS%"

REM This will run the executable automatically.
REM START %TARGET%