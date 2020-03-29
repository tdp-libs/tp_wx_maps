#include "tp_wx_maps/OpenGLConfig.h"

#include "tp_utils/DebugUtils.h"

namespace tp_wx_maps
{

//##################################################################################################
struct OpenGLConfig::Private
{
  tp_maps::OpenGLConfig config;

  wxChoice* profileCombo{nullptr};
  wxChoice* depthCombo{nullptr};

  //################################################################################################
  int indexFromProfile(tp_maps::OpenGLProfile profile)
  {
    switch(profile)
    {
    case tp_maps::OpenGLProfile::VERSION_110    : return  0;
    case tp_maps::OpenGLProfile::VERSION_120    : return  1;
    case tp_maps::OpenGLProfile::VERSION_130    : return  2;
    case tp_maps::OpenGLProfile::VERSION_140    : return  3;
    case tp_maps::OpenGLProfile::VERSION_150    : return  4;
    case tp_maps::OpenGLProfile::VERSION_330    : return  5;
    case tp_maps::OpenGLProfile::VERSION_400    : return  6;
    case tp_maps::OpenGLProfile::VERSION_410    : return  7;
    case tp_maps::OpenGLProfile::VERSION_420    : return  8;
    case tp_maps::OpenGLProfile::VERSION_430    : return  9;
    case tp_maps::OpenGLProfile::VERSION_440    : return 10;
    case tp_maps::OpenGLProfile::VERSION_450    : return 11;
    case tp_maps::OpenGLProfile::VERSION_460    : return 12;
    case tp_maps::OpenGLProfile::VERSION_100_ES : return 13;
    case tp_maps::OpenGLProfile::VERSION_300_ES : return 14;
    case tp_maps::OpenGLProfile::VERSION_310_ES : return 15;
    case tp_maps::OpenGLProfile::VERSION_320_ES : return 16;
    }
    return 0;
  }

  //################################################################################################
  tp_maps::OpenGLProfile indexToProfile(int index)
  {
    switch(index)
    {
    case  0 : return tp_maps::OpenGLProfile::VERSION_110   ;
    case  1 : return tp_maps::OpenGLProfile::VERSION_120   ;
    case  2 : return tp_maps::OpenGLProfile::VERSION_130   ;
    case  3 : return tp_maps::OpenGLProfile::VERSION_140   ;
    case  4 : return tp_maps::OpenGLProfile::VERSION_150   ;
    case  5 : return tp_maps::OpenGLProfile::VERSION_330   ;
    case  6 : return tp_maps::OpenGLProfile::VERSION_400   ;
    case  7 : return tp_maps::OpenGLProfile::VERSION_410   ;
    case  8 : return tp_maps::OpenGLProfile::VERSION_420   ;
    case  9 : return tp_maps::OpenGLProfile::VERSION_430   ;
    case 10 : return tp_maps::OpenGLProfile::VERSION_440   ;
    case 11 : return tp_maps::OpenGLProfile::VERSION_450   ;
    case 12 : return tp_maps::OpenGLProfile::VERSION_460   ;
    case 13 : return tp_maps::OpenGLProfile::VERSION_100_ES;
    case 14 : return tp_maps::OpenGLProfile::VERSION_300_ES;
    case 15 : return tp_maps::OpenGLProfile::VERSION_310_ES;
    case 16 : return tp_maps::OpenGLProfile::VERSION_320_ES;
    }
    return TP_DEFAULT_PROFILE;
  }

  //################################################################################################
  int indexFromDepth(tp_maps::OpenGLDepth depth)
  {
    switch(depth)
    {
    case tp_maps::OpenGLDepth::OFF   : return 0;
    case tp_maps::OpenGLDepth::ON_16 : return 1;
    case tp_maps::OpenGLDepth::ON_24 : return 2;
    case tp_maps::OpenGLDepth::ON_32 : return 3;
    }
    return 0;
  }

  //################################################################################################
  tp_maps::OpenGLDepth indexToDepth(int index)
  {
    switch(index)
    {
    case 0 : return tp_maps::OpenGLDepth::OFF  ;
    case 1 : return tp_maps::OpenGLDepth::ON_16;
    case 2 : return tp_maps::OpenGLDepth::ON_24;
    case 3 : return tp_maps::OpenGLDepth::ON_32;
    }
    return tp_maps::OpenGLDepth::ON_16;
  }

  //################################################################################################
  void updateUI()
  {
    profileCombo->SetSelection(indexFromProfile(config.profile));
    depthCombo->SetSelection(indexFromDepth(config.depth));
  }
};

//##################################################################################################
OpenGLConfig::OpenGLConfig(wxWindow* parent,
                           wxWindowID id):
  wxPanel(parent, id),
  d(new Private())
{
  wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

  auto label = [&](const std::string& text)
  {
    return new wxStaticText(this, wxID_ANY, wxString::FromUTF8(text.c_str()));
  };

  vbox->Add(label("Profile"));
  d->profileCombo = new wxChoice(this, wxID_ANY);
  d->profileCombo->Append("VERSION_110");
  d->profileCombo->Append("VERSION_120");
  d->profileCombo->Append("VERSION_130");
  d->profileCombo->Append("VERSION_140");
  d->profileCombo->Append("VERSION_150");
  d->profileCombo->Append("VERSION_330");
  d->profileCombo->Append("VERSION_400");
  d->profileCombo->Append("VERSION_410");
  d->profileCombo->Append("VERSION_420");
  d->profileCombo->Append("VERSION_430");
  d->profileCombo->Append("VERSION_440");
  d->profileCombo->Append("VERSION_450");
  d->profileCombo->Append("VERSION_460");
  d->profileCombo->Append("VERSION_100_E");
  d->profileCombo->Append("VERSION_300_E");
  d->profileCombo->Append("VERSION_310_E");
  d->profileCombo->Append("VERSION_320_E");
  vbox->Add(d->profileCombo);

  vbox->AddSpacer(5);

  vbox->Add(label("Depth"));
  d->depthCombo = new wxChoice(this, wxID_ANY);
  d->depthCombo->Append("OFF");
  d->depthCombo->Append("ON_16");
  d->depthCombo->Append("ON_24");
  d->depthCombo->Append("ON_32");
  vbox->Add(d->depthCombo);

  d->updateUI();

  SetSizerAndFit(vbox);
  Centre();
}

//##################################################################################################
OpenGLConfig::~OpenGLConfig()
{
  delete d;
}

//##################################################################################################
void OpenGLConfig::setConfig(const tp_maps::OpenGLConfig& config)
{
  d->config = config;
  d->updateUI();
}

//##################################################################################################
tp_maps::OpenGLConfig OpenGLConfig::config()
{
  d->config.profile = d->indexToProfile(d->profileCombo->GetSelection());
  d->config.depth = d->indexToDepth(d->depthCombo->GetSelection());
  return d->config;
}

//##################################################################################################
int OpenGLConfig::showModal(tp_maps::OpenGLConfig& config,
                            wxWindow* parent,
                            wxWindowID id,
                            const wxString& title)
{
  wxDialog dialog(parent, id, title);

  wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

  OpenGLConfig configWidget(&dialog, id);
  configWidget.setConfig(config);

  vbox->Add(&configWidget, 0, wxALL, 5);
  vbox->AddStretchSpacer();

  vbox->Add(dialog.CreateButtonSizer(wxOK | wxCANCEL), 0, wxALIGN_RIGHT);
  vbox->AddSpacer(5);

  dialog.SetSizerAndFit(vbox);
  dialog.SetSize(dialog.GetSize() + wxSize(100, 60));
  dialog.Center();

  auto result = dialog.ShowModal();
  if(result == wxID_OK)
    config = configWidget.config();

  return result;
}


}
