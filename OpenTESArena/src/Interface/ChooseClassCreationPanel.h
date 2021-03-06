#ifndef CHOOSE_CLASS_CREATION_PANEL_H
#define CHOOSE_CLASS_CREATION_PANEL_H

#include <string>

#include "Panel.h"

// This panel is for the "How do you wish to select your class?" screen.

// I added new tooltips for each option. I always found it confusing what 
// the buttons meant exactly.

class Button;
class Renderer;
class TextBox;
class Texture;

class ChooseClassCreationPanel : public Panel
{
private:
	std::unique_ptr<Texture> parchment;
	std::unique_ptr<TextBox> titleTextBox, generateTextBox, selectTextBox;
	std::unique_ptr<Button> backToMainMenuButton, generateButton, selectButton;

	void drawTooltip(const std::string &text, Renderer &renderer);
public:
	ChooseClassCreationPanel(Game *game);
	virtual ~ChooseClassCreationPanel();

	virtual void handleEvent(const SDL_Event &e) override;
	virtual void render(Renderer &renderer) override;
};

#endif
