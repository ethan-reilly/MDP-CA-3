#include "RoboCatClientPCH.hpp"

std::unique_ptr< RenderManager >	RenderManager::sInstance;

RenderManager::RenderManager()
{
	view.reset(sf::FloatRect(0, 0, 1920, 1080));
	WindowManager::sInstance->setView(view);
	background.setTexture(*TextureManager::sInstance->GetTexture("floor"));
	deathscreen.setTexture(*TextureManager::sInstance->GetTexture("deathscreen"));
	winscreen.setTexture(*TextureManager::sInstance->GetTexture("winnerscreen"));
	titlescreen.setTexture(*TextureManager::sInstance->GetTexture("titlescreen"));
}


void RenderManager::StaticInit()
{
	sInstance.reset(new RenderManager());
}


void RenderManager::AddComponent(SpriteComponent* inComponent)
{
	mComponents.emplace_back(inComponent);
}

void RenderManager::RemoveComponent(SpriteComponent* inComponent)
{
	int index = GetComponentIndex(inComponent);

	if (index != -1)
	{
		int lastIndex = mComponents.size() - 1;
		if (index != lastIndex)
		{
			mComponents[index] = mComponents[lastIndex];
		}
		mComponents.pop_back();
	}
}

int RenderManager::GetComponentIndex(SpriteComponent* inComponent) const
{
	for (int i = 0, c = mComponents.size(); i < c; ++i)
	{
		if (mComponents[i] == inComponent)
		{
			return i;
		}
	}

	return -1;
}

uint8_t RenderManager::FindChefHealth()
{
	uint32_t chefID = (uint32_t)'RCAT';
	for (auto obj : World::sInstance->GetGameObjects())
	{
		//find the chefs
		if (obj->GetClassId() == chefID)
		{
			RoboCat* chef = dynamic_cast<RoboCat*>(obj.get());
			auto id = chef->GetPlayerId();
			auto ourID = NetworkManagerClient::sInstance->GetPlayerId();
			if (id == ourID)
			{
				return chef->GetHealth();
			}
		}
	}
	return 0;
}

sf::Vector2f RenderManager::FindChefCenter()
{
	uint32_t chefID = (uint32_t)'RCAT';
	for (auto obj : World::sInstance->GetGameObjects())
	{
		// Find a cat.
		if (obj->GetClassId() == chefID)
		{
			RoboCat* chef = dynamic_cast<RoboCat*>(obj.get());
			auto id = chef->GetPlayerId();
			auto ourID = NetworkManagerClient::sInstance->GetPlayerId();
			if (id == ourID)
			{
				// If so grab the centre point.
				auto centre = chef->GetLocation();
				m_lastCatPos.x = centre.mX;
				m_lastCatPos.y = centre.mY;
				return sf::Vector2f(centre.mX, centre.mY);
			}
		}
	}
	return sf::Vector2f(-1, -1);
}


//this part that renders the world is really a camera-
//in a more detailed engine, we'd have a list of cameras, and then render manager would
//render the cameras in order
void RenderManager::RenderComponents()
{
	//Get the logical viewport so we can pass this to the SpriteComponents when it's draw time
	for (SpriteComponent* c : mComponents)
	{
		WindowManager::sInstance->draw(c->GetSprite());
	}
}

void RenderManager::Render()
{
	//
	// Clear the back buffer
	//

	//WindowManager::sInstance->clear(sf::Color(100, 149, 237, 255));

	WindowManager::sInstance->clear(sf::Color(255, 204, 204, 255));

	if (mComponents.size() > 0)
	{


		//Background image
		//WindowManager::sInstance->clear(sf::Image(TextureManager::sInstance->GetTexture("floor")));
		WindowManager::sInstance->draw(background);

		RenderManager::sInstance->RenderComponents();

		HUD::sInstance->Render();


		if (FindChefCenter() == sf::Vector2f(-1, -1))
		{
			sf::Vector2f died(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);
			deathscreen.setPosition(died);
			WindowManager::sInstance->draw(deathscreen);
		}
		else
		{

			if (FindChefHealth() > 0 &&
				ScoreBoardManager::sInstance->GetEntry(NetworkManagerClient::sInstance->GetPlayerId())->GetScore() > 5)
			{
				// Draw some you are the winner screen.
				sf::Vector2f winner(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);
				winscreen.setPosition(winner);
				WindowManager::sInstance->draw(winscreen);
			}
		}
		//
		// Present our back buffer to our front buffer
		//
	}
	else
	{
		//WindowManager::sInstance->draw(titlescreen);
	}
	WindowManager::sInstance->display();

}