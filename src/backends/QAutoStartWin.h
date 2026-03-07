#ifndef QAUTOSTART_WIN_H
#define QAUTOSTART_WIN_H

#include "../QAutoStart.h"

class QAutoStartWin : public QAutoStart
{
public:
  bool isEnabled() override;
  bool setEnabled(bool enabled) override;

protected:
  virtual QString registryKey() const;
};

#endif // QAUTOSTART_WIN_H
