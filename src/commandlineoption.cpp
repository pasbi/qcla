#include "commandlineoption.h"
#include "argumentgroup.h"
#include "fmt.h"

#include <ranges>

namespace qcla
{

CommandLineOption::CommandLineOption(QString name) : m_name(std::move(name))
{
}

CommandLineOption& CommandLineOption::description(QString description)
{
  m_description = std::move(description);
  return *this;
}

CommandLineOption& CommandLineOption::value_name(QString value_name)
{
  m_value_name = std::move(value_name);
  return *this;
}

CommandLineOption& CommandLineOption::default_value(QString default_value)
{
  m_default_value = std::move(default_value);
  return *this;
}

QString CommandLineOption::description() const
{
  auto description = m_description;
  if (!m_default_value.isEmpty()) {
    description += QStringLiteral(" Default: %1.").arg(m_default_value);
  }
  if (m_group != nullptr) {
    if (m_group->argument_names.size() == 1) {
      description += " Mandatory.";
    } else {
      const auto not_this_argument = [this](const auto& arg_name) { return m_name != arg_name; };
      description += QString::fromStdString(
          fmt::format(" Mutually exclusive with [{}]",
                      fmt::join(m_group->argument_names | std::views::filter(not_this_argument), ", ")));
    }
  }
  return description;
}

CommandLineOption& CommandLineOption::argument_group(ArgumentGroup& group)
{
  if (m_group != nullptr) {
    throw std::runtime_error("Group already set.");
  }
  m_group = &group;
  m_group->argument_names.emplace_back(m_name);
  return *this;
}

CommandLineOption::operator QCommandLineOption() const
{
  return QCommandLineOption(m_name, description(), m_value_name, m_default_value);
}

}  // namespace qcla
