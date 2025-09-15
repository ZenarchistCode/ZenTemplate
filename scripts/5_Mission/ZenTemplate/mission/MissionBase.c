modded class MissionBase
{
	void MissionBase()
	{
		#ifdef SERVER
		// SERVER RECEIVE RPCs
        //GetRPCManager().AddRPC("RPC", "RPC_Receive_Client_to_Server", this, SingeplayerExecutionType.Server);
		#else
		// CLIENT RECEIVE RPCs
        GetRPCManager().AddRPC("RPC", "RPC_Receive_ZenTemplateConfig", this, SingeplayerExecutionType.Client);
		#endif
	}

	override UIScriptedMenu CreateScriptedMenu(int id)
    {
        UIScriptedMenu menu = super.CreateScriptedMenu(id);

        if (!menu)
        {
            switch (id)
            {
                /*
				case YourConstantsFile.YOUR_GUI_ID:
                {
                    menu = new CustomGUI();
                    break;
                }
                */
            }
        }

        return menu;
    }

	// Server -> client
    void RPC_Receive_ZenTemplateConfig(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        Param1<ref ZenTemplateConfig> data;
        if (!ctx.Read(data))
        {
            Error("Error sync'ing server-side data to client - RPC_Receive_ZenTemplateConfig");
            return;
        }

        m_ZenTemplateConfig = data.param1;

        Print("[ZenTemplate] Received config sync: " + GetZenTemplateConfig().ExampleConfig);

        for (int i = 0; i < GetZenTemplateConfig().ExampleArrayConfig.Count(); i++)
        {
            ZenTemplateCustomConfig customConfig = GetZenTemplateConfig().ExampleArrayConfig.Get(i);
            Print("[ZenTemplate] Received no build zone: " + customConfig.Name + " - dist = " + customConfig.NoBuildZone + " @ " + customConfig.Location);

            for (int x = 0; x < customConfig.Whitelist.Count(); x++)
            {
                Print("[" + customConfig.Name + "] Whitelist Item name=" + customConfig.Whitelist.Get(x));
            }
        }
    }
}