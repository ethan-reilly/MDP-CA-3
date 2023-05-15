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
	
	//kill yourself!    :(
	SetDoesWantToDie(true);

	
	//ScoreBoardManager::sInstance->IncScore(inCat->GetPlayerId(), 1);
	//HUD::sInstance->IncHealth(1);

	
	return false;
}






