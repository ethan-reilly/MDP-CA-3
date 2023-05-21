
//I take care of rendering things!

class RenderManager
{
public:

	static void StaticInit();
	static std::unique_ptr< RenderManager >	sInstance;

	void Render();
	void RenderComponents();

	//vert inefficient method of tracking scene graph...
	void AddComponent(SpriteComponent* inComponent);
	void RemoveComponent(SpriteComponent* inComponent);
	int	 GetComponentIndex(SpriteComponent* inComponent) const;

	uint8_t FindChefHealth();
	sf::Vector2f FindChefCenter();
private:

	RenderManager();

	//this can't be only place that holds on to component- it has to live inside a GameObject in the world
	vector< SpriteComponent* >		mComponents;

	sf::View view;
	sf::Sprite background;
	sf::Sprite deathscreen;
	sf::Vector2f m_lastCatPos;
	sf::Sprite winscreen;
	sf::Sprite titlescreen;
	bool gamewinner;

};




