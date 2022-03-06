dwmblocks &
picom &
sxhkd &
xwallpaper --zoom .config/wall.png &
xmodmap -e "clear Lock" -e "keycode 0x42 = Escape" &
bato.sh &
systemctl --user import-environment DISPLAY
