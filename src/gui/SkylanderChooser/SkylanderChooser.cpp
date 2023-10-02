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

using std::string;

#include "Cafe/OS/libs/nsyshid/nsyshid.h"
#include "Cafe/OS/libs/nsyshid/Skylander.h"

#include "resource/embedded/resources.h"

const string skylanders_baseurl = "C:\\Users\\micha\\Documents\\Emulators\\Cemu POP\\skylanders";

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

wxPanel* SkylanderChooser::AddTrapTeamPage(wxNotebook* notebook) {
	string trapteam_path = skylanders_baseurl + "\\Skylanders Trap Team";

	auto* trapTeamPanel = new wxPanel(notebook);
	auto* trapTeamSizer = new wxGridBagSizer(0, 0);

	// water
	string water_path = trapteam_path + "\\Water";
	string water_symbol = water_path + "\\WaterSymbolSkylanders.png";
	auto* trapTeamWaterSizer = new wxBoxSizer(wxHORIZONTAL);
	auto* water_icon = new wxImage(water_symbol);
	water_icon->Rescale(100, 100);
	auto* water_element_icon = new wxStaticBitmap(trapTeamPanel, wxID_ANY, wxBitmapBundle::FromImage(*water_icon));
	trapTeamWaterSizer->Add(water_element_icon);
	trapTeamWaterSizer->AddSpacer(10);

	auto* snapShot = new Skylander();
	snapShot->name = "Snap Shot (Trap Master)";
	snapShot->imgUrl = "C:\\Users\\micha\\Downloads\\skylanders icons\\water\\Snap_Shot.png";
	snapShot->fileUrl = water_path + "\\Snap Shot.sky";
	//trapTeamWaterSizer->Add(snapShotSizer);
	trapTeamWaterSizer->Add(CreateSkylanderElement(trapTeamPanel, snapShot));
	trapTeamWaterSizer->AddSpacer(10);

	auto* lobStar = new Skylander();
	lobStar->name = "Lob Star (Trap Master)";
	lobStar->imgUrl = "C:\\Users\\micha\\Downloads\\skylanders icons\\water\\Lob_Star_Promo.png";
	lobStar->fileUrl = trapteam_path + "\\Lob Star.sky";
	trapTeamWaterSizer->Add(CreateSkylanderElement(trapTeamPanel, lobStar));
	trapTeamWaterSizer->AddSpacer(10);
	// trapTeamSizer->Add(btn_LobStar, wxGBPosition(0, 1));

	auto* tidalWaveGillGrunt = new Skylander();
	tidalWaveGillGrunt->name = "Tidel Wave Gill Grunt";
	tidalWaveGillGrunt->imgUrl = water_symbol;
	tidalWaveGillGrunt->fileUrl = water_path + "\\Tidal Wave Gill Grunt.sky";
	trapTeamWaterSizer->Add(CreateSkylanderElement(trapTeamPanel, tidalWaveGillGrunt));
	trapTeamWaterSizer->AddSpacer(10);

	auto* echo = new Skylander();
	echo->name = "Echo";
	echo->imgUrl = water_symbol;
	echo->fileUrl = water_path + "\\Echo.sky";
	trapTeamWaterSizer->Add(CreateSkylanderElement(trapTeamPanel, echo));
	trapTeamWaterSizer->AddSpacer(10);

	// undead
	auto* trapTeamUndeadSizer = new wxBoxSizer(wxHORIZONTAL);
	auto* imgKryptKing = new wxImage("C:\\Users\\micha\\Downloads\\skylanders icons\\undead\\Krypt_king.png");
	imgKryptKing->Rescale(100, 100);
	wxBitmapBundle kryptKingBitMap = wxBitmapBundle::FromImage(*imgKryptKing);
	auto* btn_KryptKing = new wxBitmapButton(trapTeamPanel, wxID_ANY, kryptKingBitMap);
	trapTeamUndeadSizer->Add(btn_KryptKing);
	// trapTeamSizer->Add(btn_KryptKing, wxGBPosition(1, 0));
	auto* imgShortCut = new wxImage("C:\\Users\\micha\\Downloads\\skylanders icons\\undead\\Short_Cut_Promo.png");
	imgShortCut->Rescale(100, 100);
	wxBitmapBundle shortCutBitmap = wxBitmapBundle::FromImage(*imgShortCut);
	auto* btn_ShortCut = new wxBitmapButton(trapTeamPanel, wxID_ANY, shortCutBitmap);
	trapTeamUndeadSizer->Add(btn_ShortCut);
	// trapTeamSizer->Add(btn_ShortCut, wxGBPosition(1, 1));

	trapTeamSizer->Add(trapTeamWaterSizer, wxGBPosition(0, 0));
	trapTeamSizer->Add(trapTeamUndeadSizer, wxGBPosition(1, 0));

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

wxBoxSizer* SkylanderChooser::CreateSkylanderElement(wxPanel* parent, Skylander* skylander) {
	auto* sizer = new wxBoxSizer(wxVERTICAL);
	auto* img = new wxImage(skylander->imgUrl);
	img->Rescale(100, 100);
	wxBitmapBundle bitmap = wxBitmapBundle::FromImage(*img);
	auto* button = new wxBitmapButton(parent, wxID_ANY, bitmap);
	button->Bind(wxEVT_BUTTON, [file = (skylander->fileUrl)](wxCommandEvent&) {
		printf("%s\n", file.c_str());
	});
	sizer->Add(button, wxSizerFlags(0).Align(wxALIGN_CENTER_HORIZONTAL));
	sizer->Add(new wxStaticText(parent, wxID_ANY, skylander->name), wxSizerFlags(0).Align(wxALIGN_CENTER_HORIZONTAL));

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