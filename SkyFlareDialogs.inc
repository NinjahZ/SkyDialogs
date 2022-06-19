#if defined inc_SkyFlareDialogs
	#endinput
#endif
#define _inc_SkyFlareDialogs

#if !defined isnull
    #define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

#define SkyDiag:%0(%1,%2,%3,%4) \
		forward skyd_%0_response(%1, %2, %3, %4); \
		public skyd_%0_response(%1, %2, %3, %4)

new Sky_Player_Dialog[MAX_PLAYERS] = {-1,...};

forward OnPlayerSkyDiagSpoofing(playerid, dialogid);

public OnPlayerConnect(playerid)
{
    Sky_Player_Dialog[playerid] = -1;
    #if defined SkyDiag_OnPlayerConnect
		return SkyDiag_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}
public OnPlayerDisconnect(playerid, reason)
{
	Sky_Player_Dialog[playerid] = -1;
	#if defined SkyDiag_OnPlayerDisconnect
		return SkyDiag_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(Sky_Player_Dialog[playerid] == dialogid)
	{
		if(!isnull(inputtext))
		{
			for(new i; i < strlen(inputtext); i++)
			{
				if(inputtext[i] == '%') inputtext[i] = '#';
			}
		}

		new dialog_name[32];
		format(dialog_name, 32, "skyd_%d_response", dialogid);
		if(funcidx(dialog_name) != -1) CallLocalFunction(dialog_name, "ddds", playerid, response, listitem, inputtext);
	}
	else CallLocalFunction("OnPlayerSkyDiagSpoofing", "ii", playerid, dialogid);

	#if defined SkyDiag_OnDialogResponse
		return SkyDiag_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}

public OnPlayerSkyDiagSpoofing(playerid, dialogid)
{
    Sky_Player_Dialog[playerid] = -1;
    #if defined SkyDiag_OnPlayerSkyDiagSpoofing
		return SkyDiag_OnPlayerSkyDiagSpoofing(playerid, dialogid);
	#else
		return 1;
	#endif
}

stock SkyDiag_ShowPlayerDialog(playerid, dialogid, style, const caption[], const info[], const button1[], const button2[])
{
	Sky_Player_Dialog[playerid] = dialogid;
	return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);
}

#if defined _ALS_ShowPlayerDialog
	#undef ShowPlayerDialog
#else
	#define _ALS_ShowPlayerDialog
#endif
#define ShowPlayerDialog SkyDiag_ShowPlayerDialog

#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif
#define OnDialogResponse Sky_OnDialogResponse
#if defined SkyDiag_OnDialogResponse
	forward SkyDiag_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect SkyDiag_OnPlayerDisconnect
#if defined SkyDiag_OnPlayerDisconnect
	forward SkyDiag_OnPlayerDisconnect(playerid, reason);
#endif

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect SkyDiag_OnPlayerConnect
#if defined SkyDiag_OnPlayerConnect
	forward SkyDiag_OnPlayerConnect(playerid);
#endif

#if defined _ALS_OnPlayerSkyDiagSpoofing
	#undef OnPlayerSkyDiagSpoofing
#else
	#define _ALS_OnPlayerSkyDiagSpoofing
#endif
#define OnPlayerSkyDiagSpoofing SkyDiag_OnPlayerSkyDiagSpoofing
#if defined SkyDiag_OnPlayerSkyDiagSpoofing
	forward SkyDiag_OnPlayerSkyDiagSpoofing(playerid, dialogid);
#endif
