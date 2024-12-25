/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 9;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
// static const char *fonts[]          = { "FiraCode Nerd Font Mono:size=12" };
static const char *fonts[]          = { "FiraCode Nerd Font:size=10" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=10";
//background color
static const char col_gray1[]       = "#292522";
//inactive windows border color
static const char col_gray2[]       = "#ECE1D7";
//font color
static const char col_gray3[]       = "#ECE1D7";
//current tag and current window font color
static const char col_gray4[]       = "#E49B5D";
//topbar second color and active window border color
static const char col_cyan[]        = "#34302C";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
// static const char *tags[] = { "", "", "", "", "", "", ""};
static const char *tags[] = { "1. code", "2. code", "3. web", "4. web", "5. mail", "6. doc", "7. chat"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Chromium",     NULL,       NULL,       1 << 3,            0,           -1 },
	{ "mpv",  NULL,       NULL,       1 << 5,       0,           -1 },
	{ "firefox",  NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Slack",  NULL,       NULL,       1 << 6,       0,           -1 },
	{ "Viber",  NULL,       NULL,       1 << 6,       0,           -1 },
	{ "google-chrome",  NULL,       NULL,       1 << 2,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#include <X11/XF86keysym.h>
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static const char *rofid[]     = { "rofi", "-show", "drun", "-show-icons", "-font JetBrainsMono Nerd Font 10", NULL };
static const char *rofi[]     = { "rofi", "-show", "run", "-font JetBrainsMono Nerd Font 10", NULL };
static const char *rofis[]     = { "rofi", "-show", "ssh", "-font JetBrainsMono Nerd Font 10", NULL };
// static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
// static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "wezterm", NULL };
static const char *flameshot[] = { "flameshot", "gui", NULL };
static const char *extmonitor[] = { "sb-monitor",NULL };
static const char *rofipass[] = { "rofipass", "gui", NULL };
static const char *sblock[] = { "sb-lock", NULL };
static const char *sbshutdown[] = { "sb-shutdown", NULL };
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = rofid } },
	{ MODKEY,                       XK_d,      spawn,          {.v = rofi } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = rofis } },
	{ MODKEY|ShiftMask,             XK_x,      spawn,          {.v = sblock } },
	{ MODKEY|ControlMask,           XK_x,      spawn,          {.v = sbshutdown } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = rofipass } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = extmonitor } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	// { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ 0,                            XF86XK_AudioMute,           spawn,          SHCMD("pactl set-sink-mute 0 toggle") },
	{ 0,                            XF86XK_AudioLowerVolume,    spawn,          SHCMD("pactl set-sink-volume 0 -3%") },
        { 0,                            XF86XK_AudioRaiseVolume,    spawn,          SHCMD("pactl set-sink-volume 0 +3%") },
        { 0,                            XF86XK_MonBrightnessUp,     spawn,          SHCMD("brightnessctl g +5%") },
        { 0,                            XF86XK_MonBrightnessDown,   spawn,          SHCMD("brightnessctl g 5%-") },
        { 0,                            XK_Print,                   spawn,          {.v = flameshot} },
        { 0,                            XK_ISO_Next_Group,          spawn,          SHCMD("pkill -RTMIN+10 dwmblocks") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
        { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	// { ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	// { ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	// { ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

