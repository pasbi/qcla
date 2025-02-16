#pragma once

#include "argumentgroup.h"
#include "commandlineoption.h"
#include "dependency.h"
#include <QCommandLineParser>
#include <vector>

namespace qcla
{

class CommandLineParser
{
public:
  CommandLineOption& add_option(QString name);
  [[nodiscard]] std::unique_ptr<QCommandLineParser> process(const QStringList& arguments) const;
  [[nodiscard]] ArgumentGroup& make_argument_group();
  void add_help_option();
  void add_version_option();
  void add_dependency(Dependency dependency);

private:
  // ArgumentGroups must not be destroyed until CommandLineParser is destroyed.
  std::list<ArgumentGroup> m_argument_groups;
  std::vector<CommandLineOption> m_options;
  bool m_help_option_active = false;
  std::vector<Dependency> m_dependencies;
  bool m_version_option_active = false;
};

}  // namespace qcla
