CC ?=gcc
JCC ?= javac
FLAGS ?= -Wall -O2 
JFLAGS ?= -g -verbose
LIBS ?= /root/ipc/java-c-YC/java_EchoServer/log4j-1.2.17.jar

all: c_app EchoServer

c_app: ./c_com/c_app.c ./c_com/DataPoolDefine.c
	$(CC) $(FLAGS) -o c_app ./c_com/c_app.c ./c_com/DataPoolDefine.c

EchoServer: ./java_EchoServer/EchoServer.java
	$(JCC) $(JFLAGS) -cp "$(LIBS)" -d ./ ./java_EchoServer/EchoServer.java 

    
clean:
	rm -f c_app EchoServer.class
