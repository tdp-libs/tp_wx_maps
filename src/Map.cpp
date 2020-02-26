#include "tp_wx_maps/Map.h"

#include "tp_maps/Map.h"
#include "tp_maps/MouseEvent.h"
#include "tp_maps/KeyEvent.h"

#include "tp_utils/TimeUtils.h"
#include "tp_utils/DebugUtils.h"

namespace tp_wx_maps
{

//##################################################################################################
struct Map::Private final: public tp_maps::Map
{
  friend class tp_wx_maps::Map;
  tp_wx_maps::Map* q;
  // SDL_Window *window{nullptr};
  // SDL_GLContext context{nullptr};

  glm::ivec2 mousePos{0,0};

  int64_t animationTimeMS{0};

  bool paint{true};
  bool quitting{false};

  //################################################################################################
  Private(tp_wx_maps::Map* q_, bool enableDepthBuffer):
    tp_maps::Map(enableDepthBuffer),
    q(q_)
  {

  }

  //################################################################################################
  ~Private() override;

  //################################################################################################
  void makeCurrent() override
  {
    //  SDL_GL_MakeCurrent(d->window, d->context);
  }

  //################################################################################################
  void update() override
  {
    // Trigger a repaint here.
  }

//  //################################################################################################
//  void update()
//  {
//    SDL_Event event;
//    while(SDL_PollEvent(&event))
//    {
//      switch(event.type)
//      {

//      case SDL_QUIT: //-----------------------------------------------------------------------------
//      {
//        quitting = true;
//        break;
//      }

//      case SDL_MOUSEBUTTONDOWN: //------------------------------------------------------------------
//      {
//        tp_maps::MouseEvent e(tp_maps::MouseEventType::Press);
//        e.pos = {event.button.x, event.button.y};
//        switch (event.button.button)
//        {
//        case SDL_BUTTON_LEFT:  e.button = tp_maps::Button::LeftButton;  break;
//        case SDL_BUTTON_RIGHT: e.button = tp_maps::Button::RightButton; break;
//        default:               e.button = tp_maps::Button::NoButton;    break;
//        }
//        q->mouseEvent(e);
//        break;
//      }

//      case SDL_MOUSEBUTTONUP: //--------------------------------------------------------------------
//      {
//        tp_maps::MouseEvent e(tp_maps::MouseEventType::Release);
//        e.pos = {event.button.x, event.button.y};
//        switch (event.button.button)
//        {
//        case SDL_BUTTON_LEFT:  e.button = tp_maps::Button::LeftButton;  break;
//        case SDL_BUTTON_RIGHT: e.button = tp_maps::Button::RightButton; break;
//        default:               e.button = tp_maps::Button::NoButton;    break;
//        }
//        q->mouseEvent(e);
//        break;
//      }

//      case SDL_MOUSEMOTION: //----------------------------------------------------------------------
//      {
//        tp_maps::MouseEvent e(tp_maps::MouseEventType::Move);
//        mousePos = {event.motion.x, event.motion.y};
//        e.pos = mousePos;
//        e.posDelta = {event.motion.xrel, event.motion.yrel};
//        q->mouseEvent(e);
//        break;
//      }

//      case SDL_MOUSEWHEEL: //-----------------------------------------------------------------------
//      {
//        tp_maps::MouseEvent e(tp_maps::MouseEventType::Wheel);
//        e.pos = mousePos;
//        e.delta = event.wheel.y;
//        q->mouseEvent(e);
//        break;
//      }

//      case SDL_WINDOWEVENT: //----------------------------------------------------------------------
//      {
//        if (event.window.event == SDL_WINDOWEVENT_RESIZED)
//        {
//          q->resizeGL(event.window.data1, event.window.data2);
//          paint = true;
//        }
//        else if (event.window.event == SDL_WINDOWEVENT_SHOWN || event.window.event == SDL_WINDOWEVENT_EXPOSED)
//        {
//          paint = true;
//        }

//        break;
//      }

//      case SDL_KEYDOWN: //--------------------------------------------------------------------------
//      {
//        tp_maps::KeyEvent e(tp_maps::KeyEventType::Press);
//        e.scancode = event.key.keysym.scancode;
//        q->keyEvent(e);
//        break;
//      }

//      case SDL_KEYUP: //----------------------------------------------------------------------------
//      {
//        if(event.key.keysym.scancode == 41)
//          quitting = true;

//        tp_maps::KeyEvent e(tp_maps::KeyEventType::Release);
//        e.scancode = event.key.keysym.scancode;
//        q->keyEvent(e);
//        break;
//      }

//      default: //-----------------------------------------------------------------------------------
//      {
//        break;
//      }
//      }
//    }

//    if(const auto t = tp_utils::currentTimeMS(); animationTimeMS<t)
//    {
//      animationTimeMS = t+8;
//      q->makeCurrent();
//      q->animate(double(t));
//    }

//    if(paint)
//    {
//#if 0
//  static tp_utils::ElapsedTimer t;
//  auto a=t.restart();
//  TP_CLEANUP([&]{tpWarning() << "External: " << a << " Internal:" << t.restart();});
//#endif
//      paint = false;
//      q->makeCurrent();
//      q->paintGL();
//      SDL_GL_SwapWindow(window);
//    }
//  }
};

//##################################################################################################
Map::Private::~Private()
{

}

//##################################################################################################
Map::Map(wxWindow* parent, bool enableDepthBuffer, bool fullScreen, const wxString& title):
  wxGLCanvas(parent, wxID_ANY,  wxDefaultPosition, wxDefaultSize, 0, title),
  d(new Private(this, enableDepthBuffer))
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

}
