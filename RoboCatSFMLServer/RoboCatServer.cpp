#include "RoboCatServerPCH.hpp"

RoboCatServer::RoboCatServer() :
	mCatControlType(ESCT_Human),
	mTimeOfNextShot(0.f),
	//need to adjust between burger/yarn and fry
	mTimeBetweenFryShots(0.2f),
	mTimeBetweenBurgerShots(0.9f)
{}

void RoboCatServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}

void RoboCatServer::Update()
{
	RoboCat::Update();

	Vector3 oldLocation = GetLocation();
	Vector3 oldVelocity = GetVelocity();
	float oldRotation = GetRotation();

	//are you controlled by a player?
	//if so, is there a move we haven't processed yet?
	if (mCatControlType == ESCT_Human)
	{
		ClientProxyPtr client = NetworkManagerServer::sInstance->GetClientProxy(GetPlayerId());
		if (client)
		{
			MoveList& moveList = client->GetUnprocessedMoveList();
			for (const Move& unprocessedMove : moveList)
			{
				const InputState& currentState = unprocessedMove.GetInputState();

				float deltaTime = unprocessedMove.GetDeltaTime();

				ProcessInput(deltaTime, currentState);
				SimulateMovement(deltaTime);

				//LOG( "Server Move Time: %3.4f deltaTime: %3.4f left rot at %3.4f", unprocessedMove.GetTimestamp(), deltaTime, GetRotation() );

			}

			moveList.Clear();
		}
	}
	else
	{
		//do some AI stuff
		SimulateMovement(Timing::sInstance.GetDeltaTime());
	}


	HandleShooting();

	if (!RoboMath::Is2DVectorEqual(oldLocation, GetLocation()) ||
		!RoboMath::Is2DVectorEqual(oldVelocity, GetVelocity()) ||
		oldRotation != GetRotation())
	{
		NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), ECRS_Pose);
	}
}

void RoboCatServer::HandleShooting()
{
	float time = Timing::sInstance.GetFrameStartTime();
	if (mIsShootingFry && Timing::sInstance.GetFrameStartTime() > mTimeOfNextShot)
	{
		mTimeOfNextShot = time + mTimeBetweenFryShots;

		//fire!
		FryPtr fry = std::static_pointer_cast<Fry>(GameObjectRegistry::sInstance->CreateGameObject('FRY'));
		fry->InitFromShooter(this);
	}
	
	
	if (mIsShootingBurger && Timing::sInstance.GetFrameStartTime() > mTimeOfNextShot)
	{
		//not exact, but okay
		mTimeOfNextShot = time + mTimeBetweenBurgerShots;

		//fire!
		YarnPtr yarn = std::static_pointer_cast<Yarn>(GameObjectRegistry::sInstance->CreateGameObject('YARN'));
		yarn->InitFromShooter(this);
	}
}

/// <summary>
/// Does different damage based on projectile type
/// </summary>
/// <param name="inDamagingPlayerId"></param>
/// <param name="damage"></param>
void RoboCatServer::TakeDamage(int inDamagingPlayerId, int damage)
{	
	mHealth-= damage;
	if (mHealth <= 0.f)
	{
		//score one for damaging player...
		ScoreBoardManager::sInstance->IncScore(inDamagingPlayerId, 1);

		//and you want to die
		SetDoesWantToDie(true);

		//tell the client proxy to make you a new cat
		ClientProxyPtr clientProxy = NetworkManagerServer::sInstance->GetClientProxy(GetPlayerId());
		if (clientProxy)
		{
			clientProxy->HandleCatDied();
		}
	}

	//tell the world our health dropped
	NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), ECRS_Health);
}

