#include "RoboCatServerPCH.hpp"


MouseServer::MouseServer()
{
}

void MouseServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}


bool MouseServer::HandleCollisionWithCat(RoboCat* inCat)
{
	// Change so when you collect pickup, health increases
	inCat->GetHealth()++;
	//inCat->GetHealth() + 1;
	int ECRS_Health = 1 << 3;
	NetworkManagerServer::sInstance->SetStateDirty(inCat->GetNetworkId(), ECRS_Health);

	//kill yourself!    :(
	SetDoesWantToDie(true);

	//ScoreBoardManager::sInstance->IncScore(inCat->GetPlayerId(), 1);

	return false;
}
