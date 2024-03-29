# My build of dwm

dwm is an extremely fast, small, and dynamic window manager for X.

## Patches and features
 
- actualfullscreen
- alwayscenter
- attachaside
- cfacts
- fakefullscreen
- fibonacci
- fullgaps
- fullscreen
- hide_vacant_tags
- noborderfloatingfix
- notitle
- pertag
- restartsig
- scratchpad
- stacker
- status2d
- swallow

## Requirements

In order to build dwm you need the `Xlib` and `libxft-bgra` header files.

# Installation
```
git clone https://github.com/BishrGhalil/dwm
cd dwm
sudo make install
```

Add the following line to your .xinitrc to start dwm using startx:

```
exec dwm
```

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

```
DISPLAY=foo.bar:1 exec dwm
```

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:
```
    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm
```

## Keybinding
- SUPER + n - `next workspace`
- SUPER + p - `prev workspace`
- SUPER + [1...9] - `workspace number n`
- SUPER + b - `toggle status bar`
- SUPER + c - `increase master's windows number`
- SUPER + d - `decrease master's windows number`
- SUPER + h - `increase window's width`
- SUPER + l - `decrease window's width`
- SUPER + t - `set Tile layout`
- SUPER + y - `set Fibo layout`
- SUPER + y - `set Float layout`
- SUPER + y - `set Float layout`
- SUPER + [ - `set Float layout`
- SUPER + shift + h - `increase window's high`
- SUPER + shift + l - `decrease window's high`
- SUPER + shift + o - `reset window's high`
- SUPER + shift + f - `fullscreen`
 
## Configuration

The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
