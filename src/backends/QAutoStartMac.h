#ifndef QAUTOSTART_MAC_H
#define QAUTOSTART_MAC_H

#include "../QAutoStart.h"

class QAutoStartMac : public QAutoStart
{
public:
  bool isEnabled() override;
  bool setEnabled(bool enabled) override;

protected:
  virtual QString plistPath() const;
};

#endif // QAUTOSTART_MAC_H
