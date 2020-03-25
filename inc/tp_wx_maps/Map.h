#ifndef tp_wx_maps_Map_h
#define tp_wx_maps_Map_h

#include "tp_wx_maps/Globals.h"

#include "tp_maps/Globals.h"

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
  Map(wxWindow* parent,
      bool enableDepthBuffer = true,
      const wxString& title=wxString(),
      tp_maps::OpenGLProfile openGLProfile=tp_maps::OpenGLProfile::VERSION_330);

  //################################################################################################
  ~Map() override;

  //################################################################################################
  tp_maps::Map* map() const;

protected:
    void paintEvent(wxPaintEvent& event);
    void mouseMovedEvent(wxMouseEvent& event);
    void mouseDownEvent(wxMouseEvent& event);
    void mouseWheelMovedEvent(wxMouseEvent& event);
    void mouseReleasedEvent(wxMouseEvent& event);
    void resizedEvent(wxSizeEvent& event);
    void keyPressedEvent(wxKeyEvent& event);
    void keyReleasedEvent(wxKeyEvent& event);

private:
    static const wxEventTableEntry sm_eventTableEntries[];

protected:
    static const wxEventTable sm_eventTable;
    const wxEventTable*       GetEventTable() const override;
    static wxEventHashTable   sm_eventHashTable;
    wxEventHashTable&         GetEventHashTable() const override;

private:
  struct Private;
  Private* d;
  friend struct Private;
};
}
#endif
