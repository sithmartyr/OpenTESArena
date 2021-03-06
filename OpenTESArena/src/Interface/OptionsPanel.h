#ifndef OPTIONS_PANEL_H
#define OPTIONS_PANEL_H

#include "Panel.h"

// Arena doesn't have an options menu, so I made one up!

class Button;
class Renderer;
class TextBox;

class OptionsPanel : public Panel
{
private:
	static const std::string FPS_TEXT;

	std::unique_ptr<TextBox> titleTextBox, fpsTextBox;
	std::unique_ptr<Button> backToPauseButton, fpsUpButton, fpsDownButton;

	void updateFPSText(int fps);
public:
	OptionsPanel(Game *game);
	virtual ~OptionsPanel();

	virtual void handleEvent(const SDL_Event &e) override;
	virtual void render(Renderer &renderer) override;
};

#endif
