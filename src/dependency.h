#pragma once

#include <QString>

struct Dependency
{
  QString name;
  QString version;
  QString vcs_describe;
};
