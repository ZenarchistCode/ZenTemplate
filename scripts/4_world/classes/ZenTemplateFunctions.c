class ZenTemplateFunctions
{
	//! Debug message - sends a server-side player message to all online players
	static void SendGlobalMessage(string msg)
	{
		SendGlobalMessageEx(msg, "[SERVER] ");
	}

	//! Debug message - sends a server-side player message to all online players
	static void SendGlobalMessageEx(string msg, string prefix = "")
	{
		#ifdef SERVER
		array<Man> players = new array<Man>;
		GetGame().GetWorld().GetPlayerList(players);
		for (int x = 0; x < players.Count(); x++)
		{
			PlayerBase pb = PlayerBase.Cast(players.Get(x));
			if (pb)
			{
				SendPlayerMessage(pb, prefix + msg);
			}
		}
		#endif
	}

	//! Display client message ONLY on client
	static void ZenClientMessage(string message)
	{
#ifndef SERVER
		if (GetGame().GetPlayer())
		{
			GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(CCDirect, "", message, ""));
		}
#endif
	}

	//! Print a debug chat message both client-side & server-side
	static void DebugMessage(string message)
	{
		ZenClientMessage("[CLIENT] " + message);
		SendGlobalMessage(message);
	}

	//! Send a message to the given player
	static void SendPlayerMessage(PlayerBase player, string msg)
	{
#ifdef SERVER
		if (msg == "" || msg == string.Empty)
			return;

		if (!player || player.IsPlayerDisconnected() || !player.GetIdentity())
			return;

		Param1<string> m_MessageParam = new Param1<string>("");
		if (m_MessageParam && msg != "")
		{
			m_MessageParam.param1 = msg;
			GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, m_MessageParam, true, player.GetIdentity());
		}
#endif
	}

	//! Enable/disable player controls - WARNING: This function does not check if controls should be enabled given what the player is doing at the time when it's called, so use carefully and thoughtfully
	static void SetPlayerControl(bool isEnabled = true, bool hideHud = false)
	{
		if (!GetGame().IsClient())
			return;

		if (isEnabled)
		{
			GetGame().GetMission().AddActiveInputExcludes({"menu"});

			if (hideHud)
				GetGame().GetMission().GetHud().Show(true);
		}
		else
		{
			GetGame().GetMission().RemoveActiveInputExcludes({"menu"});

			if (hideHud)
				GetGame().GetMission().GetHud().Show(false);
		}
	}

	static void EnablePlayerControl()
	{
		SetPlayerControl(true, false);
	}

	static void DisablePlayerControl()
	{
		SetPlayerControl(false, false);
	}
}