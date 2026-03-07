#include "QAutoStart.h"

#include <QCoreApplication>
#include <QDebug>

#ifdef Q_OS_WIN
#include "backends/QAutoStartWin.h"
#elif defined(Q_OS_MAC)
#include "backends/QAutoStartMac.h"
#elif defined(Q_OS_LINUX)
#include "backends/QAutoStartLinux.h"
#endif


QAutoStart& QAutoStart::Get()
{
#ifdef Q_OS_WIN
  static QAutoStartWin instance;
  return instance;
#elif defined(Q_OS_MAC)
  static QAutoStartMac instance;
  return instance;
#elif defined(Q_OS_LINUX)
  static QAutoStartLinux instance;
  return instance;
#else
  qWarning() << "QAutoStart: no implementation for this platform";
  static QAutoStart instance;
  return instance;
#endif
}


QString QAutoStart::identifier()
{
  QString domain = QCoreApplication::organizationDomain();
  QString name = QCoreApplication::applicationName();
  return domain.isEmpty() ? name : domain + "." + name;
}


bool QAutoStart::isEnabled()
{
  return false;
}


bool QAutoStart::setEnabled(bool enabled)
{
  Q_UNUSED(enabled);
  qWarning() << "QAutoStart: setEnabled not implemented on this platform";
  return false;
}
