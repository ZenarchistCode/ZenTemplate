modded class Screwdriver
{
	ref EffectSound	m_ExampleSoundEffect;

	static const int ZEN_ACTION_LOOP = 10103030;
	static const string ZEN_ACTION_SOUNDSET = "ZenTemplateExample_SoundSet";

	bool m_ZenShouldPlaySound;

	static ref NoiseParams 	m_NoisePar;
	static NoiseSystem		m_NoiseSystem;

	override void InitItemVariables()
	{
		super.InitItemVariables();

		RegisterNetSyncVariableBoolSignal("m_ZenShouldPlaySound");

		if (GetGame().IsServer())
		{
			m_NoiseSystem = GetGame().GetNoiseSystem();

			if (m_NoiseSystem && !m_NoisePar)
			{
				// Create and load noise parameters
				m_NoisePar = new NoiseParams;
				m_NoisePar.LoadFromPath("CfgSoundSets ZenTemplateExample_SoundSet NoiseAI");
			}
		}
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();

		CheckZenPlaySoundOnClient();
	}

	void CheckZenPlaySoundOnClient()
	{
		if (m_ZenShouldPlaySound)
		{
			EffectSound singleSound = SEffectManager.PlaySoundOnObject(ZEN_ACTION_SOUNDSET, this);
			if (singleSound)
			{
				singleSound.SetAutodestroy(true);
			}
		}
	}

	void ZenPlaySound()
	{
		m_ZenShouldPlaySound = true;
		SetSynchDirty();

		m_NoiseSystem.AddNoiseTarget(GetPosition(), 5000, m_NoisePar, NoiseAIEvaluate.GetNoiseReduction(GetGame().GetWeather()));
	}

	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionExample);
	}

	override void OnRPC(PlayerIdentity sender, int rpc_type,ParamsReadContext ctx) 
	{
		super.OnRPC(sender, rpc_type, ctx);

		if (rpc_type == ZEN_ACTION_LOOP)
		{
			Param2<string, bool> params;
			
			if (!ctx.Read(params))
				return;

			if (params.param2)
			{
				m_ExampleSoundEffect = SEffectManager.PlaySoundOnObject(params.param1, this, 0, 0, true);

				if (m_ExampleSoundEffect)
				{
					m_ExampleSoundEffect.SetAutodestroy(true);
				}
			}
			else 
			{
				if (m_ExampleSoundEffect)
				{
					m_ExampleSoundEffect.SoundStop();
				}
			}
		}
	}
}