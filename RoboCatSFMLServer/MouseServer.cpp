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
	//kill yourself!    :(
	SetDoesWantToDie(true);

	// Change so when you collect mouse, health increases
	//ScoreBoardManager::sInstance->IncScore(inCat->GetPlayerId(), 1);
	HUD::sInstance->IncHealth(1);
	return false;
}






