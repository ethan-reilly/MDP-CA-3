class FryServer : public Fry
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new FryServer()); }
	void HandleDying() override;

	virtual bool		HandleCollisionWithCat(RoboCat* inCat) override;

	virtual void Update() override;

protected:
	FryServer();

private:
	float mTimeToDie;

};

