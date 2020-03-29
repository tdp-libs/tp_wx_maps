#ifndef tp_wx_maps_OpenGLConfig_h
#define tp_wx_maps_OpenGLConfig_h

#include "tp_wx_maps/Globals.h"

#include "tp_maps/Globals.h"

#include <wx/wx.h>

namespace tp_wx_maps
{

//##################################################################################################
class TP_WX_MAPS_SHARED_EXPORT OpenGLConfig : public wxPanel
{
public:
  //################################################################################################
  OpenGLConfig(wxWindow* parent,
               wxWindowID id);

  //################################################################################################
  ~OpenGLConfig() override;

  //################################################################################################
  void setConfig(const tp_maps::OpenGLConfig& config);

  //################################################################################################
  tp_maps::OpenGLConfig config();

  //################################################################################################
  static int showModal(tp_maps::OpenGLConfig& config,
                       wxWindow* parent,
                       wxWindowID id,
                       const wxString& title);

private:
  struct Private;
  Private* d;
  friend struct Private;
};
}
#endif
