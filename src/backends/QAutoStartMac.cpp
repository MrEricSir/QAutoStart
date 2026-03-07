#include "QAutoStartMac.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>


QString QAutoStartMac::plistPath() const
{
  return QDir::homePath() + "/Library/LaunchAgents/" + identifier() + ".plist";
}


bool QAutoStartMac::isEnabled()
{
  return QFile::exists(plistPath());
}


bool QAutoStartMac::setEnabled(bool enabled)
{
  QString path = plistPath();

  if (enabled)
  {
    QDir().mkpath(QFileInfo(path).absolutePath());

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      qWarning() << "QAutoStart: failed to write" << path;
      return false;
    }

    QString appPath = QCoreApplication::applicationFilePath();
    QString id = identifier();

    QTextStream out(&file);
    out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    out << "<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\""
           " \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n";
    out << "<plist version=\"1.0\">\n";
    out << "<dict>\n";
    out << "  <key>Label</key>\n";
    out << "  <string>" << id.toHtmlEscaped() << "</string>\n";
    out << "  <key>ProgramArguments</key>\n";
    out << "  <array>\n";
    out << "    <string>" << appPath.toHtmlEscaped() << "</string>\n";
    out << "  </array>\n";
    out << "  <key>RunAtLoad</key>\n";
    out << "  <true/>\n";
    out << "</dict>\n";
    out << "</plist>\n";

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
