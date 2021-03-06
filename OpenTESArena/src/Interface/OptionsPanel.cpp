#include <algorithm>
#include <cassert>

#include "SDL.h"

#include "OptionsPanel.h"

#include "Button.h"
#include "PauseMenuPanel.h"
#include "TextAlignment.h"
#include "TextBox.h"
#include "../Game/Game.h"
#include "../Game/Options.h"
#include "../Math/Vector2.h"
#include "../Media/Color.h"
#include "../Media/FontManager.h"
#include "../Media/FontName.h"
#include "../Media/PaletteFile.h"
#include "../Media/PaletteName.h"
#include "../Media/TextureFile.h"
#include "../Media/TextureManager.h"
#include "../Media/TextureName.h"
#include "../Rendering/Renderer.h"
#include "../Rendering/Texture.h"

const std::string OptionsPanel::FPS_TEXT = "FPS Limit: ";

OptionsPanel::OptionsPanel(Game *game)
	: Panel(game)
{
	this->titleTextBox = [game]()
	{
		Int2 center(160, 30);
		auto color = Color::White;
		std::string text("Options");
		auto &font = game->getFontManager().getFont(FontName::A);
		auto alignment = TextAlignment::Center;
		return std::unique_ptr<TextBox>(new TextBox(
			center,
			color,
			text,
			font,
			alignment,
			game->getRenderer()));
	}();

	this->fpsTextBox = [game]()
	{
		int x = 20;
		int y = 45;
		auto color = Color::White;
		std::string text(OptionsPanel::FPS_TEXT +
			std::to_string(game->getOptions().getTargetFPS()));
		auto &font = game->getFontManager().getFont(FontName::Arena);
		auto alignment = TextAlignment::Left;
		return std::unique_ptr<TextBox>(new TextBox(
			x,
			y,
			color,
			text,
			font,
			alignment,
			game->getRenderer()));
	}();

	this->backToPauseButton = []()
	{
		auto function = [](Game *game)
		{
			std::unique_ptr<Panel> pausePanel(new PauseMenuPanel(game));
			game->setPanel(std::move(pausePanel));
		};
		return std::unique_ptr<Button>(new Button(function));
	}();

	this->fpsUpButton = [this]()
	{
		int x = 85;
		int y = 41;
		int width = 8;
		int height = 8;
		auto function = [this](Game *game)
		{
			auto &options = game->getOptions();
			const int newFPS = options.getTargetFPS() + 5;
			options.setTargetFPS(newFPS);

			this->updateFPSText(newFPS);
		};
		return std::unique_ptr<Button>(new Button(x, y, width, height, function));
	}();

	this->fpsDownButton = [this]()
	{
		int x = this->fpsUpButton->getX();
		int y = this->fpsUpButton->getY() + this->fpsUpButton->getHeight();
		int width = this->fpsUpButton->getWidth();
		int height = this->fpsUpButton->getHeight();
		auto function = [this](Game *game)
		{
			auto &options = game->getOptions();
			const int newFPS = std::max(options.getTargetFPS() - 5, options.MIN_FPS);
			options.setTargetFPS(newFPS);

			this->updateFPSText(newFPS);
		};
		return std::unique_ptr<Button>(new Button(x, y, width, height, function));
	}();
}

OptionsPanel::~OptionsPanel()
{

}

void OptionsPanel::updateFPSText(int fps)
{
	assert(this->fpsTextBox.get() != nullptr);

	this->fpsTextBox = [this, fps]()
	{
		std::string text(OptionsPanel::FPS_TEXT + std::to_string(fps));
		auto &fontManager = this->getGame()->getFontManager();

		return std::unique_ptr<TextBox>(new TextBox(
			this->fpsTextBox->getX(),
			this->fpsTextBox->getY(),
			this->fpsTextBox->getTextColor(),
			text,
			fontManager.getFont(this->fpsTextBox->getFontName()),
			this->fpsTextBox->getAlignment(),
			this->getGame()->getRenderer()));
	}();
}

void OptionsPanel::handleEvent(const SDL_Event &e)
{
	bool escapePressed = (e.type == SDL_KEYDOWN) &&
		(e.key.keysym.sym == SDLK_ESCAPE);

	if (escapePressed)
	{
		this->backToPauseButton->click(this->getGame());
	}

	bool leftClick = (e.type == SDL_MOUSEBUTTONDOWN) &&
		(e.button.button == SDL_BUTTON_LEFT);

	if (leftClick)
	{
		const Int2 mousePosition = this->getMousePosition();
		const Int2 mouseOriginalPoint = this->getGame()->getRenderer()
			.nativePointToOriginal(mousePosition);

		// Check for various button clicks.
		if (this->fpsUpButton->contains(mouseOriginalPoint))
		{
			this->fpsUpButton->click(this->getGame());
		}
		else if (this->fpsDownButton->contains(mouseOriginalPoint))
		{
			this->fpsDownButton->click(this->getGame());
		}
	}
}

void OptionsPanel::render(Renderer &renderer)
{
	// Clear full screen.
	renderer.clearNative();
	renderer.clearOriginal();

	// Set palette.
	auto &textureManager = this->getGame()->getTextureManager();
	textureManager.setPalette(PaletteFile::fromName(PaletteName::Default));

	// Draw solid background.
	renderer.clearOriginal(Color(70, 70, 78));

	// Draw buttons.
	const auto &arrows = textureManager.getTexture(
		TextureFile::fromName(TextureName::UpDown),
		PaletteFile::fromName(PaletteName::CharSheet));
	renderer.drawToOriginal(arrows.get(), this->fpsUpButton->getX(),
		this->fpsUpButton->getY());

	// Draw text: title, fps.
	renderer.drawToOriginal(this->titleTextBox->getTexture(),
		this->titleTextBox->getX(), this->titleTextBox->getY());
	renderer.drawToOriginal(this->fpsTextBox->getTexture(),
		this->fpsTextBox->getX(), this->fpsTextBox->getY());

	// Scale the original frame buffer onto the native one.
	renderer.drawOriginalToNative();

	// Draw cursor.
	const auto &cursor = textureManager.getTexture(
		TextureFile::fromName(TextureName::SwordCursor));
	auto mousePosition = this->getMousePosition();
	renderer.drawToNative(cursor.get(),
		mousePosition.x, mousePosition.y,
		static_cast<int>(cursor.getWidth() * this->getCursorScale()),
		static_cast<int>(cursor.getHeight() * this->getCursorScale()));
}
