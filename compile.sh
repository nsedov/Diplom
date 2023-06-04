g++ -std=c++11  -I/usr/include/python3.8 -I/usr/local/include/boost/python -c -fPIC myntl.cpp  -o myntl.o
g++ -std=c++11 -I/usr/include/python3.8 -I/usr/local/include/boost/python -shared -Wl,-soname,hello_ext.so -o myntl.so myntl.o -lpython3.8 -lboost_python38 -lntl
echo done
