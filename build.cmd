g++ -Os -I include/ -c source/Tomato.cpp source/Export.cpp
g++ -shared -o Tomato.dll *.o -Wl,-add-stdcall-alias
rm *.o
make