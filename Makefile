CC ?=gcc
JCC ?= javac
FLAGS ?= -Wall -O2
JFLAGS ?= -g -verbose

all: c_app EchoServer

c_app: c_app.c DataPoolDefine.c
	$(CC) $(FLAGS) -o c_app c_app.c DataPoolDefine.c

EchoServer: EchoServer.java
	$(JCC) $(JFLAGS) EchoServer.java $(LIBS)

    
clean:
	rm -f c_app EchoServer.class
