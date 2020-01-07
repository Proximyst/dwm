/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 0;        /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "Source Code Pro for Powerline:size=10", "Hack:size=10", "monospace:size=10" };
static const char dmenufont[]       = "Source Code Pro for Powerline:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#282828";
static const char col_gray3[]       = "#8c8c8c";
static const char col_gray4[]       = "#eeeeee";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray2, NULL  },
	[SchemeSel]  = { col_gray3, col_gray2, NULL },
};

/* tagging                     1     2     3     4     5     6     7     8     9*/
static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class 			    instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     			NULL,       NULL,       0,            1,           -1 },
	{ "firefox",  			NULL,       NULL,       1 << 0,       0,           -1 },
	{ "discord",  	 		NULL,       NULL,       1 << 1,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol        arrange function */
	{ "タイル",        tile }, /* first entry is default */
	{ "フロート",      NULL }, /* no layout function means floating behavior */
	{ "モノクル",      monocle },
};

/* key definitions */
// Mod4Mask: Super/"Windows" key
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/bash", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
// I prefer having the command around just in case.
//static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_gray2, "-sf", col_gray4, NULL };
static const char dmenuInvoke[] = "dmenu -i -fn 'Source Code Pro for Powerline:size=10' -m 0 -nb '#222222' -nf '#8c8c8c' -sb '#282828' -sf '#eeeeee'";
static const char *dmenucmd[] = { "j4-dmenu-desktop", "--dmenu", dmenuInvoke, NULL };
static const char *termcmd[]  = { "alacritty", "--working-directory", "/home/proximyst/", NULL };
static const char *owocmd[]   = { "herbstscrot", NULL };

static const char *voltogg[] = { "pamixer", "-t", NULL };
static const char *volincr[] = { "pamixer", "-i", "1", NULL };
static const char *voldecr[] = { "pamixer", "-d", "1", NULL };
static const char *volincr5[] = { "pamixer", "-i", "5", NULL };
static const char *voldecr5[] = { "pamixer", "-d", "5", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ 0,                            XK_Print,  spawn,          {.v = owocmd} },

	{ 0, 				XF86XK_AudioMute, 			spawn, 		{ .v = voltogg } },
	{ 0, 				XF86XK_AudioRaiseVolume, 	spawn, 		{ .v = volincr5 } },
	{ 0, 				XF86XK_AudioLowerVolume, 	spawn, 		{ .v = voldecr5 } },
	{ ShiftMask, 		XF86XK_AudioRaiseVolume, 	spawn, 		{ .v = volincr } },
	{ ShiftMask,		XF86XK_AudioLowerVolume, 	spawn, 		{ .v = voldecr } },

	// As fullscreen within applications works as I've always imagined it
	// should, I see no reason in having a way to toggle the bar whatsoever.
//	{ MODKEY,                       XK_b,      togglebar,      {0} },

	// Navigation with vim-like keys.
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },

	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },

	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },

	// zoom = set as master.
	{ MODKEY,                       XK_z,      zoom,           {0} },

//	{ MODKEY,                       XK_Tab,    view,           {0} },

	// Kill the current window.
	{ MODKEY,                       XK_c,      killclient,     {0} },

	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
//	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	// I'm on a single-monitor set-up.
	// This can be revised later when I have a second.
//	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
//	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
//	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
//	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	// Exit dwm.
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
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

