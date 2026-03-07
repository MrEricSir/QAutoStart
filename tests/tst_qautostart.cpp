#include <QtTest>
#include <QTemporaryDir>

#include "QAutoStart.h"

#ifdef Q_OS_MAC
#include "backends/QAutoStartMac.h"
#elif defined(Q_OS_LINUX)
#include "backends/QAutoStartLinux.h"
#elif defined(Q_OS_WIN)
#include "backends/QAutoStartWin.h"
#endif

// Test output
#ifdef Q_OS_MAC
class TestableAutoStart : public QAutoStartMac
{
public:
  explicit TestableAutoStart(const QString& path) : m_path(path) {}
  QString plistPath() const override { return m_path; }

private:
  QString m_path;
};
#elif defined(Q_OS_LINUX)
class TestableAutoStart : public QAutoStartLinux
{
public:
  explicit TestableAutoStart(const QString& path) : m_path(path) {}
  QString desktopFilePath() const override { return m_path; }

private:
  QString m_path;
};
#elif defined(Q_OS_WIN)
class TestableAutoStart : public QAutoStartWin
{
public:
  explicit TestableAutoStart(const QString& key) : m_key(key) {}
  QString registryKey() const override { return m_key; }

private:
  QString m_key;
};
#endif

// Test cases.
class tst_QAutoStart : public QObject
{
  Q_OBJECT

private slots:
  void baseClassDefaultsToDisabled();
  void baseClassSetEnabledReturnsFalse();
  void singletonReturnsConsistentReference();
  void enableReturnsTrue();
  void disableReturnsTrue();
  void enableDisableCycle();
#ifndef Q_OS_WIN
  void generatedFileContainsExpectedFields();
#endif
};

void tst_QAutoStart::baseClassDefaultsToDisabled()
{
  QAutoStart base;
  QVERIFY(!base.isEnabled());
}

void tst_QAutoStart::baseClassSetEnabledReturnsFalse()
{
  QAutoStart base;
  QVERIFY(!base.setEnabled(true));
  QVERIFY(!base.isEnabled());
}

void tst_QAutoStart::singletonReturnsConsistentReference()
{
  QAutoStart& a = QAutoStart::Get();
  QAutoStart& b = QAutoStart::Get();
  QCOMPARE(&a, &b); // Should be same object.
}

void tst_QAutoStart::enableReturnsTrue()
{
  QTemporaryDir tmpDir;
  QVERIFY(tmpDir.isValid());

#ifdef Q_OS_WIN
  QString testKey = "HKEY_CURRENT_USER\\Software\\QAutoStartTest";
  TestableAutoStart backend(testKey);
#else
  QString filePath = tmpDir.path() + "/testentry"
#ifdef Q_OS_MAC
    ".plist";
#else
    ".desktop";
#endif
  TestableAutoStart backend(filePath);
#endif

  QVERIFY(backend.setEnabled(true));
  QVERIFY(backend.isEnabled());

  // Clean up
  backend.setEnabled(false);
}

void tst_QAutoStart::disableReturnsTrue()
{
  QTemporaryDir tmpDir;
  QVERIFY(tmpDir.isValid());

#ifdef Q_OS_WIN
  QString testKey = "HKEY_CURRENT_USER\\Software\\QAutoStartTest";
  TestableAutoStart backend(testKey);
#else
  QString filePath = tmpDir.path() + "/testentry"
#ifdef Q_OS_MAC
    ".plist";
#else
    ".desktop";
#endif
  TestableAutoStart backend(filePath);
#endif

  QVERIFY(backend.setEnabled(true));
  QVERIFY(backend.setEnabled(false));
  QVERIFY(!backend.isEnabled());
}

void tst_QAutoStart::enableDisableCycle()
{
  QTemporaryDir tmpDir;
  QVERIFY(tmpDir.isValid());

#ifdef Q_OS_WIN
  QString testKey = "HKEY_CURRENT_USER\\Software\\QAutoStartTest";
  TestableAutoStart backend(testKey);
#else
  QString filePath = tmpDir.path() + "/testentry"
#ifdef Q_OS_MAC
    ".plist";
#else
    ".desktop";
#endif
  TestableAutoStart backend(filePath);
#endif

  QVERIFY(!backend.isEnabled());
  QVERIFY(backend.setEnabled(true));
  QVERIFY(backend.isEnabled());
  QVERIFY(backend.setEnabled(false));
  QVERIFY(!backend.isEnabled());
}

#ifndef Q_OS_WIN
void tst_QAutoStart::generatedFileContainsExpectedFields()
{
  QTemporaryDir tmpDir;
  QVERIFY(tmpDir.isValid());

  QString filePath = tmpDir.path() + "/testentry"
#ifdef Q_OS_MAC
    ".plist";
#else
    ".desktop";
#endif
  TestableAutoStart backend(filePath);
  QVERIFY(backend.setEnabled(true));

  QFile file(filePath);
  QVERIFY(file.open(QIODevice::ReadOnly | QIODevice::Text));
  QString contents = QString::fromUtf8(file.readAll());

  QVERIFY(contents.contains(QCoreApplication::applicationName()));

#ifdef Q_OS_MAC
  QVERIFY(contents.contains("<key>RunAtLoad</key>"));
  QVERIFY(contents.contains("<true/>"));
  QVERIFY(contents.contains("ProgramArguments"));
#else
  QVERIFY(contents.contains("[Desktop Entry]"));
  QVERIFY(contents.contains("Type=Application"));
  QVERIFY(contents.contains("Exec="));
#endif

  backend.setEnabled(false);
}
#endif

QTEST_MAIN(tst_QAutoStart)
#include "tst_qautostart.moc"
