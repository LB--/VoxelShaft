del /s /f /q .\build\* && for /f %%f in ('dir /ad /b .\build\') do rd /s /q .\build\%f
title RecipeSpelunker-Build && mkdir build
cd build && cmake -G "MinGW Makefiles" -DCMAKE_CXX_FLAGS=" -Wall -Wextra -pedantic -Wno-unused-parameter -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Wunreachable-code -Wmissing-include-dirs -Wmain" -DCMAKE_BUILD_TYPE=RELEASE  -DSTATIC_BUILD=1 -DSFML_ROOT="C:/Program Files (x86)/SFML" -DBOOST_ROOT="C:\MinGW" ../
cmd /k "make && resplunk-client"