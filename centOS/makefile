

######################################
##定义编译方式、依赖库路径
#CC = g++
#CFLAGS	:=	-Wall -03 -std=c++0x00
#CLIENT_LIB = -ljson


  
#target you can change test to what you want
#共享库文件名，lib*.a
TARGET  := libjson.a
  
#compile and lib parameter
#编译参数
CC      := g++
AR      = ar
RANLIB  = ranlib


main:main.o client.o file.o cjson.o
	g++ -o main  main.o client.o file.o cjson.o libjson.a

main.o:main.cpp main.h client.cpp cjson.cpp file.cpp 
	g++ -o main.o





clean :
    rm -fr *.o
    

