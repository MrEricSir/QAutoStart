#ifndef QAUTOSTART_LINUX_H
#define QAUTOSTART_LINUX_H

#include "../QAutoStart.h"

class QAutoStartLinux : public QAutoStart
{
public:
  bool isEnabled() override;
  bool setEnabled(bool enabled) override;

protected:
  virtual QString desktopFilePath() const;
};

#endif // QAUTOSTART_LINUX_H
