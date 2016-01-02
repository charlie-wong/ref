.PHONY:clean install update uninstall help all
#####################################################################
#指定安装位置
PREFIX="/home/`whoami`/.wlc/lib"
#####################################################################
# 向 HEADERS 和 LOOBJS 添加相应新文件即可
CC	  = g++
CFLAGS	  = -Wall -std=c++11
HEADERS	  = colorize.h debug.h libwlc.h value.h linuxutility.h version.h
LOOBJS	  = value.lo colorize.lo linuxutility.lo version.lo

LIBWLC    = libwlc.la#工具 libtool 生成库必须文件(libwlc库名)

DELLOOBJS   = *.o *.lo *.la .libs/*
LIBSTNE   = libwlc.a#静态库名
LIBDYNE   = libwlc.so#动态库名
#####################################################################
#使用说明
help:
	@echo "make all                 编译 libwlc 库"
	@echo "make install             编译并安装库 $(LIBSTNE) 和 $(LIBDYNE) 到 $(PREFIX) 目录"
	@echo "make install PREFIX=PATH 将库安装在 PATH 目录"
	@echo "make update              编译并更新本地库"
	@echo "make uninstall           从 $(PREFIX) 位置卸载 $(LIBSTNE) 和 $(LIBDYNE) "
	@echo "make clean               删除所有编译输出"
	@echo "make help                显示本帮助信息"
	@echo ""
	@echo "TIPS: 如何使用安装好的库，请查看 ./test 目录的 Makefile"
all:$(LIBWLC)
	@echo "Frome Charlie: All is up to date."
update:
	@make uninstall
	@make install
	@echo "Frome Charlie: Update completed."
#安装
install:$(LIBWLC)
	libtool --mode=install install -c $(LIBWLC) $(PREFIX)
	@echo "安装后如果不能使用或出现问题,使用以下命令"
	@echo "libtool -n --mode=finish $(PREFIX)"
#卸载
uninstall:
	libtool --mode=uninstall rm $(PREFIX)/$(LIBWLC)

#创建库
#-rpath PATH	指定生成的库的安装位置,仅绝对路径有效
#libXXX.la	生成的库的名字,该名字必须以 lib 开头且以 .la 结尾
$(LIBWLC):$(LOOBJS)
	libtool --mode=link $(CC) -o $(LIBWLC) $(LOOBJS) -rpath $(PREFIX)

#生成创建库时依赖的.o .lo等对象文件
%.lo:%.cpp $(HEADERS)
	libtool --mode=compile $(CC) $(CFLAGS) -c -o $@ $<
clean:
	rm -f $(DELLOOBJS)
