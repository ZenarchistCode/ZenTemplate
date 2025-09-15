// Server-side only code
modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();

		Print("[ZenTemplate] MissionServer::OnInit");

		// Load server-side config 
		GetZenTemplateConfig();
	}

	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity) 
	{
		super.InvokeOnConnect(player, identity);

		if (ZenTemplateConfig.SYNC_TO_CLIENTS)
		{
			GetRPCManager().SendRPC("RPC", "RPC_Receive_ZenTemplateConfig", new Param1<ref ZenTemplateConfig>(GetZenTemplateConfig()), true, identity);
		}
	}
}