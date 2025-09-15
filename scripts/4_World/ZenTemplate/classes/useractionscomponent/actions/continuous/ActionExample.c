class ActionExampleCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(5);
	}
}

class ActionExample : ActionContinuousBase
{
	void ActionExample()
	{
		m_CallbackClass = ActionExampleCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_CRAFTING;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
		m_Text = "Your action name";
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINonRuined();
		m_ConditionTarget = new CCTNonRuined();
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		Barrel_ColorBase barrel = Barrel_ColorBase.Cast(target.GetObject());

		if (!barrel)
			return false;

		return true;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		ZenTemplateFunctions.DebugMessage("DISMANTLE BARREL!");

		Screwdriver tool = Screwdriver.Cast(action_data.m_MainItem);
		if (!tool)
			return;

		Barrel_ColorBase barrel = Barrel_ColorBase.Cast(action_data.m_Target.GetObject());
		if (!barrel)
			return;

		tool.ZenPlaySound();
		barrel.DeleteSafe();
	}

	override void OnStartAnimationLoop(ActionData action_data)
	{
		super.OnStartAnimationLoop(action_data);

		SendZenSoundPlay(action_data, true);
	}
	
	override void OnEnd(ActionData action_data)
	{
		super.OnEnd(action_data);

		SendZenSoundPlay(action_data, false);
	}
	
	override void OnEndAnimationLoop(ActionData action_data)
	{
		super.OnEndAnimationLoop(action_data);

		SendZenSoundPlay(action_data, false);
	}

	protected void SendZenSoundPlay(ActionData action_data, bool loop)
	{
		#ifdef SERVER

		Screwdriver tool = Screwdriver.Cast(action_data.m_MainItem);
		if (!tool)
			return;

		ZenTemplateFunctions.DebugMessage("Play sound loop: " + loop);
		
		Param2<string, bool> soundParams = new Param2<string, bool>("minePickAxe_SoundSet", loop);
		GetGame().RPCSingleParam(tool, Screwdriver.ZEN_ACTION_LOOP, soundParams, true);
		
		#endif
	}
}