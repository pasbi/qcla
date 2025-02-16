#include "commandlineparser.h"
#include "argumentgroup.h"

#include "fmt.h"
#include <QCoreApplication>
#include <spdlog/spdlog.h>

namespace
{

constexpr auto VERSION_OPTION_NAME = "version";

}

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
  parser->process(arguments);
  if (parser->isSet(VERSION_OPTION_NAME)) {
    for (const auto& [name, version, vcs_describe] : m_dependencies) {
      if (vcs_describe.isEmpty()) {
        fmt::print("  {:.<30} {}\n", name, version);
      } else {
        fmt::print("  {:.<30} {: <8} {}\n", name, version, vcs_describe);
      }
    }
    ::exit(EXIT_SUCCESS);
  }
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
  add_option(VERSION_OPTION_NAME).description("Print version information and exit.");
}

void CommandLineParser::add_dependency(Dependency dependency)
{
  m_dependencies.emplace_back(std::move(dependency));
}

}  // namespace qcla
