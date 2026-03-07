#include "QAutoStartWin.h"

#include <QCoreApplication>
#include <QDebug>
#include <QSettings>

static const char* DEFAULT_RUN_KEY = "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run";


QString QAutoStartWin::registryKey() const
{
  return QString::fromLatin1(DEFAULT_RUN_KEY);
}


bool QAutoStartWin::isEnabled()
{
  QSettings reg(registryKey(), QSettings::NativeFormat);
  return reg.contains(QCoreApplication::applicationName());
}


bool QAutoStartWin::setEnabled(bool enabled)
{
  QSettings reg(registryKey(), QSettings::NativeFormat);
  QString appName = QCoreApplication::applicationName();

  if (enabled)
  {
    QString appPath = QCoreApplication::applicationFilePath();
    appPath.replace('/', '\\');
    reg.setValue(appName, '"' + appPath + '"');
    qInfo() << "QAutoStart: registered" << appPath;
  }
  else
  {
    reg.remove(appName);
    qInfo() << "QAutoStart: unregistered";
  }

  reg.sync();
  return reg.status() == QSettings::NoError;
}
