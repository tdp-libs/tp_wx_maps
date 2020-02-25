#ifndef tp_wx_maps_Map_h
#define tp_wx_maps_Map_h

#include "tp_wx_maps/Globals.h"

#include "tp_maps/Map.h"

namespace tp_wx_maps
{

//##################################################################################################
class TP_WX_MAPS_SHARED_EXPORT Map : public tp_maps::Map
{
public:
  //################################################################################################
  Map(bool enableDepthBuffer = true, bool fullScreen = false, const std::string& title=std::string());

  //################################################################################################
  ~Map() override;

  //################################################################################################
  void exec();

  //################################################################################################
  void processEvents();

  //################################################################################################
  void makeCurrent() override;

  //################################################################################################
  //! Called to queue a refresh
  void update() override;

  //################################################################################################
  void setRelativeMouseMode(bool enabled) override;

  //################################################################################################
  bool relativeMouseMode() const override;

private:
  struct Private;
  Private* d;
  friend struct Private;
};
}
#endif
