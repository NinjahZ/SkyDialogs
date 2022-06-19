# SkyDialogs
### Simple and Sweet Dialog Processor to split Dialog's into a modular state.

## Usage

### Example Script:

```pawn
#include <SkyFlareDialogs>
new SpoofAttempts[MAX_PLAYERS];
forward DelayedKick(playerid);
public DelayedKick(playerid)
{
    Kick(playerid);
    return 1;
}

public OnPlayerConnect(playerid)
{
	SpoofAttempts[playerid] = 0;
}

public OnPlayerRequestClass(playerid, classid)
{
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Hello there!", "Hello, world!", "Accept", "bye");
	return 1;
}

//This is a Modular Dialog Response Section to break up SkyDiag_OnDialogResponse Length, you could in theory put these in seperate code files and include them.
SkyDiag:0(playerid, response, listitem, inputtext[])
{
	if(!response) return 0;
	else ShowPlayerDialog(playerid, 1, DIALOG_STYLE_MSGBOX, "responses!", "Replied!!!", "Accept", "bye");
	return 1;
}

public SkyDiag_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case 1:
		{
			if(!response) return 0;
			else ShowPlayerDialog(playerid, 2, DIALOG_STYLE_MSGBOX, "responses2!", "Replied again!!!", "Accept", "bye");
			return 1;
		}
		case 2:
		{
			if(!response) return 0;
			else ShowPlayerDialog(playerid, 3, DIALOG_STYLE_MSGBOX, "responses3!", "and again!!!", "Accept", "bye");
			return 1;
		}
	}
	return 1;
}

public OnPlayerSkyDiagSpoofing(playerid, dialogid)
{
	if(SpoofAttempts[playerid] != 3)
	{
		SendClientMessage(playerid, -1, "You have attempted to Spoof a Dialog, repeated attempts will get you kicked!");
		SpoofAttempts[playerid] ++;
		return 1;
	}
	else
	{
		SendClientMessage(playerid, -1, "You have been kicked for attempting to Spoof a Dialog!");
		SetTimerEx("DelayedKick", 1000, false, "i", playerid);
		return 1;
	}
    return 1;
}

```

## Installation

Place SkyFlareDialogs.inc inside \pawno\include
Refer to Example Script for Usage.
