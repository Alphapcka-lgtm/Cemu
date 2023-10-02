#pragma once

#include <array>

#include <wx/frame.h>

class wxCheckBox;
class wxFlexGridSizer;
class wxNotebook;
class wxPanel;
class wxStaticBox;
class wxTextCtrl;

class EmulatedUSBDeviceFrame : public wxFrame {

public:
  EmulatedUSBDeviceFrame(wxWindow* parent);
  ~EmulatedUSBDeviceFrame();

private:
  wxWindow* m_parent;
  wxCheckBox* m_emulate_portal;
  std::array<wxTextCtrl*, 16> m_skylander_slots;
  std::array<std::optional<std::tuple<uint8, uint16, uint16>>, 16> sky_slots;

  wxPanel* AddSkylanderPage(wxNotebook* notebook);
  wxFlexGridSizer* AddSkylanderRow(uint8 row_number, wxStaticBox* box);
  void LoadSkylander(uint8 slot);
  void CreateSkylander(uint8 slot);
  void ClearSkylander(uint8 slot);
  void UpdateSkylanderEdits();
};