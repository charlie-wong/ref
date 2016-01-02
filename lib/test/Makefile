.PHONY: help
####################################################
CC	= g++
CFLAGS  = -std=c++11
LIBWLC	= /home/charlie/.wlc/lib
LIBWLCNE= wlc
####################################################
help:
	@echo '$$ ldd      命令用于查看可执行程序的动态库依赖关系'
colorize-test-static:
	$(CC) $(CFLAGS) colorize-test.cpp -L$(LIBWLC) -l$(LIBWLCNE) -static
colorize-test-dynamic:
	$(CC) $(CFLAGS) colorize-test.cpp -L$(LIBWLC) -l$(LIBWLCNE) -Wl,-rpath=$(LIBWLC)
value-test-static:
	$(CC) $(CFLAGS) value-test.cpp -L$(LIBWLC) -l$(LIBWLCNE) -static
value-test-dynamic:
	$(CC) $(CFLAGS) value-test.cpp -L$(LIBWLC) -l$(LIBWLCNE) -Wl,-rpath=$(LIBWLC)
linuxutility-test-static:
	$(CC) $(CFLAGS) linuxutility-test.cpp -L$(LIBWLC) -l$(LIBWLCNE) -static
linuxutility-test-dynamic:
	$(CC) $(CFLAGS) linuxutility-test.cpp -L$(LIBWLC) -l$(LIBWLCNE) -Wl,-rpath=$(LIBWLC)
version-test-static:
	$(CC) $(CFLAGS) version-test.cpp -L$(LIBWLC) -l$(LIBWLCNE) -static
version-test-dynamic:
	$(CC) $(CFLAGS) version-test.cpp -L$(LIBWLC) -l$(LIBWLCNE) -Wl,-rpath=$(LIBWLC)
