# ref
Show example usage of a given command, for quick reference<br>
The program's action is affected by the config file under `~/.config/ref/config` if it exist.<br>

# HOWTOS
Makefiles is under `build` directory.<br>
1. change to `build` directory, and then use `make`, choose a target, for example, `arch64r`<br>
![](https://raw.githubusercontent.com/charlie-wong/ref/master/prtsc/ref-make.png "Choose a target to build")
2. `$ make arch64r` to make, and will show a prompt to ask do you want to install?<br>
![](https://raw.githubusercontent.com/charlie-wong/ref/master/prtsc/ref-build-install.png "Build & Install")
3. `$ make uninstall` to completely remove it!<br>
![](https://raw.githubusercontent.com/charlie-wong/ref/master/prtsc/ref-uninstall.png "Uninstall")
###### tips:
  1. For ubuntu, make sure you know the root passwd, because i install it at `/opt/ref`, which a root passwd required. 
     If you want, you can change the Makefiles in `build` to install at another location.<br>
  2. For debian, the `sudo` must work.<br>
  3. If you have any questions, you can contact with me by email, all welcome!<br>


# PrintScreen
## ubuntu
Example: `$ ref ls`<br>
![](https://raw.githubusercontent.com/charlie-wong/ref/master/prtsc/ref-ls.png "Example: $ ref ls")<br>
Example: `$ ref scp ls`<br>
![](https://raw.githubusercontent.com/charlie-wong/ref/master/prtsc/ref-scp-ls.png "Example: $ ref scp ls")<br>

## debian
Example: `$ ref -v ls`<br>
![](https://raw.githubusercontent.com/charlie-wong/ref/master/prtsc/ref-debian.png "Example: $ ref -v ls")<br>

