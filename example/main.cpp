#include <QApplication>
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

#include "QAutoStart.h"


int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  app.setApplicationName("QAutoStartExample");
  app.setOrganizationDomain("com.EricGregory.QAutoStartExample");

  QWidget window;
  window.setWindowTitle("QAutoStart Example");

  auto* layout = new QVBoxLayout(&window);

  auto* label = new QLabel("Hello, World!");
  layout->addWidget(label);

  auto* checkbox = new QCheckBox("Start on Login");
  checkbox->setChecked(QAutoStart::Get().isEnabled());
  QObject::connect(checkbox, &QCheckBox::toggled, [checkbox](bool checked) {
    if (!QAutoStart::Get().setEnabled(checked))
    {
      QSignalBlocker blocker(checkbox);
      checkbox->setChecked(!checked);
    }
  });
  layout->addWidget(checkbox);

  window.show();
  return app.exec();
}
