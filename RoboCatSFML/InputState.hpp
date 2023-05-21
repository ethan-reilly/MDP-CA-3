class InputState
{
public:

	InputState() :
		mDesiredRightAmount(0),
		mDesiredLeftAmount(0),
		mDesiredForwardAmount(0),
		mDesiredBackAmount(0),
		mIsShootingFry(false),
		mIsShootingBurger(false)
	{}

	float GetDesiredHorizontalDelta()	const { return mDesiredRightAmount - mDesiredLeftAmount; }
	float GetDesiredVerticalDelta()		const { return mDesiredForwardAmount - mDesiredBackAmount; }
	bool  IsShootingFry()					const { return mIsShootingFry; }
	bool  IsShootingBurger()					const { return mIsShootingBurger; }

	bool Write(OutputMemoryBitStream& inOutputStream) const;
	bool Read(InputMemoryBitStream& inInputStream);

private:
	friend class InputManager;

	float mDesiredRightAmount, mDesiredLeftAmount;
	float mDesiredForwardAmount, mDesiredBackAmount;
	bool mIsShootingFry;
	bool mIsShootingBurger;
};
