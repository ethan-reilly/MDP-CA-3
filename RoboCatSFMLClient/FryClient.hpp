class FryClient : public Fry
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new FryClient()); }

	virtual void		Read(InputMemoryBitStream& inInputStream) override;

protected:
	FryClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};
