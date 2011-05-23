#define USE_QT_SIGNALS

#include <QObject>
#include <QTimer>
#include <iostream>

#include "raul/Path.hpp"
#include "ingen/EngineBase.hpp"
#include "ingen/client/ObjectModel.hpp"
#include "ingen/shared/World.hpp"

using namespace std;
using namespace Ingen::Client;

namespace Core {
  namespace Internal {

// A crappy class to whip Ingen.  Temporary.
class BackgroundStuff : public QObject
{
  Q_OBJECT

public:
  BackgroundStuff (QObject* parent, Ingen::Shared::World* world) :
    QObject(parent),
    m_world(world)
  {
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(fire()));
    timer->start(100);
  }

  virtual ~BackgroundStuff() {};

public Q_SLOTS:
  void fire ()
  {
    m_world->local_engine()->main_iteration();
  }

private:
  Ingen::Shared::World* m_world;
};

  } // namespace Internal
} // namespace Core

// vim: tw=90 ts=8 sw=2 sts=4 et ci pi cin cino=l1,g0,+2s,\:0,(0,u0,U0,W2s