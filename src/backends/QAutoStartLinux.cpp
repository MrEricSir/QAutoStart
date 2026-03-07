#include "QAutoStartLinux.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>


QString QAutoStartLinux::desktopFilePath() const
{
  QString configDir = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation);
  return configDir + "/autostart/" + identifier() + ".desktop";
}


bool QAutoStartLinux::isEnabled()
{
  return QFile::exists(desktopFilePath());
}


bool QAutoStartLinux::setEnabled(bool enabled)
{
  QString path = desktopFilePath();

  if (enabled)
  {
    QDir().mkpath(QFileInfo(path).absolutePath());

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      qWarning() << "QAutoStart: failed to write" << path;
      return false;
    }

    QString appName = QCoreApplication::applicationName();

    QTextStream out(&file);
    out << "[Desktop Entry]\n";
    out << "Type=Application\n";
    out << "Name=" << appName << "\n";
    out << "Exec=" << QCoreApplication::applicationFilePath() << "\n";
    out << "Icon=" << identifier() << "\n";
    out << "X-GNOME-Autostart-enabled=true\n";

    qInfo() << "QAutoStart: created" << path;
    return true;
  }
  else
  {
    if (QFile::remove(path))
    {
      qInfo() << "QAutoStart: removed" << path;
      return true;
    }
    qWarning() << "QAutoStart: failed to remove" << path;
    return false;
  }
}
