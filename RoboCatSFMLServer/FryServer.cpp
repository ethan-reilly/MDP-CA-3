#include "RoboCatServerPCH.hpp"


FryServer::FryServer()
{

	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 0.8f;
}

void FryServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}


void FryServer::Update()
{
	Fry::Update();

	if (Timing::sInstance.GetFrameStartTime() > mTimeToDie)
	{
		SetDoesWantToDie(true);
	}

}

bool FryServer::HandleCollisionWithCat(RoboCat* inCat)
{
	if (inCat->GetPlayerId() != GetPlayerId())
	{
		//kill yourself!
		SetDoesWantToDie(true);

		static_cast<RoboCatServer*>(inCat)->TakeDamage(GetPlayerId(), 1);

	}

	return false;
}



