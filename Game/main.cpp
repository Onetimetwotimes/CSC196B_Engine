#include "core.h"
#include "scene.h"
#include "Player.h"
#include "HostileSpawner.h"
#include "AsteroidSpawner.h"
#include "AudioSystem.h"
#include "gamestate.h"
#include "scoreboard.h"

float exitTimer = 1;
std::string playerTag = "---";
UINT8 cursorPos = 0;
bool release = true;


zbe::scene scene;
HostileSpawner hostiles;
AsteroidSpawner asteroids;


zbe::shape title = zbe::shape({
		zbe::math::vector( -10, -50),
		zbe::math::vector(  10, -50),
		zbe::math::vector(  50,  40),
		zbe::math::vector(  10,  20),
		zbe::math::vector(  00, -10),
		zbe::math::vector( -10,  20),
		zbe::math::vector( -50,  40),
		zbe::math::vector( -10, -50)
	},
	zbe::Color(1, 1, 1));



void drawScoreSubmission(Core::Graphics& g) {
	sb.drawBoard(g);
	g.DrawString(130, 200,		
		"  _|_|_|\n"
		" _|           _|_|_|   _|_|_|  _|_|       _|_|   \n"
		" _|  _|_|   _|    _|   _|    _|    _|   _|_|_|_| \n"
		" _|    _|   _|    _|   _|    _|    _|   _|       \n"
		"   _|_|_|     _|_|_|   _|    _|    _|     _|_|_| \n"
		"\n"
		"     _|_|                                        \n"
		"   _|    _|   _|      _|     _|_|     _|  _|_|   \n"
		"   _|    _|   _|      _|   _|_|_|_|   _|_|       \n"
		"   _|    _|     _|  _|     _|         _|         \n"
		"     _|_|         _|         _|_|_|   _|         \n"
		"\n"
		"               Submit your score!                \n"
	);
	std::string text = "   ";
	text[cursorPos] = '.';
	text +="\n" + playerTag;
	g.DrawString(290, 360,text.c_str());

	sb.drawSavedScores(g);
}

bool Update(float dT) {

	switch (gamestate)
	{
	case E_Gamestate::START:
		if (Core::Input::IsPressed(Core::Input::KEY_UP))
			gamestate = E_Gamestate::PLAY;
		break;
	case E_Gamestate::PLAY:
		scene.Update(dT);
		asteroids.Update(dT);
		hostiles.Update(dT);
		break;
	case E_Gamestate::LOSE:
		if (Core::Input::IsPressed(Core::Input::KEY_DOWN)) {
			if (release) {
				playerTag[cursorPos] = sb.tagCycleDown(playerTag[cursorPos]);
				release = false;
			}
		}
		else if (Core::Input::IsPressed(Core::Input::KEY_UP)) {
			if (release) {
				playerTag[cursorPos] = sb.tagCycleUp(playerTag[cursorPos]);
				release = false;
			}
		}
		else if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) {
			if (release) {
				cursorPos = max(cursorPos - 1, 0);
				release = false;
			}
		}
		else if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) {
			if (release) {
				cursorPos++;
				release = false;
				if(cursorPos == 3) {
					sb.submitScore(playerTag, sb.gameScore);
					sb.writeScores();
				}
			}
		}
		else
			release = cursorPos < 3;
	}
	if (Core::Input::IsPressed(Core::Input::KEY_ESCAPE)) {
		scene.Close();
		scene.addActor(new Player);
		scene.Init();
		hostiles.Init(&scene,0,15,20);
		asteroids.Init(&scene);
		gamestate = E_Gamestate::START;
		sb.gameScore = 0;
		cursorPos = 0;

		exitTimer -= dT;
		std::cout << exitTimer;
		if (exitTimer <= 0)
			return true;
	}
	else {
		if (exitTimer < 1) {
			exitTimer += dT;
		}
		
	}

	return false;

}

void Draw(Core::Graphics& graphics) {
	switch (gamestate) {
	case E_Gamestate::START:
		title.Draw(graphics, zbe::math::transform(zbe::math::vector(300,400)));
		graphics.DrawString(245, 450, "Press ^ to start!");
		break;
	case E_Gamestate::PLAY:
		sb.drawBoard(graphics);
		scene.Draw(graphics);
		break;
	case E_Gamestate::LOSE:
		drawScoreSubmission(graphics);
		

		break;
		
	}

	if (exitTimer < 1) {
		auto status = "Exiting";
		if (exitTimer < .75)
			status = "Exiting.";
		if (exitTimer < .5)
			status = "Exiting..";
		if (exitTimer < .25)
			status = "Exiting...";
		graphics.DrawString(0, 0, status);
	}
}


int main() {
	char name[] = "Victor Antonio - Asteroids";
	g_audio.Start();
	g_audio.AddAudio("laser", "laser.wav");
	g_audio.AddAudio("break", "break.wav");
	g_audio.AddAudio("small_break", "small_break.wav");
	g_audio.AddAudio("lose", "lose.wav");
	scene.addActor(new Player());
	scene.Init();
	asteroids.Init(&scene);
	hostiles.Init(&scene,0,15,20);
	Core::Init(name, 600, 800);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	
	Core::GameLoop();
	Core::Shutdown();
}