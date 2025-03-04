#include "Sprite.h"

class Stage
{
private:
	std::vector<Isatronia::Sprite::Sprite> Sprites;
};

class Game
{
	// static
public:
	static Game& getInstance()
	{
		static Game instance; // C++11 起线程安全
		return instance;
	}

	// class definations
private:
	std::vector<Stage> stages;

private:
	Game()
	{
		stages = std::vector<Stage>();
	}
	~Game()
	{

	}
public:
	// singleton
	Game(const Game&) = delete;
	Game& operator= (const Game&) = delete;
};

void InitializeStage()
{
	return;
}