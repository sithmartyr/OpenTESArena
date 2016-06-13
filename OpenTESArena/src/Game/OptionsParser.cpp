#include <cassert>

#include "OptionsParser.h"

#include "Options.h"
#include "../Utilities/KvpTextMap.h"

const std::string OptionsParser::PATH = "options/";
const std::string OptionsParser::FILENAME = "options.txt";

const std::string OptionsParser::SCREEN_WIDTH_KEY = "ScreenWidth";
const std::string OptionsParser::SCREEN_HEIGHT_KEY = "ScreenHeight";
const std::string OptionsParser::FULLSCREEN_KEY = "Fullscreen";
const std::string OptionsParser::VERTICAL_FOV_KEY = "VerticalFieldOfView";
const std::string OptionsParser::H_SENSITIVITY_KEY = "HorizontalSensitivity";
const std::string OptionsParser::V_SENSITIVITY_KEY = "VerticalSensitivity";
const std::string OptionsParser::MUSIC_VOLUME_KEY = "MusicVolume";
const std::string OptionsParser::SOUND_VOLUME_KEY = "SoundVolume";
const std::string OptionsParser::SOUNDFONT_KEY = "Soundfont";
const std::string OptionsParser::SOUND_CHANNELS_KEY = "SoundChannels";
const std::string OptionsParser::DATA_PATH_KEY = "DataPath";
const std::string OptionsParser::SKIP_INTRO_KEY = "SkipIntro";

std::unique_ptr<Options> OptionsParser::parse()
{
	// Path to the options file.
	std::string fullPath = OptionsParser::PATH + OptionsParser::FILENAME;

	// Read in all the key-value pairs from the options file.
	KvpTextMap textMap(fullPath);
	
	// Graphics.
	int screenWidth = textMap.getInteger(OptionsParser::SCREEN_WIDTH_KEY);
	int screenHeight = textMap.getInteger(OptionsParser::SCREEN_HEIGHT_KEY);
	bool fullscreen = textMap.getBoolean(OptionsParser::FULLSCREEN_KEY);
	double verticalFOV = textMap.getDouble(OptionsParser::VERTICAL_FOV_KEY);

	// Input.
	double hSensitivity = textMap.getDouble(OptionsParser::H_SENSITIVITY_KEY);
	double vSensitivity = textMap.getDouble(OptionsParser::V_SENSITIVITY_KEY);

    // Sound.
    double musicVolume = textMap.getDouble(OptionsParser::MUSIC_VOLUME_KEY);
    double soundVolume = textMap.getDouble(OptionsParser::SOUND_VOLUME_KEY);
	std::string soundfont = textMap.getString(OptionsParser::SOUNDFONT_KEY);
    int soundChannels = textMap.getInteger(OptionsParser::SOUND_CHANNELS_KEY);

	// Miscellaneous.
	std::string dataPath = textMap.getString(OptionsParser::DATA_PATH_KEY);
	bool skipIntro = textMap.getBoolean(OptionsParser::SKIP_INTRO_KEY);
	
	return std::unique_ptr<Options>(new Options(std::move(dataPath),
		screenWidth, screenHeight, fullscreen, verticalFOV, hSensitivity, 
		vSensitivity, std::move(soundfont), musicVolume, soundVolume, 
		soundChannels, skipIntro));
}

void OptionsParser::save(const Options &options)
{
	// not done! 
	
	// Maybe make a "KvpTextMap::save(std::map, filename)" method?
	// What about custom comments per line? std::vector<std::string> would be better,
	// but that doesn't require KvpTextMap functionality then. There could be default
	// comments, like "# Graphics", etc..
}
