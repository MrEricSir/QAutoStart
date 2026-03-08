// MIT License

// Copyright (c) 2026 Eric Gregory

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef QAUTOSTART_H
#define QAUTOSTART_H

#include <QObject>

// When running QDoc we have to ignore Q_OBJECT to avoid parsing Qt internals.
#ifdef Q_QDOC
#define Q_OBJECT
#endif

/*!
    \module QAutoStart
    \title QAutoStart C++ Classes
    \brief Cross-platform Qt auto-start on user login.
*/

/*!
    \class QAutoStart
    \inmodule QAutoStart
    \brief The QAutoStart class provides Qt cross-platform application auto start
    on user login.

    The following platforms are supported:

    \list
    \li \b{Windows}: Creates a registry entry under
        \c{HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run}.
    \li \b{macOS}: Creates a LaunchAgent plist in
        \c{~/Library/LaunchAgents/}.
    \li \b{Linux}: Creates an XDG autostart \c{.desktop} file in \c{~/.config/autostart/}.
    \endlist

    The autostart artifact names are derived from QCoreApplication::organizationDomain()
    and QCoreApplication::applicationName(). These properties must be set before
    QAutoStart can be used.

    \section1 Example

    \code
    QCoreApplication::setApplicationName("MyApp");
    QCoreApplication::setOrganizationDomain("com.example");

    QAutoStart &autoStart = QAutoStart::Get();
    autoStart.setEnabled(true);
    \endcode

    \sa QCoreApplication::setApplicationName(),
        QCoreApplication::setOrganizationDomain()
*/
class QAutoStart : public QObject
{
  Q_OBJECT

public:
  /*!
      Returns a reference to the singleton.

      On unsupported platforms the returned instance will do nothing.
  */
  static QAutoStart& Get();

  explicit QAutoStart(QObject* parent = nullptr) : QObject(parent) {}

  /*!
      Returns \c true if the application is currently registered to start on
      user login.

      On unsupported platforms, this will always return \c false.
  */
  virtual bool isEnabled();

  /*!
      Sets or unsets the application to auto start on user login.

      When \a enabled is \c true the platform-specific entry is created.
      When \a enabled is \c false the entry is removed.

      Returns \c true on success, \c false if the operation failed.
  */
  virtual bool setEnabled(bool enabled);

protected:
  /*!
      \internal
      Returns an identifier string.
  */
  static QString identifier();
};

#endif // QAUTOSTART_H
