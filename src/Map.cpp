#include "tp_wx_maps/Map.h"

#include "tp_maps/Map.h"
#include "tp_maps/MouseEvent.h"
#include "tp_maps/KeyEvent.h"

#include "tp_utils/TimeUtils.h"
#include "tp_utils/DebugUtils.h"

namespace tp_wx_maps
{

namespace
{
//##################################################################################################
const int* attribList(const tp_maps::OpenGLConfig& openGLConfig)
{
  static std::vector<int> attribList;
  attribList.clear();

  attribList.push_back(WX_GL_DEPTH_SIZE);
  attribList.push_back(int(openGLConfig.depth));

  if(int(openGLConfig.profile) >= int(tp_maps::OpenGLProfile::VERSION_130))
    attribList.push_back(WX_GL_CORE_PROFILE);

  attribList.push_back(WX_GL_MAJOR_VERSION);
  attribList.push_back(int(openGLConfig.profile)/10);

  attribList.push_back(WX_GL_MINOR_VERSION);
  attribList.push_back(int(openGLConfig.profile) - ((int(openGLConfig.profile)/10) * 10));

  attribList.push_back(0);

  return attribList.data();
}
}

//##################################################################################################
struct Map::Private final: public tp_maps::Map
{
  friend class tp_wx_maps::Map;
  tp_wx_maps::Map* q;
  glm::ivec2 mousePos{0,0};

  wxGLContext context;

  //################################################################################################
  Private(tp_wx_maps::Map* q_,
          const tp_maps::OpenGLConfig& openGLConfig):
    tp_maps::Map(openGLConfig.depth!=tp_maps::OpenGLDepth::OFF),
    q(q_),
    context(q)
  {
    setOpenGLProfile(openGLConfig.profile);
  }

  //################################################################################################
  ~Private() override;

  //################################################################################################
  void makeCurrent() override
  {
    context.SetCurrent(*q);
  }

  //################################################################################################
  void update() override
  {
    q->Refresh();
  }
};

//##################################################################################################
Map::Private::~Private()
{

}

//##################################################################################################
Map::Map(wxWindow* parent,
         const wxString& title,
         const tp_maps::OpenGLConfig& openGLConfig):
  wxGLCanvas(parent, wxID_ANY, attribList(openGLConfig), wxDefaultPosition, wxDefaultSize, 0, title),
  d(new Private(this, openGLConfig))
{
}

//##################################################################################################
Map::~Map()
{
  d->preDelete();
  delete d;
}

//##################################################################################################
tp_maps::Map* Map::map() const
{
  return d;
}

//##################################################################################################
void Map::paintEvent(wxPaintEvent& event)
{
  TP_UNUSED(event);
  d->makeCurrent();
  d->paintGL();
  glFlush();
  SwapBuffers();
}

//##################################################################################################
void Map::mouseMovedEvent(wxMouseEvent& event)
{
  tp_maps::MouseEvent e(tp_maps::MouseEventType::Move);
  e.posDelta = glm::ivec2(event.GetX(), event.GetY()) - d->mousePos;
  d->mousePos = {event.GetX(), event.GetY()};
  e.pos = d->mousePos;
  d->mouseEvent(e);
}

//##################################################################################################
void Map::mouseDownEvent(wxMouseEvent& event)
{
  tp_maps::MouseEvent e(tp_maps::MouseEventType::Press);
  e.pos = {event.GetX(), event.GetY()};
  switch (event.GetButton())
  {
  case wxMOUSE_BTN_LEFT:   e.button = tp_maps::Button::LeftButton;   break;
  case wxMOUSE_BTN_RIGHT:  e.button = tp_maps::Button::RightButton;  break;
  case wxMOUSE_BTN_MIDDLE: e.button = tp_maps::Button::MiddleButton; break;
  default:                 e.button = tp_maps::Button::NoButton;     break;
  }
  d->mouseEvent(e);
}

//##################################################################################################
void Map::mouseWheelMovedEvent(wxMouseEvent& event)
{
  tp_maps::MouseEvent e(tp_maps::MouseEventType::Wheel);
  e.pos = d->mousePos;    
  e.delta = event.GetWheelRotation();
  d->mouseEvent(e);
}

//##################################################################################################
void Map::mouseReleasedEvent(wxMouseEvent& event)
{
  tp_maps::MouseEvent e(tp_maps::MouseEventType::Release);
  e.pos = {event.GetX(), event.GetY()};
  switch (event.GetButton())
  {
  case wxMOUSE_BTN_LEFT:   e.button = tp_maps::Button::LeftButton;   break;
  case wxMOUSE_BTN_RIGHT:  e.button = tp_maps::Button::RightButton;  break;
  case wxMOUSE_BTN_MIDDLE: e.button = tp_maps::Button::MiddleButton; break;
  default:                 e.button = tp_maps::Button::NoButton;     break;
  }
  d->mouseEvent(e);
}

//##################################################################################################
void Map::resizedEvent(wxSizeEvent& event)
{
  d->resizeGL(event.GetSize().GetWidth(), event.GetSize().GetHeight());
}

//##################################################################################################
void Map::keyPressedEvent(wxKeyEvent& event)
{
  tp_maps::KeyEvent e(tp_maps::KeyEventType::Press);
  e.scancode = event.GetKeyCode();
  d->keyEvent(e);
}

//##################################################################################################
void Map::keyReleasedEvent(wxKeyEvent& event)
{
  tp_maps::KeyEvent e(tp_maps::KeyEventType::Release);
  e.scancode = event.GetKeyCode();
  d->keyEvent(e);
}

BEGIN_EVENT_TABLE (Map, wxGLCanvas)
EVT_PAINT       (Map::paintEvent          )
EVT_MOTION      (Map::mouseMovedEvent     )
EVT_LEFT_DOWN   (Map::mouseDownEvent      )
EVT_LEFT_UP     (Map::mouseReleasedEvent  )
EVT_RIGHT_DOWN  (Map::mouseDownEvent      )
EVT_RIGHT_UP    (Map::mouseReleasedEvent  )
EVT_MIDDLE_DOWN (Map::mouseDownEvent      )
EVT_MIDDLE_UP   (Map::mouseReleasedEvent  )
EVT_SIZE        (Map::resizedEvent        )
EVT_KEY_DOWN    (Map::keyPressedEvent     )
EVT_KEY_UP      (Map::keyReleasedEvent    )
EVT_MOUSEWHEEL  (Map::mouseWheelMovedEvent)
END_EVENT_TABLE()

}
