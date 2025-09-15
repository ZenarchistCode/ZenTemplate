class PluginExample extends PluginBase
{
	static const float UPDATE_TICK_SECS = 1;

	protected float m_DeltaTime;

	override void OnInit()
    {
        Print("[PluginExample] :: OnInit.");
    }

    override void OnDestroy()
	{
		Print("[PluginExample] :: OnDestroy.");
    }

    override void OnUpdate(float delta_time)
	{
		m_DeltaTime += delta_time;
		if (m_DeltaTime < UPDATE_TICK_SECS)
			return;

		m_DeltaTime = 0;

		// (optional - to update on every tick remove the throttle code above)
		Update();
	}

	void Update()
	{
		// Do something here, delayed by UPDATE_TICK_SECS seconds between updates
	}
}