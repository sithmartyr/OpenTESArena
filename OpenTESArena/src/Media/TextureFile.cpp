#include <cassert>
#include <unordered_map>

#include "TextureFile.h"

#include "TextureName.h"
#include "TextureSequenceName.h"

namespace std
{
	// Hash specializations, since GCC doesn't support enum classes used as keys
	// in unordered_maps.
	template <>
	struct hash<TextureName>
	{
		size_t operator()(const TextureName &x) const
		{
			return static_cast<size_t>(x);
		}
	};

	template <>
	struct hash<TextureSequenceName>
	{
		size_t operator()(const TextureSequenceName &x) const
		{
			return static_cast<size_t>(x);
		}
	};
}

namespace
{
	// The filename of each TextureName, by type.
	const std::unordered_map<TextureName, std::string> TextureFilenames =
	{
		// Character heads for the character sheet.	
		{ TextureName::FemaleArgonianHeads, "FACESF17.CIF" },
		{ TextureName::FemaleBretonHeads, "FACESF10.CIF" },
		{ TextureName::FemaleDarkElfHeads, "FACESF13.CIF" },
		{ TextureName::FemaleHighElfHeads, "FACESF14.CIF" },
		{ TextureName::FemaleKhajiitHeads, "FACESF16.CIF" },
		{ TextureName::FemaleNordHeads, "FACESF12.CIF" },
		{ TextureName::FemaleRedguardHeads, "FACESF11.CIF" },
		{ TextureName::FemaleWoodElfHeads, "FACESF15.CIF" },
		{ TextureName::MaleArgonianHeads, "FACES17.CIF" },
		{ TextureName::MaleBretonHeads, "FACES10.CIF" },
		{ TextureName::MaleDarkElfHeads, "FACES13.CIF" },
		{ TextureName::MaleHighElfHeads, "FACES14.CIF" },
		{ TextureName::MaleKhajiitHeads, "FACES16.CIF" },
		{ TextureName::MaleNordHeads, "FACES12.CIF" },
		{ TextureName::MaleRedguardHeads, "FACES11.CIF" },
		{ TextureName::MaleWoodElfHeads, "FACES15.CIF" },

		// Character heads for the in-game interface.
		{ TextureName::FemaleArgonianTrimmedHeads, "FACESF07.CIF" },
		{ TextureName::FemaleBretonTrimmedHeads, "FACESF00.CIF" },
		{ TextureName::FemaleDarkElfTrimmedHeads, "FACESF03.CIF" },
		{ TextureName::FemaleHighElfTrimmedHeads, "FACESF04.CIF" },
		{ TextureName::FemaleKhajiitTrimmedHeads, "FACESF06.CIF" },
		{ TextureName::FemaleNordTrimmedHeads, "FACESF02.CIF" },
		{ TextureName::FemaleRedguardTrimmedHeads, "FACESF01.CIF" },
		{ TextureName::FemaleWoodElfTrimmedHeads, "FACESF05.CIF" },
		{ TextureName::MaleArgonianTrimmedHeads, "FACES07.CIF" },
		{ TextureName::MaleBretonTrimmedHeads, "FACES00.CIF" },
		{ TextureName::MaleDarkElfTrimmedHeads, "FACES03.CIF" },
		{ TextureName::MaleHighElfTrimmedHeads, "FACES04.CIF" },
		{ TextureName::MaleKhajiitTrimmedHeads, "FACES06.CIF" },
		{ TextureName::MaleNordTrimmedHeads, "FACES02.CIF" },
		{ TextureName::MaleRedguardTrimmedHeads, "FACES01.CIF" },
		{ TextureName::MaleWoodElfTrimmedHeads, "FACES05.CIF" },

		// Character backgrounds (without clothes).
		{ TextureName::FemaleArgonianBackground, "CHRBKF07.IMG" },
		{ TextureName::FemaleBretonBackground, "CHRBKF00.IMG" },
		{ TextureName::FemaleDarkElfBackground, "CHRBKF03.IMG" },
		{ TextureName::FemaleHighElfBackground, "CHRBKF04.IMG" },
		{ TextureName::FemaleKhajiitBackground, "CHRBKF06.IMG" },
		{ TextureName::FemaleNordBackground, "CHRBKF02.IMG" },
		{ TextureName::FemaleRedguardBackground, "CHRBKF01.IMG" },
		{ TextureName::FemaleWoodElfBackground, "CHRBKF05.IMG" },
		{ TextureName::MaleArgonianBackground, "CHARBK07.IMG" },
		{ TextureName::MaleBretonBackground, "CHARBK00.IMG" },
		{ TextureName::MaleDarkElfBackground, "CHARBK03.IMG" },
		{ TextureName::MaleHighElfBackground, "CHARBK04.IMG" },
		{ TextureName::MaleKhajiitBackground, "CHARBK06.IMG" },
		{ TextureName::MaleNordBackground, "CHARBK02.IMG" },
		{ TextureName::MaleRedguardBackground, "CHARBK01.IMG" },
		{ TextureName::MaleWoodElfBackground, "CHARBK05.IMG" },

		// Cursors.
		{ TextureName::ArrowCursors, "ARROWS.CIF" },
		{ TextureName::QuillCursor, "POINTER.IMG" },
		{ TextureName::SwordCursor, "ARENARW.IMG" },

		// Equipment overlays.
		{ TextureName::FemaleEquipment, "1EQUIP.CIF" },
		{ TextureName::FemaleHelmet, "1ARGHELM.IMG" },
		{ TextureName::FemaleNonMagicShirt, "FSSHIRT.IMG" },
		{ TextureName::FemaleMagicShirt, "FRSHIRT.IMG" },
		{ TextureName::FemaleDemoTop, "TOP.IMG" },
		{ TextureName::FemalePants, "FPANTS.IMG" },
		{ TextureName::MaleEquipment, "0EQUIP.CIF" },
		{ TextureName::MaleHelmet, "0ARGHELM.IMG" },
		{ TextureName::MaleNonMagicShirt, "MSSHIRT.IMG" },
		{ TextureName::MaleMagicShirt, "MRSHIRT.IMG" },
		{ TextureName::MalePants, "MPANTS.IMG" },

		// Interface.
		{ TextureName::AcceptReject, "ACCPREJT.IMG" },
		{ TextureName::AcceptCounterReject, "NEGOTBUT.IMG" },
		{ TextureName::AddJobStatusCancel, "NEWOLD.IMG" },
		{ TextureName::BarterBackground, "MENUSCRN.IMG" },
		{ TextureName::BonusPointsText, "BONUS.IMG" },
		{ TextureName::Brass, "BRASS.CIF" },
		{ TextureName::Brass2, "BRASS2.CIF" },
		{ TextureName::CharacterCreation, "STARTGAM.MNU" },
		{ TextureName::CharacterEquipment, "EQUIP.IMG" },
		{ TextureName::CharacterStats, "CHARSTAT.IMG" },
		{ TextureName::CompassFrame, "COMPASS.IMG" },
		{ TextureName::CompassSlider, "SLIDER.IMG" },
		{ TextureName::GameWorldInterface, "P1.IMG" },
		{ TextureName::IntroTitle, "TITLE.IMG" },
		{ TextureName::IntroQuote, "QUOTE.IMG" },
		{ TextureName::LoadSave, "LOADSAVE.IMG" },
		{ TextureName::Logbook, "LOGBOOK.IMG" },
		{ TextureName::MainMenu, "MENU.IMG" },
		{ TextureName::Marble, "MARBLE.CIF" },
		{ TextureName::Marble2, "MARBLE2.CIF" },
		{ TextureName::NextPage, "PAGE2.IMG" },
		{ TextureName::NoExit, "NOEXIT.IMG" },
		{ TextureName::NoSpell, "NOSPELL.IMG" },
		{ TextureName::Parchment, "PARCH.CIF" },
		{ TextureName::ParchmentBig, "PARCH.IMG" },
		{ TextureName::PauseBackground, "OP.IMG" },
		{ TextureName::PopUp, "POPUP.IMG" },
		{ TextureName::PopUp2, "POPUP2.IMG" },
		{ TextureName::PopUp11, "POPUP11.IMG" },
		{ TextureName::RaceSelect, "TAMRIEL.MNU" },
		{ TextureName::Scroll, "SCROLL.CIF" },
		{ TextureName::SpellbookText, "SPELLBK.IMG" },
		{ TextureName::StatusGradients, "STATUS.CIF" },
		{ TextureName::UpDown, "UPDOWN.IMG" },
		{ TextureName::YesNoCancel, "YESNO.IMG" },

		// Main quest dungeon splash screens.
		{ TextureName::CryptOfHeartsSplash, "CRYPT.IMG" },
		{ TextureName::CrystalTowerSplash, "TOWER.IMG" },
		{ TextureName::DagothUrSplash, "DAGOTHUR.IMG" },
		{ TextureName::EldenGroveSplash, "GROVE.IMG" },
		{ TextureName::FangLairSplash, "FANGLAIR.IMG" },
		{ TextureName::HallsOfColossusSplash, "COLOSSUS.IMG" },
		{ TextureName::LabyrinthianSplash, "LABRINTH.IMG" },
		{ TextureName::MurkwoodSplash, "MIRKWOOD.IMG" },

		// Maps.
		{ TextureName::Automap, "AUTOMAP.IMG" },
		{ TextureName::BlackMarshMap, "BLAKMRSH.IMG" },
		{ TextureName::ElsweyrMap, "ELSWEYR.IMG" },
		{ TextureName::HammerfellMap, "HAMERFEL.IMG" },
		{ TextureName::HighRockMap, "HIGHROCK.IMG" },
		{ TextureName::ImperialProvinceMap, "IMPERIAL.IMG" },
		{ TextureName::MorrowindMap, "MOROWIND.IMG" },
		{ TextureName::SkyrimMap, "SKYRIM.IMG" },
		{ TextureName::SummersetIsleMap, "SUMERSET.IMG" },
		{ TextureName::ValenwoodMap, "VALNWOOD.IMG" },
		{ TextureName::WorldMap, "TAMRIEL.MNU" },

		// Map icons.
		{ TextureName::CityStateIcon, "CITY.IMG" },
		{ TextureName::DungeonIcon, "DUNGEON.IMG" },
		{ TextureName::TownIcon, "TOWN.IMG" },
		{ TextureName::VillageIcon, "VILLAGE.IMG" },

		// Spellbook and spellmaker.
		{ TextureName::BuySpellBackground, "BUYSPELL.IMG" },
		{ TextureName::Form1, "FORM1.IMG" },
		{ TextureName::Form2, "FORM2.IMG" },
		{ TextureName::Form3, "FORM3.IMG" },
		{ TextureName::Form4, "FORM4.IMG" },
		{ TextureName::Form4A, "FORM4A.IMG" },
		{ TextureName::Form5, "FORM5.IMG" },
		{ TextureName::Form6, "FORM6.IMG" },
		{ TextureName::Form6A, "FORM6A.IMG" },
		{ TextureName::Form7, "FORM7.IMG" },
		{ TextureName::Form8, "FORM8.IMG" },
		{ TextureName::Form9, "FORM9.IMG" },
		{ TextureName::Form10, "FORM10.IMG" },
		{ TextureName::Form11, "FORM11.IMG" },
		{ TextureName::Form12, "FORM12.IMG" },
		{ TextureName::Form13, "FORM13.IMG" },
		{ TextureName::Form14, "FORM14.IMG" },
		{ TextureName::Form15, "FORM15.IMG" },
		{ TextureName::SpellMakerBackground, "SPELLMKR.IMG" },

		// Weapon animations.
		{ TextureName::ArrowsAnimation, "ARROWHLF.CFA" },
		{ TextureName::AxeAnimation, "AXE.CIF" },
		{ TextureName::ChainAnimation, "CHAIN.CIF" },
		{ TextureName::FistsAnimation, "HAND.CIF" },
		{ TextureName::FlailAnimation, "STAR.CIF" },
		{ TextureName::HammerAnimation, "HAMMER.CIF" },
		{ TextureName::MaceAnimation, "MACE.CIF" },
		{ TextureName::PlateAnimation, "PLATE.CIF" },
		{ TextureName::StaffAnimation, "STAFF.CIF" },
		{ TextureName::SwordAnimation, "SWORD.CIF" }
	};

	// The filename of each TextureSequenceName.
	const std::unordered_map<TextureSequenceName, std::string> TextureSequenceFilenames =
	{
		{ TextureSequenceName::ChaosVision, "CHAOSVSN.FLC" },
		{ TextureSequenceName::End01, "END01.FLC" },
		{ TextureSequenceName::End02, "END02.FLC" },
		{ TextureSequenceName::Jagar, "JAGAR.FLC" },
		{ TextureSequenceName::JagarDeath, "JAGARDTH.FLC" },
		{ TextureSequenceName::JagarShield, "JAGRSHLD.FLC" },
		{ TextureSequenceName::King, "KING.FLC" },
		{ TextureSequenceName::Mage, "MAGE.CEL" },
		{ TextureSequenceName::Morph, "MORPH.FLC" },
		{ TextureSequenceName::OpeningScroll, "SCROLL.FLC" },
		{ TextureSequenceName::Rogue, "ROGUE.CEL" },
		{ TextureSequenceName::Silmane, "VISION.FLC" },
		{ TextureSequenceName::Warhaft, "WARHAFT.FLC" },
		{ TextureSequenceName::Warrior, "WARRIOR.CEL" }
	};
}

const std::string &TextureFile::fromName(TextureName textureName)
{
	const auto &filename = TextureFilenames.at(textureName);
	return filename;
}

const std::string &TextureFile::fromName(TextureSequenceName sequenceName)
{
	const auto &filename = TextureSequenceFilenames.at(sequenceName);
	return filename;
}
