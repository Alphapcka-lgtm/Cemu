#pragma once

#include <wx/frame.h>
#include <wx/textctrl.h>

class wxPanel;
class wxNotebook;
class wxBoxSizer;
class wxTextCtrl;

class SkylanderChooser: public wxFrame {

  public:
	SkylanderChooser(wxWindow* parent, std::array<wxTextCtrl*, 16> skylander_slots, std::array<std::optional<std::tuple<uint8, uint16, uint16>>, 16> sky_slots,const std::map<const std::pair<const uint16, const uint16>, const std::string>* list_skylanders);
	~SkylanderChooser();

  private:
	struct Skylander
	{
		std::string imgUrl;
		std::string name;
		std::string fileUrl;
	};

	wxWindow* m_parent;
	std::array<wxTextCtrl*, 16> m_skylander_slots;
	std::array<std::optional<std::tuple<uint8, uint16, uint16>>, 16> m_sky_slots;
	std::map<const std::pair<const uint16, const uint16>, const std::string> m_list_skylanders;

	wxPanel* AddSpyrosAdventurePage(wxNotebook* notebook);
	wxPanel* AddGiantsPage(wxNotebook* notebook);
	wxPanel* AddSwapForcePage(wxNotebook* notebook);
	wxPanel* AddTrapTeamPage(wxNotebook* notebook);
	wxPanel* AddSuperChargersPage(wxNotebook* notebook);
	wxPanel* AddImaginatorsPage(wxNotebook* notebook);
<<<<<<< Updated upstream
	wxBoxSizer* CreateSkylanderElement(wxPanel* parent, Skylander* skylander);
=======

	wxBoxSizer* CreateSkylanderElement(wxPanel* parent, Skylander* skylander);
	void AddSkylandersToElementSizer(wxBoxSizer* elementSizer, wxPanel* parent, std::list<Skylander*> skylanders);
>>>>>>> Stashed changes

	void LoadSkylander(uint8 slot, std::string file);
	void CreateSkylander(uint8 slot);
	void ClearSkylander(uint8 slot);
	void UpdateSkylanderEdits();
};