#include "SkylanderChooser.h"

#include <wx/bitmap.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/gbsizer.h>
#include <wx/bmpbuttn.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statbmp.h>
#include <wx/scrolwin.h>

using std::string;
using std::list;

#include "Cafe/OS/libs/nsyshid/nsyshid.h"
#include "Cafe/OS/libs/nsyshid/Skylander.h"

#include "resource/embedded/resources.h"

const string skylanders_baseurl = "C:\\Users\\micha\\Documents\\Emulators\\Cemu POP\\skylanders";
const int rescale_width = 50;
const int rescale_height = 50;
const int name_width = 75;

SkylanderChooser::SkylanderChooser(wxWindow* parent, std::array<wxTextCtrl*, 16> skylander_slots, std::array<std::optional<std::tuple<uint8, uint16, uint16>>, 16> sky_slots,const std::map<const std::pair<const uint16, const uint16>, const string>* list_skylanders)
	: wxFrame(parent, wxID_ANY, _("Skylanders Chooser")) {
	m_skylander_slots = skylander_slots;
	m_sky_slots = sky_slots;
	m_list_skylanders = *list_skylanders;

	SetIcon(wxICON(X_BOX));
	auto* sizer = new wxBoxSizer(wxHORIZONTAL);
	auto* notebook = new wxNotebook(this, wxID_ANY);

	notebook->AddPage(AddTrapTeamPage(notebook), "Trap Team");

	sizer->Add(notebook, 1, wxEXPAND | wxALL, 5);

	SetSizerAndFit(sizer);
	Layout();
	Center(wxBOTH);
}

SkylanderChooser::~SkylanderChooser(){}

wxScrolledWindow* SkylanderChooser::AddTrapTeamPage(wxNotebook* notebook)
{
	string trapteam_path = skylanders_baseurl + "\\Skylanders Trap Team";
	string minis_path = trapteam_path + "\\Minis";

	auto* trapTeamPanel = new wxScrolledWindow(notebook);
	trapTeamPanel->FitInside();
	trapTeamPanel->SetScrollRate(5, 5);
	auto* trapTeamSizer = new wxGridBagSizer(0, 0);

	// builds the sizer containing all the magic trap team skylanders
	auto magic = [trapteam_path, trapTeamPanel, minis_path, this](){
		string magic_path = trapteam_path + "\\Magic";
		string magic_symbol = magic_path + "\\MagicSymbolSkylanders.png";
		auto* magicSizer = new wxBoxSizer(wxHORIZONTAL);
		auto* magic_icon = new wxImage(magic_symbol);
		magic_icon->Rescale(rescale_width, rescale_height);
		auto* magic_element_icon = new wxStaticBitmap(trapTeamPanel, wxID_ANY, wxBitmapBundle::FromImage(*magic_icon));
		magicSizer->Add(magic_element_icon);
		magicSizer->AddSpacer(10);

		list<Skylander*> magicSkylanders;
		auto* blastermind = new Skylander();
		blastermind->name = "Bastermind (Trap Master)";
		blastermind->imgUrl = magic_symbol;
		blastermind->fileUrl = magic_path + "\\Blastermind.sky";
		magicSkylanders.push_back(blastermind);

		auto* enigma = new Skylander();
		enigma->name = "Enigma";
		enigma->imgUrl = magic_symbol;
		enigma->fileUrl = magic_path + "\\Enigma.sky";
		magicSkylanders.push_back(enigma);

		auto* fizzyFrenzyPopFizz = new Skylander();
		fizzyFrenzyPopFizz->name = "Fizzy Frenzy Pop Fizz";
		fizzyFrenzyPopFizz->imgUrl = magic_symbol;
		fizzyFrenzyPopFizz->fileUrl = magic_path + "\\Fizzy Frenzy Pop Fizz.sky";
		magicSkylanders.push_back(fizzyFrenzyPopFizz);
		auto* lovePotionPopFizz = new Skylander();
		lovePotionPopFizz->name = "Love Potion Pop Fizz";
		lovePotionPopFizz->imgUrl = magic_symbol;
		lovePotionPopFizz->fileUrl = magic_path + "\\Alternate types\\Love Potion Pop Fizz.sky";
		magicSkylanders.push_back(lovePotionPopFizz);

		auto* dejaVu = new Skylander();
		dejaVu->name = "Déjà Vu";
		dejaVu->imgUrl = magic_symbol;
		dejaVu->fileUrl = magic_path + "\\Deja Vu.sky";
		magicSkylanders.push_back(dejaVu);
		auto* legendDejaVu = new Skylander();
		legendDejaVu->name = "Legendary Déjà Vu";
		legendDejaVu->imgUrl = magic_symbol;
		legendDejaVu->fileUrl = magic_path + "\\Alternate types\\Legendary Deja Vu.sky";
		magicSkylanders.push_back(legendDejaVu);

		auto* cobraCadabra = new Skylander();
		cobraCadabra->name = "Cobra Cadabra";
		cobraCadabra->imgUrl = magic_symbol;
		cobraCadabra->fileUrl = magic_path + "\\Cobra Candabra.sky";
		magicSkylanders.push_back(cobraCadabra);
		auto* kingCobraCadabra = new Skylander();
		kingCobraCadabra->name = "King Cobra Cadabra";
		kingCobraCadabra->imgUrl = magic_symbol;
		kingCobraCadabra->fileUrl = magic_path + "\\Alternate types\\King Cobra Cadabra.sky";
		magicSkylanders.push_back(kingCobraCadabra);

		auto* eonsEliteSpyro = new Skylander();
		eonsEliteSpyro->name = "Eon's Elite Spyro";
		eonsEliteSpyro->imgUrl = magic_symbol;
		eonsEliteSpyro->fileUrl = magic_path + "\\Eon's Elite Spyro.sky";
		magicSkylanders.push_back(eonsEliteSpyro);

		auto* miniJini = new Skylander();
		miniJini->name = "Mini Jini (Mini)";
		miniJini->imgUrl = magic_symbol;
		miniJini->fileUrl = minis_path + "Mini-Jini.sky";
		magicSkylanders.push_back(miniJini);

		auto* spry = new Skylander();
		spry->name = "Spry (Mini)";
		spry->imgUrl = magic_symbol;
		spry->fileUrl = minis_path + "\\Spry.sky";
		magicSkylanders.push_back(spry);

		AddSkylandersToElementSizer(magicSizer, trapTeamPanel, magicSkylanders);
		return magicSizer;
	};

	// builds the sizer containing all the water trap team skylanders
	auto water = [trapTeamPanel, trapteam_path, minis_path, this]() {
		string water_path = trapteam_path + "\\Water";
		string water_symbol = water_path + "\\WaterSymbolSkylanders.png";
		auto* waterSizer = new wxBoxSizer(wxHORIZONTAL);
		auto* water_icon = new wxImage(water_symbol);
		water_icon->Rescale(rescale_width, rescale_height);
		auto* water_element_icon = new wxStaticBitmap(trapTeamPanel, wxID_ANY, wxBitmapBundle::FromImage(*water_icon));
		waterSizer->Add(water_element_icon);
		waterSizer->AddSpacer(10);

		list<Skylander*> waterSkylanders;
		auto* snapShot = new Skylander();
		snapShot->name = "Snap Shot (Trap Master)";
		snapShot->imgUrl = "C:\\Users\\micha\\Downloads\\skylanders icons\\water\\Snap_Shot.png";
		snapShot->fileUrl = water_path + "\\Snap Shot.sky";
		waterSkylanders.push_back(snapShot);
		auto* darkSnapShot = new Skylander();
		darkSnapShot->name = "Dark Snap Shot (Trap Master)";
		darkSnapShot->imgUrl = "C:\\Users\\micha\\Downloads\\skylanders icons\\water\\Snap_Shot.png";
		darkSnapShot->fileUrl = water_path + "\\Alternate types\\Dark Snap Shot.sky";
		waterSkylanders.push_back(darkSnapShot);

		auto* lobStar = new Skylander();
		lobStar->name = "Lob-Star (Trap Master)";
		lobStar->imgUrl = "C:\\Users\\micha\\Downloads\\skylanders icons\\water\\Lob_Star_Promo.png";
		lobStar->fileUrl = trapteam_path + "\\Lob Star.sky";
		waterSkylanders.push_back(lobStar);

		auto* winterLobStar = new Skylander();
		winterLobStar->name = "Winterfest Lob-Star (Trap Master)";
		winterLobStar->imgUrl = "C:\\Users\\micha\\Downloads\\skylanders icons\\water\\Lob_Star_Promo.png";
		winterLobStar->fileUrl = water_path + "\\Alternate types\\Winterfest Lob-Star.sky";
		waterSkylanders.push_back(winterLobStar);

		auto* tidalWaveGillGrunt = new Skylander();
		tidalWaveGillGrunt->name = "Tidel Wave Gill Grunt";
		tidalWaveGillGrunt->imgUrl = water_symbol;
		tidalWaveGillGrunt->fileUrl = water_path + "\\Tidal Wave Gill Grunt.sky";
		waterSkylanders.push_back(tidalWaveGillGrunt);

		auto* eonsEliteGillGrunt = new Skylander();
		eonsEliteGillGrunt->name = "Eon's Elite Gill Grunt";
		eonsEliteGillGrunt->imgUrl = water_symbol;
		eonsEliteGillGrunt->fileUrl = water_path + "\\Eon's Elite Gill Grunt.sky";
		waterSkylanders.push_back(eonsEliteGillGrunt);

		auto* echo = new Skylander();
		echo->name = "Echo";
		echo->imgUrl = water_symbol;
		echo->fileUrl = water_path + "\\Echo.sky";
		waterSkylanders.push_back(echo);

		auto* flipWreck = new Skylander();
		flipWreck->name = "Flip Wreck";
		flipWreck->imgUrl = water_symbol;
		flipWreck->fileUrl = water_path + "\\Flip Wreck.sky";
		waterSkylanders.push_back(flipWreck);

		auto* thumbling = new Skylander();
		thumbling->name = "Thumbling (Mini)";
		thumbling->imgUrl = water_symbol;
		thumbling->fileUrl = minis_path + "\\Thumpling.sky";
		waterSkylanders.push_back(thumbling);

		auto* gillRunt = new Skylander();
		gillRunt->name = "Gill Runt";
		gillRunt->imgUrl = water_symbol;
		gillRunt->fileUrl = minis_path + "\\Gill Runt.sky";
		waterSkylanders.push_back(gillRunt);

		AddSkylandersToElementSizer(waterSizer, trapTeamPanel, waterSkylanders);
		return waterSizer;
	};

	auto fire = [trapTeamPanel, trapteam_path, minis_path, this]() {
		string fire_path = trapteam_path + "\\Fire";
		string fire_symbol = fire_path + "\\FireSymbolSkylanders.png";
		auto* fireSizer = new wxBoxSizer(wxHORIZONTAL);
		auto* fireIcon = new wxImage(fire_symbol);
		fireIcon->Rescale(rescale_width, rescale_height);
		auto* fireIconBm = new wxStaticBitmap(trapTeamPanel, wxID_ANY, wxBitmapBundle::FromImage(*fireIcon));
		fireSizer->Add(fireIconBm);
		fireSizer->AddSpacer(10);

		list<Skylander*> fireSkylanders;
		auto* wildfire = new Skylander();
		wildfire->name = "Wildfire (Trap Master)";
		wildfire->imgUrl = fire_symbol;
		wildfire->fileUrl = fire_path + "\\Wildfire.sky"; 
		fireSkylanders.push_back(wildfire);
		auto* darkWildfire = new Skylander();
		darkWildfire->name = "Dark Wildfire (Trap Master)";
		darkWildfire->imgUrl = fire_symbol;
		darkWildfire->fileUrl = fire_path + "\\Alternate types\\Dark Wildfire.sky";
		fireSkylanders.push_back(darkWildfire);

		auto* kaBoom = new Skylander();
		kaBoom->name = "Ka-Boom (Trap Master)";
		kaBoom->imgUrl = fire_symbol;
		kaBoom->fileUrl = fire_path + "\\Ka Boom.sky";
		fireSkylanders.push_back(kaBoom);

		auto* hogWildFryno = new Skylander();
		hogWildFryno->name = "Hog Wild Fryno";
		hogWildFryno->imgUrl = fire_symbol;
		hogWildFryno->fileUrl = fire_path + "\\Hog Wild Fryno.sky";
		fireSkylanders.push_back(hogWildFryno);

		auto* torch = new Skylander();
		torch->name = "Torch";
		torch->imgUrl = fire_symbol;
		torch->fileUrl = fire_path + "\\Torch.sky";
		fireSkylanders.push_back(torch);

		auto* trailBlazer = new Skylander();
		trailBlazer->name = "Trail Blazer";
		trailBlazer->imgUrl = fire_symbol;
		trailBlazer->fileUrl = fire_path + "\\Trail Blazer.sky";
		fireSkylanders.push_back(trailBlazer);

		auto* eonsEliteEruptor = new Skylander();
		eonsEliteEruptor->name = "Eon's Elite Eruptor";
		eonsEliteEruptor->imgUrl = fire_symbol;
		eonsEliteEruptor->fileUrl = fire_path + "\\Eon's Elite Eruptor.sky";
		fireSkylanders.push_back(eonsEliteEruptor);

		auto* smallFry = new Skylander();
		smallFry->name = "Small Fry (Mini)";
		smallFry->imgUrl = fire_symbol;
		smallFry->fileUrl = minis_path + "\\Small Fry.sky";
		fireSkylanders.push_back(smallFry);

		auto* weeruptor = new Skylander();
		weeruptor->name = "Weeruptor (Mini)";
		weeruptor->imgUrl = fire_symbol;
		weeruptor->fileUrl = minis_path + "\\Weeruptor.sky";
		fireSkylanders.push_back(weeruptor);
		auto* eggcellentWeeruptor = new Skylander();
		eggcellentWeeruptor->name = "Eggcellent Weeruptor (Mini)";
		eggcellentWeeruptor->imgUrl = fire_symbol;
		eggcellentWeeruptor->fileUrl = minis_path + "\\Alternate types\\Eggcellent Weeruptor.sky";
		fireSkylanders.push_back(eggcellentWeeruptor);

		AddSkylandersToElementSizer(fireSizer, trapTeamPanel, fireSkylanders);
		return fireSizer;
	};

	auto life = [trapTeamPanel, trapteam_path, minis_path, this]() {
		string life_path = trapteam_path + "\\Life";
		string life_symbol = life_path + "\\LifeSymbolSkylanders.png";
		auto* life_sizer = new wxBoxSizer(wxHORIZONTAL);
		auto* life_icon = new wxImage(life_symbol);
		life_icon->Rescale(rescale_width, rescale_height);
		auto lifeIconBm = new wxStaticBitmap(trapTeamPanel, wxID_ANY, wxBitmapBundle::FromImage(*life_icon));
		life_sizer->Add(lifeIconBm);
		life_sizer->AddSpacer(10);

		list<Skylander*> lifeSkylander;
		auto* tuffLuck = new Skylander();
		tuffLuck->name = "Tuff Luck (Trap Master)";
		tuffLuck->imgUrl = life_symbol;
		tuffLuck->fileUrl = life_path + "\\Tuff Luck.sky";
		lifeSkylander.push_back(tuffLuck);

		auto* bushwhack = new Skylander();
		bushwhack->name = "Bushwhack (Trap Master)";
		bushwhack->imgUrl = life_symbol;
		bushwhack->fileUrl = life_path + "\\Bushwack.sky";
		lifeSkylander.push_back(bushwhack);
		auto* legendBushwhack = new Skylander();
		legendBushwhack->name = "Legendary Bushwhack (Trap Master)";
		legendBushwhack->imgUrl = life_symbol;
		legendBushwhack->fileUrl = life_path + "\\Alternate types\\Legendary Bushwack.sky";
		lifeSkylander.push_back(legendBushwhack);

		auto* sureShotShroomBoom = new Skylander();
		sureShotShroomBoom->name = "Sure Shot Shroom Boom";
		sureShotShroomBoom->imgUrl = life_symbol;
		sureShotShroomBoom->fileUrl = life_path + "\\Sure Shot Shroomboom.sky";
		lifeSkylander.push_back(sureShotShroomBoom);

		auto* foodFight = new Skylander();
		foodFight->name = "Food Fight";
		foodFight->imgUrl = life_symbol;
		foodFight->fileUrl = life_path + "\\Food Fight.sky";
		lifeSkylander.push_back(foodFight);
		auto* darkFoodFight = new Skylander();
		darkFoodFight->name = "Dark Food Fight";
		darkFoodFight->imgUrl = life_symbol;
		darkFoodFight->fileUrl = life_path + "\\Alternate types\\Dark Food Fight.sky";
		lifeSkylander.push_back(darkFoodFight);

		auto* highFive = new Skylander();
		highFive->name = "High Five";
		highFive->imgUrl = life_symbol;
		highFive->fileUrl = life_path + "\\High Five.sky";
		lifeSkylander.push_back(highFive);

		auto* eonsEliteStealthElf = new Skylander();
		eonsEliteStealthElf->name = "Eon's Elite Stealth Elf";
		eonsEliteStealthElf->imgUrl = life_symbol;
		eonsEliteStealthElf->fileUrl = life_path + "\\Eon's Elite Stealth Elf.sky";
		lifeSkylander.push_back(eonsEliteStealthElf);

		auto* whisperElf = new Skylander();
		whisperElf->name = "Whipser Elf (Mini)";
		whisperElf->imgUrl = life_symbol;
		whisperElf->fileUrl = minis_path + "\\Whisper Elf.sky";
		lifeSkylander.push_back(whisperElf);

		auto* barkley = new Skylander();
		barkley->name = "Barkley (Mini)";
		barkley->imgUrl = life_symbol;
		barkley->fileUrl = minis_path + "\\Barkley.sky";
		lifeSkylander.push_back(barkley);

		AddSkylandersToElementSizer(life_sizer, trapTeamPanel, lifeSkylander);
		return life_sizer;
	};

	auto air = [trapTeamPanel, trapteam_path, minis_path, this]() {
		string air_path = trapteam_path + "\\Air";
		string air_symbol = air_path + "\\AirSymbolSkylanders.png";
		auto* airSizer = new wxBoxSizer(wxHORIZONTAL);
		auto* AirIcon = new wxImage(air_symbol);
		AirIcon->Rescale(rescale_width, rescale_height);
		auto* airIconBm = new wxStaticBitmap(trapTeamPanel, wxID_ANY, wxBitmapBundle::FromImage(*AirIcon));
		airSizer->Add(airIconBm);
		airSizer->AddSpacer(10);
		
		list<Skylander*> airSkylander;
		auto* gusto = new Skylander();
		gusto->name = "Gusto (Trap Master)";
		gusto->imgUrl = air_symbol;
		gusto->fileUrl = air_path + "\\Gusto.sky";
		airSkylander.push_back(gusto);

		auto* thunderbolt = new Skylander();
		thunderbolt->name = "Thunderbolt (Trap Master)";
		thunderbolt->imgUrl = air_symbol;
		thunderbolt->fileUrl = air_path + "\\Thunderbolt.sky";
		airSkylander.push_back(thunderbolt);

		auto* jetVac = new Skylander();
		jetVac->name = "Full Blast Jet-Vac";
		jetVac->imgUrl = air_symbol;
		jetVac->fileUrl = air_path + "\\Full Blast Jet Vac.sky";
		airSkylander.push_back(jetVac);

		auto* flingKong = new Skylander();
		flingKong->name = "Fling Kong";
		flingKong->imgUrl = air_symbol;
		flingKong->fileUrl = air_path + "\\Fling Kong.sky";
		airSkylander.push_back(flingKong);

		auto* blades = new Skylander();
		blades->name = "Blades";
		blades->imgUrl = air_symbol;
		blades->fileUrl = air_path + "\\Blades.sky";
		airSkylander.push_back(blades);
		auto* legBlades = new Skylander();
		legBlades->name = "Legendary Blades";
		legBlades->imgUrl = air_symbol;
		legBlades->fileUrl = air_path + "\\Alternate types\\Legendary Blades.sky";
		airSkylander.push_back(legBlades);

		auto* eonsEliteWhilwind = new Skylander();
		eonsEliteWhilwind->name = "Eon's Elite Whirlwind";
		eonsEliteWhilwind->imgUrl = air_symbol;
		eonsEliteWhilwind->fileUrl = air_path + "\\Eon's Elite Whirlwind.sky";
		airSkylander.push_back(eonsEliteWhilwind);

		auto* petVac = new Skylander();
		petVac->name = "Pet Vac (Mini)";
		petVac->imgUrl = air_symbol;
		petVac->fileUrl = minis_path + "\\Pet Vac.sky";
		airSkylander.push_back(petVac);
		auto* ppVac = new Skylander();
		ppVac->name = "Power Punch Pet Vac (Mini)";
		ppVac->imgUrl = air_symbol;
		ppVac->fileUrl = minis_path + "\\Alternate types\\Power Punch Pet Vac.sky";
		airSkylander.push_back(ppVac);

		auto* breeze = new Skylander();
		breeze->name = "Breeze (Mini)";
		breeze->imgUrl = air_symbol;
		breeze->fileUrl = minis_path + "Breeze.sky";
		airSkylander.push_back(breeze);

		AddSkylandersToElementSizer(airSizer, trapTeamPanel, airSkylander);
		return airSizer;
	};

	auto tech = [trapTeamPanel, trapteam_path, minis_path, this]() {
		string tech_path = trapteam_path + "\\Tech";
		string tech_symbol = tech_path + "\\TechSymbolSkylanders.png";
		auto* techSizer = new wxBoxSizer(wxHORIZONTAL);
		auto* techIcon = new wxImage(tech_symbol);
		techIcon->Rescale(rescale_width, rescale_height);
		auto* techIconBm = new wxStaticBitmap(trapTeamPanel, wxID_ANY, wxBitmapBundle::FromImage(*techIcon));
		techSizer->Add(techIconBm);
		techSizer->AddSpacer(10);

		list<Skylander*> techSkylander;
		auto* jawbreaker = new Skylander();
		jawbreaker->name = "Jawbreaker (Trap Master)";
		jawbreaker->imgUrl = tech_symbol;
		jawbreaker->fileUrl = tech_path + "\\Jawbreaker.sky";
		techSkylander.push_back(jawbreaker);
		auto* legJawbreaker = new Skylander();
		legJawbreaker->name = "Legendary Jawbreaker (Trap Master)";
		legJawbreaker->imgUrl = tech_symbol;
		legJawbreaker->fileUrl = tech_path + "\\Alternate types\\Legendary Jawbreaker.sky";
		techSkylander.push_back(legJawbreaker);

		auto* gearshift = new Skylander();
		gearshift->name = "Gearshift (Trap Master)";
		gearshift->imgUrl = tech_symbol;
		gearshift->fileUrl = tech_path + "\\Gearshift.sky";
		techSkylander.push_back(gearshift);

		auto* treadHead = new Skylander();
		treadHead->name = "Tread Head";
		treadHead->imgUrl = tech_symbol;
		treadHead->fileUrl = tech_path + "\\Tread Head.sky";
		techSkylander.push_back(treadHead);

		auto* chopper = new Skylander();
		chopper->name = "Chopper";
		chopper->imgUrl = tech_symbol;
		chopper->fileUrl = tech_path + "\\Chopper.sky";
		techSkylander.push_back(chopper);

		auto* eonsEliteTriggerHappy = new Skylander();
		eonsEliteTriggerHappy->name = "Eon's Elite Trigger Happy";
		eonsEliteTriggerHappy->imgUrl = tech_symbol;
		eonsEliteTriggerHappy->fileUrl = tech_path + "\\Eon's Elite Trigger Happy.sky";
		techSkylander.push_back(eonsEliteTriggerHappy);

		auto* triggerSnappy = new Skylander();
		triggerSnappy->name = "Trigger Snappy (Mini)";
		triggerSnappy->imgUrl = tech_symbol;
		triggerSnappy->fileUrl = minis_path + "\\Trigger Snappy.sky";
		techSkylander.push_back(triggerSnappy);

		auto* drobit = new Skylander();
		drobit->name = "Drobit (Mini)";
		drobit->imgUrl = tech_symbol;
		drobit->fileUrl = minis_path + "\\Drobit.sky";
		techSkylander.push_back(drobit);

		AddSkylandersToElementSizer(techSizer, trapTeamPanel, techSkylander);
		return techSizer;
	};

	auto earth = [trapTeamPanel, trapteam_path, minis_path, this]() {
		string earth_path = trapteam_path + "\\Earth";
		string earth_symbol = earth_path + "\\EarthSymbolSkylanders.png";
		auto* earthSizer = new wxBoxSizer(wxHORIZONTAL);
		auto* earthIcon = new wxImage(earth_symbol);
		earthIcon->Rescale(rescale_width, rescale_height);
		auto* earthIconBm = new wxStaticBitmap(trapTeamPanel, wxID_ANY, wxBitmapBundle::FromImage(*earthIcon));
		earthSizer->Add(earthIconBm);
		earthSizer->AddSpacer(10);

		list<Skylander*> earthSkylander;

		auto* wallop = new Skylander();
		wallop->name = "Wallop (Trap Master)";
		wallop->imgUrl = earth_symbol;
		wallop->fileUrl = earth_path + "\\Wallop.sky";
		earthSkylander.push_back(wallop);

		auto* headRush = new Skylander();
		headRush->name = "Head Rush (Trap Master)";
		headRush->imgUrl = earth_symbol;
		headRush->fileUrl = earth_path + "\\Head Rush.sky";
		earthSkylander.push_back(headRush);
		auto* nitroHeadRush = new Skylander();
		nitroHeadRush->name = "Nitro Head Rush (Trap Master)";
		nitroHeadRush->imgUrl = earth_symbol;
		nitroHeadRush->fileUrl = earth_path + "\\Alternate types\\Nitro Head Rush.sky";
		earthSkylander.push_back(nitroHeadRush);

		auto* rockyRoll = new Skylander();
		rockyRoll->name = "Rocky Roll";
		rockyRoll->imgUrl = earth_symbol;
		rockyRoll->fileUrl = earth_path + "\\Rocky Roll.sky";
		earthSkylander.push_back(rockyRoll);

		auto* fistBump = new Skylander();
		fistBump->name = "Fist Bump";
		fistBump->imgUrl = earth_symbol;
		fistBump->fileUrl = earth_path + "\\Fist Bump.sky";
		earthSkylander.push_back(fistBump);

		auto* eonsEliteTerrafin = new Skylander();
		eonsEliteTerrafin->name = "Eon's Elite Terrafin";
		eonsEliteTerrafin->imgUrl = earth_symbol;
		eonsEliteTerrafin->fileUrl = earth_path + "\\Eon's Elite Terrafin.sky";
		earthSkylander.push_back(eonsEliteTerrafin);

		auto* terrabite = new Skylander();
		terrabite->name = "Terrabite (Mini)";
		terrabite->imgUrl = earth_symbol;
		terrabite->fileUrl = minis_path + "\\Terrabite.sky";
		earthSkylander.push_back(terrabite);

		auto* bop = new Skylander();
		bop->name = "Bop (Mini)";
		bop->imgUrl = earth_symbol;
		bop->fileUrl = minis_path + "\\Bop.sky";
		earthSkylander.push_back(bop);

		AddSkylandersToElementSizer(earthSizer, trapTeamPanel, earthSkylander);
		return earthSizer;
	};

	// builds the sizer containing all the undead trap team skylanders
	auto undead = [trapTeamPanel, trapteam_path, minis_path, this]()-> wxBoxSizer* {
		string undead_path = trapteam_path + "\\Undead";
		string undead_symbol = undead_path + "\\UndeadSymbolSkylanders.png";
		auto* undeadSizer = new wxBoxSizer(wxHORIZONTAL);
		auto* undead_icon = new wxImage(undead_symbol);
		undead_icon->Rescale(rescale_width, rescale_width);
		auto* undead_element_icon = new wxStaticBitmap(trapTeamPanel, wxID_ANY, wxBitmapBundle::FromImage(*undead_icon));
		undeadSizer->Add(undead_element_icon);
		undeadSizer->AddSpacer(10);

		list<Skylander*> undeadSkylanders;
		auto* kryptKing = new Skylander();
		kryptKing->name = "Krypt King (Trap Master)";
		kryptKing->imgUrl = "C:\\Users\\micha\\Downloads\\skylanders icons\\undead\\Krypt_king.png";
		kryptKing->fileUrl = undead_path + "Krypt King.sky";
		undeadSkylanders.push_back(kryptKing);

		auto* nitroKryptKing = new Skylander();
		nitroKryptKing->name = "Nitro Krypt King (Trap Master)";
		nitroKryptKing->imgUrl = "C:\\Users\\micha\\Downloads\\skylanders icons\\undead\\Krypt_king.png";
		nitroKryptKing->fileUrl = undead_path + "\\Alternate types\\Nitro Krypt King.sky";
		undeadSkylanders.push_back(nitroKryptKing);

		auto* shortCut = new Skylander();
		shortCut->name = "Short Cut (Trap Master)";
		shortCut->imgUrl = "C:\\Users\\micha\\Downloads\\skylanders icons\\undead\\Short_Cut_Promo.png";
		shortCut->fileUrl = undead_path + "\\Short Cut.sky";
		undeadSkylanders.push_back(shortCut);

		auto* funnyBone = new Skylander();
		funnyBone->name = "Funny Bone";
		funnyBone->imgUrl = undead_symbol;
		funnyBone->fileUrl = undead_path + "\\Funny Bone.sky";
		undeadSkylanders.push_back(funnyBone);

		auto* batSpin = new Skylander();
		batSpin->name = "Bat Spin";
		batSpin->imgUrl = undead_symbol;
		batSpin->fileUrl = undead_path + "\\Bat Spin.sky";
		undeadSkylanders.push_back(batSpin);

		auto* eonsEliteChopChop = new Skylander();
		eonsEliteChopChop->name = "Eon's Elite Chop Chop";
		eonsEliteChopChop->imgUrl = undead_symbol;
		eonsEliteChopChop->fileUrl = undead_path + "\\Eon's Elite Chop Chop.sky";
		undeadSkylanders.push_back(eonsEliteChopChop);

		auto* hijinx = new Skylander();
		hijinx->name = "Hijinx (Mini)";
		hijinx->imgUrl = undead_symbol;
		hijinx->fileUrl = undead_path + "\\Hijinx.sky";
		undeadSkylanders.push_back(hijinx);

		auto* eyeSmall = new Skylander();
		eyeSmall->name = "Eye Small (Mini)";
		eyeSmall->imgUrl = undead_symbol;
		eyeSmall->fileUrl = minis_path + "\\Eye Small.sky";
		undeadSkylanders.push_back(eyeSmall);

		AddSkylandersToElementSizer(undeadSizer, trapTeamPanel, undeadSkylanders);
		return undeadSizer;
	};

	auto light = [trapTeamPanel, trapteam_path, minis_path, this]() {
		string light_path = trapteam_path + "\\Light";
		string light_symbol = light_path + "\\LightSymbolSkylanders.png";
		auto* lightSizer = new wxBoxSizer(wxHORIZONTAL);
		auto* lightIcon = new wxImage(light_symbol);
		lightIcon->Rescale(rescale_width, rescale_height);
		auto* fireIconBm = new wxStaticBitmap(trapTeamPanel, wxID_ANY, wxBitmapBundle::FromImage(*lightIcon));
		lightSizer->Add(fireIconBm);
		lightSizer->AddSpacer(10);

		list<Skylander*> lightSkylander;

		auto* knightLight = new Skylander();
		knightLight->name = "Knight Light (Trap Master)";
		knightLight->imgUrl = light_symbol;
		knightLight->fileUrl = light_path + "\\Knight Light.sky";
		lightSkylander.push_back(knightLight);

		auto* spotlight = new Skylander();
		spotlight->name = "Spotlight";
		spotlight->imgUrl = light_symbol;
		spotlight->fileUrl = light_path + "\\Spotlight.sky";
		lightSkylander.push_back(spotlight);

		AddSkylandersToElementSizer(lightSizer, trapTeamPanel, lightSkylander);
		return lightSizer;
	};

	auto dark = [trapTeamPanel, trapteam_path, minis_path, this]() {
		string dark_path = trapteam_path + "\\Dark";
		string dark_symbol = dark_path + "\\DarkSymbolSkylanders.png";
		auto* darkSizer = new wxBoxSizer(wxHORIZONTAL);
		auto* darkIcon = new wxImage(dark_symbol);
		darkIcon->Rescale(rescale_width, rescale_height);
		auto* darkIconBm = new wxStaticBitmap(trapTeamPanel, wxID_ANY, wxBitmapBundle::FromImage(*darkIcon));
		darkSizer->Add(darkIconBm);
		darkSizer->AddSpacer(10);

		list<Skylander*> darkSkylander;

		auto* knightMare = new Skylander();
		knightMare->name = "Knight Mare (Trap Master)";
		knightMare->imgUrl = dark_symbol;
		knightMare->fileUrl = dark_path + "\\Knight Mare.sky";
		darkSkylander.push_back(knightMare);

		auto* blackout = new Skylander();
		blackout->name = "Blackout";
		blackout->imgUrl = dark_symbol;
		blackout->fileUrl = dark_path + "\\Blackout.sky";
		darkSkylander.push_back(blackout);

		AddSkylandersToElementSizer(darkSizer, trapTeamPanel, darkSkylander);
		return darkSizer;
	};

	trapTeamSizer->Add(magic(), wxGBPosition(0, 0));
	trapTeamSizer->Add(water(), wxGBPosition(1, 0));
	trapTeamSizer->Add(fire(), wxGBPosition(2, 0));
	trapTeamSizer->Add(life(), wxGBPosition(3, 0));
	trapTeamSizer->Add(air(), wxGBPosition(4, 0));
	trapTeamSizer->Add(tech(), wxGBPosition(5, 0));
	trapTeamSizer->Add(earth(), wxGBPosition(6, 0));
	trapTeamSizer->Add(undead(), wxGBPosition(7, 0));
	trapTeamSizer->Add(light(), wxGBPosition(8, 0));
	trapTeamSizer->Add(dark(), wxGBPosition(9, 0));

	trapTeamSizer->SetFlexibleDirection(wxBOTH);
	// trapTeamSizer->AddGrowableCol(0);
	// trapTeamSizer->AddGrowableCol(1);
	// trapTeamSizer->AddGrowableRow(0);
	// trapTeamSizer->AddGrowableRow(1);
	// trapTeamSizer->AddGrowableRow(2);
	// trapTeamSizer->AddGrowableRow(3);
	// trapTeamSizer->AddGrowableRow(4);

	trapTeamPanel->SetSizerAndFit(trapTeamSizer);

	return trapTeamPanel;
}

void SkylanderChooser::AddSkylandersToElementSizer(wxBoxSizer* elementSizer, wxPanel* parent, std::list<Skylander*> skylanders) {
	for (auto const& sky : skylanders)
	{
		elementSizer->Add(CreateSkylanderElement(parent, sky));
		elementSizer->AddSpacer(10);
	}
}

wxBoxSizer* SkylanderChooser::CreateSkylanderElement(wxPanel* parent, Skylander* skylander) {
	auto* sizer = new wxBoxSizer(wxVERTICAL);
	auto* img = new wxImage(skylander->imgUrl);
	img->Rescale(rescale_width, rescale_height);
	wxBitmapBundle bitmap = wxBitmapBundle::FromImage(*img);
	auto* button = new wxBitmapButton(parent, wxID_ANY, bitmap);
	button->Bind(wxEVT_BUTTON, [file = (skylander->fileUrl)](wxCommandEvent&) {
		printf("%s\n", file.c_str());
	});
	sizer->Add(button, wxSizerFlags(0).Align(wxALIGN_CENTER_HORIZONTAL));
	auto* text = new wxStaticText(parent, wxID_ANY, skylander->name);
	text->Wrap(name_width);
	sizer->Add(text, wxSizerFlags(0).Align(wxALIGN_CENTER_HORIZONTAL));

	return sizer;
}

void SkylanderChooser::LoadSkylander(uint8 slot, std::string filename)
{
	FILE* sky_file = std::fopen(filename.c_str(), "r+b");
	if (!sky_file)
	{
		return;
	}

	std::array<uint8, 0x40 * 0x10> file_data;
	size_t read_count = std::fread(&file_data[0], sizeof(file_data[0]),
								   file_data.size(), sky_file);
	if (read_count != file_data.size())
	{
		return;
	}
	ClearSkylander(slot);

	uint16 sky_id = uint16(file_data[0x11]) << 8 | uint16(file_data[0x10]);
	uint16 sky_var = uint16(file_data[0x1D]) << 8 | uint16(file_data[0x1C]);

	uint8 portal_slot = nsyshid::g_skyportal.load_skylander(file_data.data(),
															std::move(sky_file));
	m_sky_slots[slot] = std::tuple(portal_slot, sky_id, sky_var);
	UpdateSkylanderEdits();
}

void SkylanderChooser::CreateSkylander(uint8 slot){
	cemuLog_log(LogType::Force, "Create Skylander: {}", slot);
}

void SkylanderChooser::ClearSkylander(uint8 slot)
{
	if (auto slot_infos = m_sky_slots[slot])
	{
		auto [cur_slot, id, var] = slot_infos.value();
		nsyshid::g_skyportal.remove_skylander(cur_slot);
		m_sky_slots[slot] = {};
		UpdateSkylanderEdits();
	}
}

void SkylanderChooser::UpdateSkylanderEdits(){
	for (auto i = 0; i < 16; i++)
	{
		std::string display_string;
		if (auto sd = m_sky_slots[i])
		{
			auto [portal_slot, sky_id, sky_var] = sd.value();
			auto found_sky = m_list_skylanders.find(std::make_pair(sky_id, sky_var));
			if (found_sky != m_list_skylanders.end())
			{
				display_string = found_sky->second;
			}
			else
			{
				display_string = fmt::format("Unknown (Id:{} Var:{})", sky_id, sky_var);
			}
		}
		else
		{
			display_string = "None";
		}

		m_skylander_slots[i]->ChangeValue(display_string);
	}
}