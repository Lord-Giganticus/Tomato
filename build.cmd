g++ -Os -I include/ -c source/Tomato.cpp source/Export.cpp
g++ -shared -o Tomato.dll *.o
rm *.o
make