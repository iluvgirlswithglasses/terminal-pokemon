cd .\src

clang++.exe -O3 -target x86_64-pc-windows-msvc -Wno-deprecated -c *.h *.cpp
clang++.exe *.o *.gch -o o-win-clang++.exe
del *.o *.gch

cd ..
move .\src\o-win-clang++.exe .\o-win-clang++.exe
