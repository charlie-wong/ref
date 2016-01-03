.PHONY: help clean

help:
	@echo "arch32r   32bit-release"
	@echo "arch32rs  32bit-release-static"
	@echo "arch32d   32bit-debug"
	@echo "arch64r   64bit-release"
	@echo "arch64rs  64bit-release-static"
	@echo "arch64d   64bit-debug"

arch32r:
	make -f ./Makefile.32.release
	@echo "Do you want to install ?(y/n)"
	@read choice; if [ "$$choice" = "y" ];then make -f ./Makefile.32.release install;fi
	@echo "Done."
arch32rs:
	make -f ./Makefile.32.release.static
	@echo "Do you want to install ?(y/n)"
	@read choice; if [ "$$choice" = "y" ];then make -f ./Makefile.32.release.static install;fi
	@echo "Done."
arch32d:
	make -f ./Makefile.32.debug
arch64r:
	make -f ./Makefile.64.release
	@echo "Do you want to install ?(y/n)"
	@read choice; if [ "$$choice" = "y" ];then make -f ./Makefile.64.release install;fi
	@echo "Done."
arch64rs:
	make -f ./Makefile.64.release.static
	@echo "Do you want to install ?(y/n)"
	@read choice; if [ "$$choice" = "y" ];then make -f ./Makefile.64.release.static install;fi
	@echo "Done."
arch64d:
	make -f ./Makefile.64.debug

clean:
	rm -f *.o ref
