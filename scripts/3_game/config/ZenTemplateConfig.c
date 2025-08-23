class ZenTemplateConfig
{
	static const string MOD_AUTHOR				= "YourModdingName";
	static const bool LOAD_ON_SERVER			= true;		// true  = load/save this file on the server
	static const bool LOAD_ON_CLIENT			= false;	// true  = load/save this file on the client
	static const bool CLIENT_SAVE_TO_SERVER_IP	= true;		// true  = save client config file based on server IP
	static const bool SYNC_TO_CLIENTS			= true;		// false = don't sync this data to player clients

	// Config location
	private const static string ModFolder		= "$profile:\\" + MOD_AUTHOR + "\\";
	private const static string ConfigName		= "ZenTemplateConfig.json";
	private const static string CURRENT_VERSION	= "1"; // Change this to force structure update.
	string CONFIG_VERSION;

	// Config data
	string ExampleConfig;
	bool ExampleBool;
	ref array<ref ZenTemplateCustomConfig> ExampleArrayConfig;

	void Load()
	{
		string serverIP = "";
		SetDefaultValues();

		if (GetGame().IsClient())
		{
			if (!LOAD_ON_CLIENT)
			{
				return;
			}

			if (CLIENT_SAVE_TO_SERVER_IP)
			{
				GetCLIParam("connect", serverIP);
				serverIP.Replace(":", "");
				serverIP.Replace(".", "");
			}
		}

		if (GetGame().IsDedicatedServer())
		{
			if (!LOAD_ON_SERVER)
			{
				return;
			}
		}

		if (FileExist(ModFolder + serverIP + "\\" + ConfigName))
		{ 
			// If config exists, load file
			JsonFileLoader<ZenTemplateConfig>.JsonLoadFile(ModFolder + serverIP + "\\" + ConfigName, this);

			// If version mismatch, backup old version of json before replacing it
			if (CONFIG_VERSION != CURRENT_VERSION)
			{
				JsonFileLoader<ZenTemplateConfig>.JsonSaveFile(ModFolder + serverIP + "\\" + ConfigName + "_old", this);
			}
			else
			{
				// Config file exists, was loaded successfully, and version matches - stop here.
				return;
			}
		}

		CONFIG_VERSION = CURRENT_VERSION;

		Save();
	}

	void SetDefaultValues()
	{
		ExampleConfig = "Example config data.";

		ExampleArrayConfig = new array<ref ZenTemplateCustomConfig>;
		ExampleArrayConfig.Insert(new ZenTemplateCustomConfig("Tisy", "1234 0 1234", 500));
	}

	void Save()
	{
		if (GetGame().IsClient())
		{
			if (!LOAD_ON_CLIENT)
			{
				return;
			}
		}

		if (GetGame().IsDedicatedServer())
		{
			if (!LOAD_ON_SERVER)
			{
				return;
			}
		}

		if (!FileExist(ModFolder))
		{
			MakeDirectory(ModFolder);
		}

		string serverIP = "";

		if (GetGame().IsClient() && CLIENT_SAVE_TO_SERVER_IP)
		{
			GetCLIParam("connect", serverIP);
			serverIP.Replace(":", "");
			serverIP.Replace(".", "");
		}

		if (!FileExist(ModFolder + serverIP))
		{
			MakeDirectory(ModFolder + serverIP);
		}

		JsonFileLoader<ZenTemplateConfig>.JsonSaveFile(ModFolder + serverIP + "\\" + ConfigName, this);
	}
}

class ZenTemplateCustomConfig
{
	string Name;
	vector Location;
	float NoBuildZone;
	ref array<string> Whitelist;

	void ZenTemplateCustomConfig(string p_name, vector p_location, float p_nobuildzone)
	{
		Name = p_name;
		Location = p_location;
		NoBuildZone = p_nobuildzone;

		Whitelist = new array<string>;
		Whitelist.Insert("FireplaceBase");
	}
}

static ZenTemplateConfig GetZenTemplateConfig()
{
	if (!m_ZenTemplateConfig)
	{
		Print("[ZenTemplateConfig] Init");
		m_ZenTemplateConfig = new ZenTemplateConfig();
		m_ZenTemplateConfig.Load();
	}

	return m_ZenTemplateConfig;
}

ref ZenTemplateConfig m_ZenTemplateConfig;