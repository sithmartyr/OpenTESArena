#ifndef GAME_H
#define GAME_H

#include <memory>

#include "../Media/AudioManager.h"

// This class holds the current game data, manages the primary game loop, and 
// updates the game state each frame.

// The game data holds all the active player and world data. It is null if a 
// game session is not currently running (in the main menu, character creation), 
// and is not null while a game session is running (in the game world, pause menu, 
// cinematic, journal, etc.).

// Game members should be available through a getter so panels can access them.

class GameData;
class FontManager;
class Options;
class Panel;
class Renderer;
class TextureManager;
class TextAssets;

enum class MusicName;

class Game
{
private:
	AudioManager audioManager;
	std::unique_ptr<FontManager> fontManager;
	std::unique_ptr<GameData> gameData;
	std::unique_ptr<Options> options;
	std::unique_ptr<Panel> panel, nextPanel;
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<TextureManager> textureManager;
	std::unique_ptr<TextAssets> textAssets;

	// Waits the given number of milliseconds.
	void delay(int ms);

	// Resizes the SDL renderer and any other renderer-associated components.
	void resizeWindow(int width, int height);

	// Handles SDL events for the current frame.
	void handleEvents(bool &running);

	// Animates the game state by delta time.
	void tick(double dt);

	// Runs the current panel's render method for drawing to the screen.
	void render();
public:
	Game();
	~Game();

	// Gets the audio manager for changing the current music and sound.
	AudioManager &getAudioManager();

	// Gets the font manager object for creating text with.
	FontManager &getFontManager() const;

	// Determines if a game session is currently running. This is true when a player
	// is loaded into memory.
	bool gameDataIsActive() const;

	// The game data holds the "session" data for the game. If no session is active, 
	// do not call this method. Verify beforehand by calling Game::gameDataIsActive().
	GameData &getGameData() const;

	// Gets the options object for various settings (resolution, volume, sensitivity).
	Options &getOptions() const;

	// Gets the renderer object for rendering methods.
	Renderer &getRenderer() const;

	// Gets the texture manager object for loading images from file.
	TextureManager &getTextureManager() const;

	// Gets the text assets object for loading Arena-related text files.
	TextAssets &getTextAssets() const;

	// Sets the panel after the current SDL event has been processed (to avoid 
	// interfering with the current panel).
	void setPanel(std::unique_ptr<Panel> nextPanel);

	// Sets the music to the given music name.
	void setMusic(MusicName name);

	// Sets the current game data object. A game session is active if the game data
	// is not null.
	void setGameData(std::unique_ptr<GameData> gameData);

	// Initial method for starting the game loop. This must only be called by main().
	void loop();
};

#endif
