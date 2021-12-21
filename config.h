/* See LICENSE file for copyright an0od license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 3;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int minwsz    = 20;       /* Minimal heigt of a client for smfact */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "monospace:size=10", "fontawesome:size=11" };
static const char dmenufont[]       = "monospace:size=10";

// background color
static const char col_gray1[]       = "#0A050E";
// inactive window border color
static const char col_gray2[]       = "#668c9a";
// font color
static const char col_gray3[]       = "#92c9dd";
// current tag and current window font color
static const char col_gray4[]       = "#92c9dd";
// tob bar second color and active window border color
static const char col_cyan[]        = "#0759A4";

static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeStatus]  = { col_gray3, col_gray1,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { col_gray4, col_cyan,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { col_gray3, col_gray1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { col_gray4, col_cyan,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { col_gray3, col_gray1,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

static const char *const autostart[] = {
	"wal", "-R", NULL,
	"kitty", "--title", "cmus", "cmus", NULL,
	"kitty", "--title", "terminal", NULL,
	"pulseaudio", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Chromium", "chromium", NULL, 1, 0, -1 },
	{ "discord",  "discord", NULL, 2, 0, -1 },
	{ "Terminator",  "terminator", NULL, 1 << 9, 0, -1 },
	{ NULL, NULL, "terminal", 1 << 2, 0, -1},
	{ "kitty",  "kitty", NULL, 1 << 9, 0, -1 },	
	{ NULL, NULL, "cmus", 1 << 3, 0, -1},
	{ "SevTech Ages", "SevTech Ages", "SevTech Ages", 1 << 5, 0, -1},
	{ "Minecraft 1.8.9",  "Minecraft 1.8.9", NULL, 1 << 5, 0, -1 },

	{ "Minecraft* 1.17.1",  "Minecraft* 1.17.1", NULL, 1 << 5, 0, -1 },
	
	{ "civilizationvi.exe",  "civilizationvi.exe", NULL, 1 << 5, 0, -1 },
	{ "doomx64vk.exe",  "doomx64vk.exe", NULL, 1 << 5, 0, -1 },
	{ "borderlands3.exe",  "borderlands3.exe", NULL, 1 << 5, 0, -1 },
	{ "civilizationvi.exe",  "civilizationvi.exe", NULL, 1 << 5, 0, -1 },
	{ "Lutris",  "lutris", NULL, 1 << 4, 0, -1 },
	{ "MultiMC5",  "multimc", NULL, 1 << 4, 0, -1 },
	{ "steam_app_960090",  "steam_app_960090", NULL, 1 << 5, 0, -1 },
	{ "Steam",  "Steam", NULL, 1 << 4, 0, -1 },
	{ "Kodi",  "Kodi", NULL, 1 << 4, 0, -1 },
	{ "steam_app_252950",  "steam_app_252950", NULL, 1 << 5, 0, -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const float smfact     = 0.00; /* factor of tiled clients [0.00..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod4Mask
#define MODKEY2 Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-hp", "chromium,discord,firefox,kitty,vscodium,nomacs,steam,multimc,flameshot", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *flameshot[] = {"flameshot", "gui", NULL};
static const char *cmusplaypause[] = {"playerctl", "--player=cmus", "play-pause", NULL};
static const char *cmusnext[] = {"playerctl", "--player=cmus", "next", NULL};
static const char *cmusprevious[] = {"playerctl", "--player=cmus", "previous", NULL};
static const char *betterlockscreen[] = {"betterlockscreen", "-l", NULL};
static const char *suspend[] = {"systemctl", "suspend", NULL};
static const char *volup [] = {"pactl", "set-sink-volume", "1", "+5%", NULL};
static const char *voldown[] = {"pactl", "set-sink-volume", "1", "-5%", NULL};
static const char *shutdown[] = {"prompt", "Do you want to shutdown?", "sudo shutdown -h now", NULL};


#include </root/skyblue-dwm/shiftview.c>
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_p,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Tab,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Tab,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setsmfact,      {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setsmfact,      {.f = -0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	//{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,		XK_o,	   spawn,	{.v = shutdown} },
	{ MODKEY,             		XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },

	{ MODKEY2,                      XK_space,  setlayout,      {0} },
	{ MODKEY2|ShiftMask,            XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	//{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	//{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	//{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY2|ShiftMask,            XK_Tab,    shiftview,      {.i = -1 } },
	{ MODKEY2,             		XK_Tab,	   shiftview,      {.i = +1 } },
	{ NULL,				XK_Print,  spawn,	   {.v = flameshot } },
	{ ControlMask|ShiftMask,	XK_x,	   spawn,		{.v = cmusplaypause } },
	{ ControlMask|ShiftMask,	XK_b,	   spawn,		{.v = cmusnext } },
	{ ControlMask|ShiftMask,	XK_n,	   spawn,		{.v = cmusprevious } },
	{ MODKEY,			XK_apostrophe,	   spawn,	{.v = suspend } },
	{ MODKEY,			XK_semicolon,	   spawn,	{.v = betterlockscreen } },
	{ ControlMask|ShiftMask,        XK_space,  togglealwaysontop, {0} },
	{ MODKEY,			XK_equal,   spawn,		{.v = volup } },
	{ MODKEY,			XK_minus,   spawn,		{.v = voldown } },
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
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

