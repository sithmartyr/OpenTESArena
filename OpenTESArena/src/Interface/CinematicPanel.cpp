#include <cassert>

#include "SDL.h"

#include "CinematicPanel.h"

#include "Button.h"
#include "../Game/Game.h"
#include "../Media/TextureManager.h"
#include "../Rendering/Renderer.h"
#include "../Rendering/Texture.h"

CinematicPanel::CinematicPanel(Game *game,
	const std::string &sequenceName, const std::string &paletteName,
	double secondsPerImage, const std::function<void(Game*)> &endingAction)
	: Panel(game)
{
	this->skipButton = [&endingAction]()
	{
		return std::unique_ptr<Button>(new Button(endingAction));
	}();

	this->paletteName = paletteName;
	this->sequenceName = sequenceName;
	this->secondsPerImage = secondsPerImage;
	this->currentSeconds = 0.0;
	this->imageIndex = 0;
}

CinematicPanel::~CinematicPanel()
{

}

void CinematicPanel::handleEvent(const SDL_Event &e)
{
	bool leftClick = (e.type == SDL_MOUSEBUTTONDOWN) &&
		(e.button.button == SDL_BUTTON_LEFT);
	bool spacePressed = (e.type == SDL_KEYDOWN) &&
		(e.key.keysym.sym == SDLK_SPACE);
	bool returnPressed = (e.type == SDL_KEYDOWN) &&
		(e.key.keysym.sym == SDLK_RETURN);
	bool escapePressed = (e.type == SDL_KEYDOWN) &&
		(e.key.keysym.sym == SDLK_ESCAPE);
	bool numpadEnterPressed = (e.type == SDL_KEYDOWN) &&
		(e.key.keysym.sym == SDLK_KP_ENTER);

	bool skipHotkeyPressed = spacePressed || returnPressed || 
		escapePressed || numpadEnterPressed;

	if (leftClick || skipHotkeyPressed)
	{
		this->skipButton->click(this->getGame());
	}
}

void CinematicPanel::tick(double dt)
{
	// See if it's time for the next image.
	this->currentSeconds += dt;
	while (this->currentSeconds > this->secondsPerImage)
	{
		this->currentSeconds -= this->secondsPerImage;
		this->imageIndex++;
	}

	// Get a reference to all images in the sequence.
	auto &textureManager = this->getGame()->getTextureManager();
	const auto &textures = textureManager.getTextures(
		this->sequenceName, this->paletteName);

	// If at the end, then prepare for the next panel.
	if (this->imageIndex >= textures.size())
	{
		this->imageIndex = static_cast<int>(textures.size() - 1);
		this->skipButton->click(this->getGame());
	}
}

void CinematicPanel::render(Renderer &renderer)
{
	// Clear full screen.
	renderer.clearNative();
	renderer.clearOriginal();

	// Get a reference to all images in the sequence.
	auto &textureManager = this->getGame()->getTextureManager();
	const auto &textures = textureManager.getTextures(
		this->sequenceName, this->paletteName);

	// Draw image.
	const auto &texture = textures.at(this->imageIndex);
	renderer.drawToOriginal(texture.get());

	// Scale the original frame buffer onto the native one.
	renderer.drawOriginalToNative();
}
