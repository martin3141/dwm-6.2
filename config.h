/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "DejaVu sans Mono:pixelsize=14:antialias=true:autohint=true" };
static const char dmenufont[]       = "DejaVu sans Mono:pixelsize=14:antialias=true:autohint=true";
static const char col_bg[]          = "#1d2021";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_blue[]        = "#83a598";
static const char col_blue2[]       = "#076678";
static const char col_red[]         = "#fb4934";
static const char *colors[][3]      = {
	/*               fg        bg       border   */
	[SchemeNorm] = { col_blue, col_bg,  col_gray2 },
	[SchemeSel]  = { col_red,  col_bg,  col_blue  },

	//[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	//[SchemeSel]  = { col_gray4, col_blue2, col_blue2 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const char fsl[]   = "FSL 6.0.1";
static const char feat[]  = "FEAT - FMRI Expert Analysis Tool v6.00";
static const char ssvnc[] = "SSL/SSH VNC Viewer";
static const char np[]    = "notepad";
static const char sp[]    = "spant_plot";
static const char pv[]    = "Pavucontrol";

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance     title  tags mask  iscentered  isfloat  monitor */
	{ "Gimp",     NULL,        NULL,  0,         0,          1,            -1 },
	{ NULL,       "afni",      NULL,  0,         0,          1,            -1 },
	{ NULL,       "AFNI",      NULL,  0,         0,          1,            -1 },
	{ "Firefox",  NULL,        NULL,  1 << 1,    0,          0,            -1 },
	{ NULL,       NULL,         fsl,  0,         1,          1,            -1 },
	{ NULL,       NULL,        feat,  0,         1,          1,            -1 },
	{ NULL,       "r_x11",     NULL,  0,         0,          1,            -1 },
	{ NULL,       NULL,        "calc",0,         0,          1,            -1 },
	{ NULL,       NULL,        np,    0,         0,          1,            -1 },
	{ NULL,       "rstudio",   NULL,  1 << 2,    0,          0,            -1 },
	{ NULL,       NULL,        ssvnc, 1 << 7,    1,          1,            -1 },
	{ NULL,       "ssvnc.tcl", NULL,  1 << 7,    1,          1,            -1 },
	{ NULL,       "vncviewer", NULL,  1 << 7,    1,          1,            -1 },
	{ "Spotify",  NULL,        NULL,  1 << 8,    0,          0,            -1 },
	{ "Skype",    NULL,        NULL,  1 << 6,    1,          1,            -1 },
	{ sp,         NULL,        NULL,  0,         1,          1,            -1 },
	{ pv,         NULL,        NULL,  0,         1,          1,            -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]    = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg, "-nf", col_gray3, "-sb", col_blue, "-sf", col_gray4, NULL };
static const char *termcmdtm[]   = { "/home/martin/bin/sttm", NULL };
static const char *termcmd[]     = { "/home/martin/bin/st", NULL };
static const char *calccmd[]     = { "/home/martin/bin/calculator", NULL };
static const char *npcmd[]       = { "/home/martin/bin/notepad", NULL };
static const char *browsecmd[]   = { "firefox", NULL };
static const char *spotifycmd[]  = { "spotify", NULL };
static const char *rcmd[]        = { "rstudio-bin", NULL };
static const char *playcmd[]     = { "playerctl", "play-pause", NULL };
static const char *stopcmd[]     = { "playerctl", "stop", NULL };
static const char *nextcmd[]     = { "playerctl", "next", NULL };
static const char *prevcmd[]     = { "playerctl", "previous", NULL };
static const char *brightupcmd[] = { "xbacklight", "-inc", "10", NULL };
static const char *brightdncmd[] = { "xbacklight", "-dec", "10", NULL };

static Key keys[] = {
	/* modifier                  key          function        argument */
	{ MODKEY,                    XK_p,        spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,          XK_Return,   spawn,          {.v = termcmd } },
	{ MODKEY,                    XK_s,        spawn,          {.v = termcmd } },
	{ MODKEY,                    XK_w,        spawn,          {.v = browsecmd } },
	{ MODKEY,                    XK_a,        spawn,          {.v = spotifycmd } },
	{ MODKEY,                    XK_r,        spawn,          {.v = rcmd } },
	{ MODKEY,                    XK_c,        spawn,          {.v = calccmd } },
	{ MODKEY,                    XK_n,        spawn,          {.v = npcmd } },
	{ 0,                         0x1008ff14,  spawn,          {.v = playcmd } },
	{ 0,                         0x1008ff15,  spawn,          {.v = stopcmd } },
	{ 0,                         0x1008ff16,  spawn,          {.v = prevcmd } },
	{ 0,                         0x1008ff17,  spawn,          {.v = nextcmd } },
	{ 0,                         0x1008ff02,  spawn,          {.v = brightupcmd } },
	{ 0,                         0x1008ff03,  spawn,          {.v = brightdncmd } },
	{ MODKEY,                    XK_b,        togglebar,      {0} },
	{ MODKEY,                    XK_j,        focusstack,     {.i = +1 } },
	{ MODKEY,                    XK_k,        focusstack,     {.i = -1 } },
	{ MODKEY,                    XK_i,        incnmaster,     {.i = +1 } },
	{ MODKEY,                    XK_d,        incnmaster,     {.i = -1 } },
	{ MODKEY,                    XK_h,        setmfact,       {.f = -0.05} },
	{ MODKEY,                    XK_l,        setmfact,       {.f = +0.05} },
	{ MODKEY,                    XK_Return,   zoom,           {0} },
	{ MODKEY,                    XK_Tab,      view,           {0} },
	{ MODKEY|ShiftMask,          XK_q,        killclient,     {0} },
	{ MODKEY,                    XK_t,        setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                    XK_f,        setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                    XK_m,        setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                    XK_space,    setlayout,      {0} },
	{ MODKEY|ShiftMask,          XK_space,    togglefloating, {0} },
	{ MODKEY,                    XK_0,        view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,          XK_0,        tag,            {.ui = ~0 } },
	{ MODKEY,                    XK_comma,    focusmon,       {.i = -1 } },
	{ MODKEY,                    XK_period,   focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,          XK_comma,    tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,          XK_period,   tagmon,         {.i = +1 } },
	TAGKEYS(                     XK_w,                        1) // firefox
	TAGKEYS(                     XK_r,                        2) // rstudio
	TAGKEYS(                     XK_a,                        8) // spotify
	TAGKEYS(                     XK_1,                        0)
	TAGKEYS(                     XK_2,                        1)
	TAGKEYS(                     XK_3,                        2)
	TAGKEYS(                     XK_4,                        3)
	TAGKEYS(                     XK_5,                        4)
	TAGKEYS(                     XK_6,                        5)
	TAGKEYS(                     XK_7,                        6)
	TAGKEYS(                     XK_8,                        7)
	TAGKEYS(                     XK_9,                        8)
	{ MODKEY|ShiftMask,          XK_e,        quit,           {0} },
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

