.PHONY: help clean upvf version uninstall

help:
	@echo "arch32r   --> 32bit-release"
	@echo "arch32rs  --> 32bit-release-static"
	@echo "arch32d   --> 32bit-debug"
	@echo "arch64r   --> 64bit-release"
	@echo "arch64rs  --> 64bit-release-static"
	@echo "arch64d   --> 64bit-debug"

arch32r: upvf32
	make -f ./Makefile.32.release
	@echo "Do you want to install ?(y/n)"
	@read choice; if [ "$$choice" = "y" ];then make -f ./Makefile.32.release install;fi
	@echo "Done."
arch32rs: upvf32
	make -f ./Makefile.32.release.static
	@echo "Do you want to install ?(y/n)"
	@read choice; if [ "$$choice" = "y" ];then make -f ./Makefile.32.release.static install;fi
	@echo "Done."
arch32d: upvf32
	make -f ./Makefile.32.debug
arch64r: upvf64
	make -f ./Makefile.64.release
	@echo "Do you want to install ?(y/n)"
	@read choice; if [ "$$choice" = "y" ];then make -f ./Makefile.64.release install;fi
	@echo "Done."
arch64rs: upvf64
	make -f ./Makefile.64.release.static
	@echo "Do you want to install ?(y/n)"
	@read choice; if [ "$$choice" = "y" ];then make -f ./Makefile.64.release.static install;fi
	@echo "Done."
arch64d: upvf64
	make -f ./Makefile.64.debug

upvf32:
	make -f ./Makefile.32.upvf
	./upvf
upvf64:
	make -f ./Makefile.64.upvf
	./upvf

RM            = rm -f
PROG_HOME     = /opt/ref
TARGET_NAME   = ref
PREFIX_LINK   = /usr/local
BIN_LINK_DIR  = $(PREFIX_LINK)/bin
PROG_USR_DIR  = ~/.config/ref

uninstall:
	sudo $(RM) -r $(PROG_HOME)
	sudo $(RM) $(BIN_LINK_DIR)/$(TARGET_NAME)
	@echo "Do you want to delete all the data in '$(PROG_USR_DIR)' ?(y/n)"
	@read choice; if [ "$$choice" = "y" ];then $(RM) -r $(PROG_USR_DIR);fi
	@echo "Uninstall Done."	
clean:
	rm -f *.o ref upvf version
