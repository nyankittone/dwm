# nyankittone's dwm fork
[dwm](https://dwm.suckless.org/) is an extremely minimal and fast dynamic tiling window manager for
X11, made by Suckless.

This repo contains my own "fork" of dwm that I use on my desktop PC every day, containing all of
the patches I use. I have quite a few patches applied to it, and I plan on adding more of them,
and removing some that I don't find valuable, in the future.

## Included patches
In order of application, they are:
* [attachbottom](https://dwm.suckless.org/patches/attachbottom/)
* [cfacts](https://dwm.suckless.org/patches/cfacts/)
* A custom patch for moving windows up and down the stack with keybinds
* [keychord](https://dwm.suckless.org/patches/keychord/)
* [bottomstack](https://dwm.suckless.org/patches/bottomstack/)
* [centeredmaster](https://dwm.suckless.org/patches/centeredmaster/)
* [pertag](https://dwm.suckless.org/patches/pertag/)
* [alwayscenter](https://dwm.suckless.org/patches/alwayscenter/)
* [cursorwarp](https://dwm.suckless.org/patches/cursorwarp/) (modified so that the cursor can warp to a monitor even if there's no clients there)
* [systray](https://dwm.suckless.org/patches/systray/)
* [statusallmons](https://dwm.suckless.org/patches/statusallmons/)

Note that there are also extra custom patches added for the extra layouts added, so that they can
be compatible with the cfacts patch. cfacts support for the bstack and bstackhoriz layouts works
fine. Support for the centeredmaster layout is buggy right now.

In the future, I'm considering adding the ipc patch and some other patches for handling fullscreen
windows batter, since I may benefit from those additions for my workflow. I also want to add a
toggle for having new clients attach to either the top or the bottom of the window ordering.

## Default keybinds
This version of `dwm` has quite a few things changed from the defaults, and a lot of new keybinds
added. This version also includes the keychord patch, which allows for a sequence of keys to be
pressed to trigger something, instead of just a single key combination.

In the table below, individual combos in a key sequence are separated with a "->". Individual keys
in a key combo are separated with a "+".

Note that the "modkey" in the table is the Super key (Windows key), instead of Alt like it is in
vanilla `dwm`.

|Key sequence       |Description                                  |Default command run    |
|:------------------|:--------------------------------------------|:----------------------|
|modkey+Enter       |Spawn a new terminal (st)                    |`st`                   |
|modkey+b           |Toggle bar for the focused monitor           |N/A                    |
|modkey+j           |Focus the window 1 space down the stack      |N/A                    |
|modkey+k           |Focus the window 1 space up the stack        |N/A                    |
|modkey+y           |Increase windows in the master area by 1     |N/A                    |
|modkey+n           |Decrease windows in the master area by 1     |N/A                    |
|modkey+h           |Decrease width of the master area (mfact)    |N/A                    |
|modkey+l           |Increase width of the master area (mfact)    |N/A                    |
|modkey+Shift+Enter |Move focused window to the top of the stack  |N/A                    |
|modkey+Tab         |View the previously viewed tagset            |N/A                    |
|modkey+Shift+c     |Close the focused window                     |N/A                    |
|modkey+t           |Use the `tile` layout                        |N/A                    |
|modkey+f           |Use no tiling layout (float the windows)     |N/A                    |
|modkey+Space       |Use the last active tiling layout            |N/A                    |
|modkey+e           |Use the `monocle` layout                     |N/A                    |
|modkey+i           |Use the `bstack` layout                      |N/A                    |
|modkey+u           |Use the `bstackhoriz` layout                 |N/A                    |
|modkey+w           |Use the `centeredmaster` layout              |N/A                    |
|modkey+Shift+Space |Toggle f the focused window is tiled or not  |N/A                    |
|modkey+0           |Select all tags for focused monitor          |N/A                    |
|modkey+Shift+0     |Add focused client to all tags               |N/A                    |
|modkey+Comma       |Focus to the monitor to the left             |N/A                    |
|modkey+Period      |Focus to the monitor to the right            |N/A                    |
|modkey+Shift+Comma |Move focused window to the left-most monitor |N/A                    |
|modkey+Shift+Period|Move focused window to the right-most monitor|N/A                    |
|modkey+[1-9]       |Select tag of typed number for monitor       |N/A                    |
|modkey+Ctrl+[1-9]  |Toggle tag of typed number for monitor       |N/A                    |
|modkey+Shift+[1-9] |Move focused window to tag of typed number   |N/A                    |
|modkey+Ctrl+Shift+[1-9]|Toggle tag of typed number for focused window|N/A                |
|modkey+Shift+h     |Decrease focused window's cfact value        |N/A                    |
|modkey+Shift+l     |Increase focused window's cfact value        |N/A                    |
|modkey+Shift+o     |Reset focused window's cfact value           |N/A                    |
|modkey+Shift+j     |Move focused window down the stack by 1      |N/A                    |
|modkey+Shift+k     |Move focused window up the stack by 1        |N/A                    |
|modkey+Shift+q -> q|"Restart" dwm in-place (See [Running dwm](#running-dwm))   |N/A      |
|modkey+Shift+q -> w|Stop dwm                                     |N/A                    |
|modkey+Shift+q -> s|Suspend the system                           |`systemctl suspend`    |
|modkey+Shift+q -> h|Hibernate the system                         |`systemctl hibernate`  |
|modkey+Shift+q -> r|Reboot the system                            |`reboot`               |
|modkey+Shift+q -> p|Power off the system                         |`poweroff`             |
|modkey+Shift+q -> l|Lock the system via `xscreensaver`           |`xscreensaver-command --activate`|
|modkey+c           |Run a shell command                          |`rofi -show run`       |
|modkey+x           |Launch an application                        |`rofi -show drun`      |
|modkey+s           |Launch Steam                                 |`steam`                |
|modkey+d           |Launch Discord                               |`flatpak run dev.vencord.Vesktop`|
|modkey+g           |Launch GIMP                                  |`flatpak run org.gimp.GIMP`|
|modkey+z           |Launch Zen Browser                           |`flatpak run app.zen_browser.zen`|
|modkey+m           |Launch Prism Launcher                        |`flatpak run org.prismlauncher.PrismLauncher`|
|modkey+Equals or VolumeUp|Increase volume by 5%                        |`pactl set-sink-volume @DEFAULT_SINK@ +5%`|
|modkey+Shift+Equals or Shift+VolumeUp|Increase volume by 1%                        |`pactl set-sink-volume @DEFAULT_SINK@ +1%`|
|modkey+Minus or VolumeDown|Decrease volume by 5%                        |`pactl set-sink-volume @DEFAULT_SINK@ -5%`|
|modkey+Shift+Minus or Shift+VolumeDown|Decrease volume by 1%                        |`pactl set-sink-volume @DEFAULT_SINK@ -1%`|
|AudioMute        |Toggle if audio is muted                     |`pactl set-sink-mute @DEFAULT_SINK@ toggle`|
|AudioMedia or AudioPlay|Toggle music player                    |`playerctl play-pause`   |
|AudioPrev        |Play previous song                           |`playerctl previous`     |
|AudioNext        |Play next song                               |`playerctl next`         |
|modkey+Ctrl+d    |Open browser tab showing the Dow Jones       |`xdg-open https://duckduckgo.com/?t=ffab&q=dow+jones&ia=web`|

## Requirements
In order to build dwm, you will need the Xlib header files.

On Debian or a Debian-based Linux distro, these can be installed with:

    sudo apt install xorg-dev

On Arch Linux and similar:

    sudo pacman -S libx11

The default configuration of this `dwm` has dependencies on PulseAudio and some of its userspace
programs like `pactl`. If you don't use PulseAudio, you'll want to adjust the config.h accordingly.

## Installation
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default). On most Linux distros, the default `config.mk` should work
fine as-is.

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install

This fork of dwm contains custom makefile rules that allow installing it for only your current
user. To do so, run the following instead:

    make localinstall

or:

    make l

Doing this means that you won't need root privileges to install `dwm`. However, dwm's manpages
will not be installed if you choose to do this.

## Running dwm
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

This version of `dwm` supports allowing the shell running the .xinitrc script to restart it in-place
based on what exit code is returned. By default, the exit code signaling a restart is 2. To take
advantage of this, you can write something like this at the end of your .xinitrc:

    while true; do
        dwm
        case $? in
            2) continue;;
            *) exit;;
        esac
    done

This will run dwm in a loop until it exits with anything that isn't a 2. Note that the `exec`
keyword is not included, as we don't want the shell to exit right after finishing running `dwm`.

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm


## Configuration
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
