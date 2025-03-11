/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 6;        /* border pixel of windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "ZedMono Nerd Font:size=26" };
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { "#b7bdf8", "#26273a", "#494d64" },
	[SchemeSel]  = { "#26273a", "#f5bde6",  "#f5bde6"  },
};

/* tagging. I might add a 9th tag again in the future tbh... */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ NULL,  NULL,       "Zen Browser",       1,       0,           0 },
	{ "vesktop",  NULL,       NULL,       2,       0,           1 },
	{ "discord",  NULL,       NULL,       2,       0,           1 },
	{ "steam",  NULL,       NULL,       4,       0,           1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG)                                                                                               \
       &((Keychord){1, {{MODKEY, KEY}},                                        view,           {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ControlMask, KEY}},                            toggleview,     {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ShiftMask, KEY}},                              tag,            {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ControlMask|ShiftMask, KEY}},                  toggletag,      {.ui = 1 << TAG} }),

/* helper for spawning commands without a shell. Usually preferred over SHCMD */
#define CMD(...) {.v = (const char*[]) {__VA_ARGS__, NULL}}

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* alias for the terminal emulator command */
static const char terminal[] = "st";

static const Keychord *keychords[] = {
	/* modifier                     key        function        argument */
	&((Keychord){1, {{MODKEY,             XK_Return}}, spawn,          CMD(terminal) }),
	&((Keychord){1, {{MODKEY,                       XK_b}},      togglebar,      {0} }),
	&((Keychord){1, {{MODKEY,                       XK_j}},      focusstack,     {.i = +1 } }),
	&((Keychord){1, {{MODKEY,                       XK_k}},      focusstack,     {.i = -1 } }),
	&((Keychord){1, {{MODKEY,                       XK_y}},      incnmaster,     {.i = +1 } }),
	&((Keychord){1, {{MODKEY,                       XK_n}},      incnmaster,     {.i = -1 } }),
	&((Keychord){1, {{MODKEY,                       XK_h}},      setmfact,       {.f = -0.05} }),
	&((Keychord){1, {{MODKEY,                       XK_l}},      setmfact,       {.f = +0.05} }),
	&((Keychord){1, {{MODKEY|ShiftMask,                       XK_Return}}, zoom,           {0} }),
	&((Keychord){1, {{MODKEY,                       XK_Tab}},    view,           {0} }),
	&((Keychord){1, {{MODKEY|ShiftMask,             XK_c}},      killclient,     {0} }),
	&((Keychord){1, {{MODKEY,                       XK_t}},      setlayout,      {.v = &layouts[0]} }),
	&((Keychord){1, {{MODKEY,                       XK_f}},      setlayout,      {.v = &layouts[1]} }),
	&((Keychord){1, {{MODKEY,                       XK_e}},      setlayout,      {.v = &layouts[2]} }),
	&((Keychord){1, {{MODKEY,                       XK_i}},      setlayout,      {.v = &layouts[3]} }),
	&((Keychord){1, {{MODKEY,                       XK_u}},      setlayout,      {.v = &layouts[4]} }),
	&((Keychord){1, {{MODKEY,                       XK_space}},  setlayout,      {0} }),
	&((Keychord){1, {{MODKEY|ShiftMask,             XK_space}},  togglefloating, {0} }),
	&((Keychord){1, {{MODKEY,                       XK_9}},      view,           {.ui = ~0 } }),
	&((Keychord){1, {{MODKEY|ShiftMask,             XK_0}},      tag,            {.ui = ~0 } }),
	&((Keychord){1, {{MODKEY,                       XK_comma}},  focusmon,       {.i = -1 } }),
	&((Keychord){1, {{MODKEY,                       XK_period}}, focusmon,       {.i = +1 } }),
	&((Keychord){1, {{MODKEY|ShiftMask,             XK_comma}},  tagmon,         {.i = -1 } }),
	&((Keychord){1, {{MODKEY|ShiftMask,             XK_period}}, tagmon,         {.i = +1 } }),
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)

	&((Keychord){1, {{MODKEY|ShiftMask,             XK_h}},      setcfact,       {.f = -0.25} }),
	&((Keychord){1, {{MODKEY|ShiftMask,             XK_l}},      setcfact,       {.f = +0.25} }),
	&((Keychord){1, {{MODKEY,             XK_o}},      setcfact,       {.f =  0.00} }),
    &((Keychord){1,{{MODKEY|ShiftMask, XK_j}}, pushstack, {.i = INC(+1)}}),
    &((Keychord){1,{{MODKEY|ShiftMask, XK_k}}, pushstack, {.i = INC(-1)}}),

    // Stuff relating to exiting dwm and power management control.
	&((Keychord){2, {{ MODKEY|ShiftMask, XK_q}, {0, XK_q}},      quit,           {.i = 2} }),
	&((Keychord){2, {{ MODKEY|ShiftMask, XK_q}, {0, XK_w}},      quit,           {.i = 0} }),
	&((Keychord){2, {{ MODKEY|ShiftMask, XK_q}, {0, XK_s}},      spawn,           CMD("systemctl", "suspend")}),
	&((Keychord){2, {{ MODKEY|ShiftMask, XK_q}, {0, XK_h}},      spawn,           CMD("systemctl", "hibernate") }),
	&((Keychord){2, {{ MODKEY|ShiftMask, XK_q}, {0, XK_r}},      spawn,           CMD("reboot") }),
	&((Keychord){2, {{ MODKEY|ShiftMask, XK_q}, {0, XK_p}},      spawn,           CMD("poweroff") }),
	&((Keychord){2, {{ MODKEY|ShiftMask, XK_q}, {0, XK_l}},      spawn,           CMD("xscreensaver-command", "--activate") }),

    // Keybinds for controlling rofi
    &((Keychord) {1, {{MODKEY, XK_c}}, spawn, CMD("rofi", "-show", "run")}),
    &((Keychord) {1, {{MODKEY, XK_x}}, spawn, CMD("rofi", "-show", "drun")}),

    // Keybinds for starting some common apps I use.
    &((Keychord) {1, {{MODKEY, XK_s}}, spawn, CMD("steam")}),
    &((Keychord) {1, {{MODKEY, XK_d}}, spawn, CMD("flatpak", "run", "dev.vencord.Vesktop")}),
    &((Keychord) {1, {{MODKEY, XK_g}}, spawn, CMD("flatpak", "run", "org.gimp.GIMP")}),
    &((Keychord) {1, {{MODKEY, XK_z}}, spawn, CMD("flatpak", "run", "app.zen_browser.zen")}),
    &((Keychord) {1, {{MODKEY, XK_m}}, spawn, CMD("flatpak", "run", "org.prismlauncher.PrismLauncher")}),

    // Keybinds for controlling the sound and music player
    &((Keychord) {1, {{MODKEY, XK_equal}}, spawn, CMD("pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%")}),
    &((Keychord) {1, {{MODKEY, XK_minus}}, spawn, CMD("pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%")}),
    &((Keychord) {1, {{MODKEY|ShiftMask, XK_equal}}, spawn, CMD("pactl", "set-sink-volume", "@DEFAULT_SINK@", "+1%")}),
    &((Keychord) {1, {{MODKEY|ShiftMask, XK_minus}}, spawn, CMD("pactl", "set-sink-volume", "@DEFAULT_SINK@", "-1%")}),
    &((Keychord) {1, {{0, XF86XK_AudioRaiseVolume}}, spawn, CMD("pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%")}),
    &((Keychord) {1, {{0, XF86XK_AudioLowerVolume}}, spawn, CMD("pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%")}),
    &((Keychord) {1, {{0|ShiftMask, XF86XK_AudioRaiseVolume}}, spawn, CMD("pactl", "set-sink-volume", "@DEFAULT_SINK@", "+1%")}),
    &((Keychord) {1, {{0|ShiftMask, XF86XK_AudioLowerVolume}}, spawn, CMD("pactl", "set-sink-volume", "@DEFAULT_SINK@", "-1%")}),
    &((Keychord) {1, {{0, XF86XK_AudioMute}}, spawn, CMD("pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle")}),
    &((Keychord) {1, {{0, XF86XK_AudioMedia}}, spawn, CMD("playerctl", "play-pause")}),
    &((Keychord) {1, {{0, XF86XK_AudioPlay}}, spawn, CMD("playerctl", "play-pause")}),
    &((Keychord) {1, {{0, XF86XK_AudioPrev}}, spawn, CMD("playerctl", "previous")}),
    &((Keychord) {1, {{0, XF86XK_AudioNext}}, spawn, CMD("playerctl", "next")}),

    // Keybind to check the Dow Jones Industrial Average, bc I enjoy watching the economy of my country die
    &((Keychord) {1, {{MODKEY|ControlMask, XK_d}}, spawn, CMD("xdg-open", "https://duckduckgo.com/?t=ffab&q=dow+jones&ia=web")}),
};
/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          CMD(terminal)},
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

