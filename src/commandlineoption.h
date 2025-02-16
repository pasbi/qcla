#pragma once

#include <QCommandLineOption>

namespace qcla
{

struct ArgumentGroup;

class CommandLineOption
{
public:
  explicit CommandLineOption(QString name);
  CommandLineOption& description(QString description);
  CommandLineOption& value_name(QString value_name);
  CommandLineOption& default_value(QString default_value);
  CommandLineOption& argument_group(ArgumentGroup& group);
  [[nodiscard]] QString description() const;
  explicit operator QCommandLineOption() const;

private:
  QString m_name;
  QString m_description;
  QString m_value_name;
  QString m_default_value;
  ArgumentGroup* m_group = nullptr;
};

}  // namespace qcla
