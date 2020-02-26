#ifndef tp_wx_maps_Map_h
#define tp_wx_maps_Map_h

#include "tp_wx_maps/Globals.h"

#include <wx/glcanvas.h>

namespace tp_maps
{
class Map;
}

namespace tp_wx_maps
{

//##################################################################################################
class TP_WX_MAPS_SHARED_EXPORT Map : public wxGLCanvas
{
public:
  //################################################################################################
  Map(wxWindow* parent, bool enableDepthBuffer = true, bool fullScreen = false, const wxString& title=wxString());

  //################################################################################################
  ~Map() override;

  //################################################################################################
  tp_maps::Map* map() const;

private:
  struct Private;
  Private* d;
  friend struct Private;
};
}
#endif
