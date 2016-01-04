# ref
Show example usage of a given command, for quick reference<br>
The program's action is affected by the config file under `~/.config/ref/config` if it exist.<br>

# Why do i use it?
Abviously, you must like linux and will play with it. <br>
I find the `man/info` is too waste time, if i forget how to use a command and want some help.<br>
This is what this program for: a quick reference, examples.<br>
But the `man/info` is the best place for detail information.<br>

# HOWTOS
Makefiles is under `build` directory.<br>
1. change to `build` directory, and then use `make`, choose a target, for example, `arch64r`<br>
![Missing Picture](https://raw.githubusercontent.com/charlie-wong/ref/master/prtsc/ref-make.png "Choose a target to build")<br>
2. `$ make arch64r` to make, and will show a prompt to ask: do you want to install?<br>
![Missing Picture](https://raw.githubusercontent.com/charlie-wong/ref/master/prtsc/ref-build-install.png "Build & Install")<br>
3. `$ make uninstall` to completely remove it!<br>
![Missing Picture](https://raw.githubusercontent.com/charlie-wong/ref/master/prtsc/ref-uninstall.png "Uninstall")<br>
###### tips:
  1. For ubuntu, make sure you know the root passwd, because i install it at `/opt/ref`, which a root passwd required. 
     If you want, you can change the Makefiles in `build` to install at another location.<br>
  2. For debian, the `sudo` must work.<br>
  3. The original `sheets` files is got from the ['cheat' project](https://github.com/chrisallenlane/cheat).
     I classify them into 9 part, match the 9 part of man.
     You can add files to `~/.config/ref/sheets/..`, then when you use `ref` to search, that file will be considered.
     For example:<br>
     - add `test` file to `~/.config/ref/sheets/1/en/`<br>
       `$ echo -e "#This is test\n usage examples" > ~/.config/ref/sheets/1/en/test`<br>
       `$ cat ~/.config/ref/sheets/1/en/test`<br>
       `$ ref test`<br>
       ![Missing Picture](https://raw.githubusercontent.com/charlie-wong/ref/master/prtsc/ref-user.png "Customize Personal Sheets")<br>
  4. The `sheets` always nees help, if you can, help it. If you find any questions of it, feel free to let me know.:smile::smirk:
  4. If you have any questions, you can contact with me by email, all welcome!<br>


# PrintScreen
## ubuntu
Example: `$ ref ls`<br>
![Missing Picture](https://raw.githubusercontent.com/charlie-wong/ref/master/prtsc/ref-ls.png "Example: $ ref ls")<br>
Example: `$ ref scp ls`<br>
![Missing Picture](https://raw.githubusercontent.com/charlie-wong/ref/master/prtsc/ref-scp-ls.png "Example: $ ref scp ls")<br>

## debian
Example: `$ ref -v ls`<br>
![Missing Picture](https://raw.githubusercontent.com/charlie-wong/ref/master/prtsc/ref-debian.png "Example: $ ref -v ls")<br>

