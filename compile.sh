#!/bin/bash

pkill exe_ahti
pkill exe_ws
rm exe*;
clear

g++ $(ls *.cpp | grep -v "ws.cpp") *.hpp *.h -w -o exe_ahti;
g++ $(ls *.cpp | grep -v "ahti.cpp") *.hpp *.h -w -o exe_ws;
