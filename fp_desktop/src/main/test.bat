set PATH=..\..\target\dependencies\windows-x32\lib;%PATH%
set FP_LIBS=..\..\target\dependencies\windows-x32\lib
set PYHOME=..\..\target\dependencies\windows-x32\bin\python
set FPPY=..\..\target\dependencies\python\lib
..\..\target\staging\fp_desktop.exe -w 800 -h 600 -r res -p %FP_LIBS% -p %FPPY% -p %PYHOME% test.py