/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 0;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int minwsz    = 20;       /* Minimal heigt of a client for smfact */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "SourceCodePro:size=10" };
static const char dmenufont[]       = "SourceCodePro:size=10";
// static const char col_gray1[]       = "#1a1b26";    // status bar bg
static const char col_gray1[]       = "#282a36";    // status bar bg
static const char col_gray2[]       = "#282a36";    // None selected window border
static const char col_gray3[]       = "#ff79c6";    // forground
static const char col_gray4[]       = "#282a36";    // window title fg
static const char col_cyan[]        = "#ffb86c";    // selected window border and title bg 
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	// { "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "st-256color",NULL,  NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "Tile",      tile },    /* first entry is default */
 	{ "Fibo",      spiral },
	{ "Float",      NULL },    /* no layout function means floating behavior */
	{ "Mono",      monocle },
 	{ "[\\]",     dwindle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_q,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_x,     ACTION##stack, {.i = -1 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* including shiftview */
#include "shiftview.c"
/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	//{ MODKEY|ShiftMask,             XK_Return, spawn,          SHCMD("dmenu_run -i -fn 'Source Code Pro:size=10' -nb '#1a1b2c' -nf '#f7768e' -sb '#ff9e64' -sf '#1a1b27'") },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          SHCMD("dmenu_run -i -fn 'Source Code Pro:size=10'") },
	{ MODKEY|ShiftMask,             XK_d, spawn,          SHCMD("rofi -show run") },
    { MODKEY|ControlMask,           XK_Return, spawn,          SHCMD("alacritty -e bash") },
    { MODKEY,                       XK_Return, spawn,          SHCMD("st -e zsh") },
	{ MODKEY|Mod1Mask,             XK_Return, spawn,  {.v = scratchpadcmd } },
    { MODKEY,                       XK_n,      shiftview,      { .i = +1 } },
	{ MODKEY,                       XK_p,      shiftview,      { .i = -1 } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY,                       XK_c,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	/* { MODKEY,                       XK_Return, zoom,           {0} }, */
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_x,      setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_z,      setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_i,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    /*                      MOD+ALT COMMANDS                     */
	{ MODKEY|Mod1Mask,              XK_s,      spawn,          SHCMD("maim ~/Pictures/ScreenShots/$(date +%s).png;notify-send -t 600 \"MAIM\" \"Captured.\"") },
	{ MODKEY|Mod1Mask,              XK_a,      spawn,          SHCMD("maim -i $(xdotool getactivewindow) | xclip -selection clipboard -t image/png;notify-send -t 600 \"MAIM\" \"Copied to cliboard.\"") },
    { MODKEY|Mod1Mask,              XK_f,      spawn,          SHCMD("st -e lf") },
    { MODKEY|Mod1Mask,              XK_b,      spawn,          SHCMD("firefox") },
    { MODKEY|Mod1Mask,              XK_p,      spawn,          SHCMD("st -e htop") },
    { MODKEY|Mod1Mask,              XK_m,      spawn,          SHCMD("st -e ncmpcpp-ueberzug") },
    { MODKEY|Mod1Mask,              XK_e,      spawn,          SHCMD("st -e neomutt") },
    { MODKEY|Mod1Mask,              XK_w,      spawn,          SHCMD("sxiv -t ~/wallpapers") },
    { MODKEY|Mod1Mask,              XK_v,      spawn,          SHCMD("~/Documents/Scripts/vpnconn") },
    { MODKEY|Mod1Mask,              XK_z,      spawn,          SHCMD("zathura") },
    /*                  MOD+SHIFT COMMANDS                      */
    { MODKEY|ShiftMask,             XK_i,      spawn,          SHCMD("amixer set Master 5%- && pkill -RTMIN+30 dwmblocks") },
    { MODKEY|ShiftMask,             XK_u,      spawn,          SHCMD("amixer set Master 5%+ && pkill -RTMIN+30 dwmblocks") },
    { MODKEY|ShiftMask,             XK_t,      spawn,          SHCMD("amixer set Master toggle && pkill -RTMIN+30 dwmblocks && notify-send -t 500 -u low \"VOLUME TOGGLED\"") },
	{ ShiftMask|Mod1Mask,	        XK_m,	    spawn,		   SHCMD("mpc toggle; notify-send -t 500 \"MPC\" \"TOGGLED\"") },
	{ MODKEY,        			    XK_bracketleft,spawn,	   SHCMD("mpc seek -10") },
	{ MODKEY|ShiftMask,		        XK_bracketleft,spawn,	   SHCMD("mpc seek -60") },
	{ MODKEY,                       XK_bracketright,	spawn, SHCMD("mpc seek +10") },
	{ ShiftMask|ControlMask,        XK_period,	        spawn, SHCMD("mpc next && notify-send -u normal -t 1000 \"MPC\" \"$(mpc | sed -n 1p)\"") },
	{ ShiftMask|ControlMask,        XK_comma,	        spawn, SHCMD("mpc prev && notify-send -u normal -t 1000 \"MPC\" \"$(mpc | sed -n 1p)\"") },
	{ ShiftMask|Mod1Mask,           XK_i,	            spawn, SHCMD("mpc volume -10 && notify-send -t 500 -u low \"MPC\" \"$(mpc | sed -n 3p | awk '{print $1$2}')\"") },
	{ ShiftMask|Mod1Mask,           XK_u,	            spawn, SHCMD("mpc volume +10 && notify-send -t 500 -u low \"MPC\" \"$(mpc | sed -n 3p | awk '{print $1$2}')\"") },
	{ MODKEY|ShiftMask,		        XK_bracketright,	spawn, SHCMD("mpc seek +60") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,               quit,        {0} },
	{ MODKEY|ShiftMask,            XK_r,      quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkTagBar,            0,              Button4,        shiftview,     { .i = -1 } },
	{ ClkTagBar,            0,              Button5,        shiftview,     { .i = +1 } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

