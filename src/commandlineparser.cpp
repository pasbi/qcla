#include "commandlineparser.h"
#include "argumentgroup.h"

#include <spdlog/spdlog.h>

namespace qcla
{

CommandLineOption& CommandLineParser::add_option(QString name)
{
  return m_options.emplace_back(std::move(name));
}

[[nodiscard]] std::unique_ptr<QCommandLineParser> CommandLineParser::process(const QStringList& arguments) const
{
  auto parser = std::make_unique<QCommandLineParser>();
  for (const auto& option : m_options) {
    parser->addOption(static_cast<QCommandLineOption>(option));
  }
  if (m_help_option_active) {
    parser->addHelpOption();
  }
  if (m_version_option_active) {
    parser->addVersionOption();
  }
  parser->process(arguments);
  for (const auto& group : m_argument_groups) {
    group.check(*parser);
  }
  return parser;
}

ArgumentGroup& CommandLineParser::make_argument_group()
{
  m_argument_groups.push_back(ArgumentGroup{});
  auto& group = m_argument_groups.back();
  return group;
}

void CommandLineParser::add_help_option()
{
  m_help_option_active = true;
}

void CommandLineParser::add_version_option()
{
  m_version_option_active = true;
}

}  // namespace qcla
