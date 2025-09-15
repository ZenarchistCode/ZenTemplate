modded class PluginManager
{
	override void Init()
	{
		super.Init();

		//			   Plugin classname,       client, server
		RegisterPlugin("PluginExample", false, true);
	}
}