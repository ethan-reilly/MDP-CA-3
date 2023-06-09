enum ECatControlType
{
	ESCT_Human,
	ESCT_AI
};

class RoboCatServer : public RoboCat
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new RoboCatServer()); }
	virtual void HandleDying() override;

	virtual void Update() override;

	void SetCatControlType(ECatControlType inCatControlType) { mCatControlType = inCatControlType; }

	void TakeDamage(int inDamagingPlayerId, int damage);

protected:
	RoboCatServer();

private:

	void HandleShooting();

	ECatControlType	mCatControlType;


	float		mTimeOfNextShot;
	float		mTimeBetweenFryShots;
	float		mTimeBetweenBurgerShots;

};

