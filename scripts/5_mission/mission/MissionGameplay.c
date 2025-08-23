// Client-side only code
modded class MissionGameplay
{
	override void OnInit()
    {
        super.OnInit();

		// Load client-side config
		GetZenTemplateConfig();
    }

	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice); 

		if (!GetGame())
			return;

		UpdateExample();
	}

	override void OnKeyPress(int key)
	{
		super.OnKeyPress(key);

		//Print("Key pressed ID: " + key);
	}

	void UpdateExample()
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
			return;

		if (Zen_CheckInput("UAZenTemplateKeybind"))
        {
            // do something
			ZenTemplateFunctions.DebugMessage("Key pressed!");
        }
	}

    private bool Zen_CheckInput(string inputName)
    {
        if (GetUApi())
		{
            UAInput uai = GetUApi().GetInputByName(inputName);

            if (uai && uai.LocalPress())
            {
                return true;
            }
        }

        return false;
    }
}