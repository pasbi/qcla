#pragma once

#include <QCommandLineParser>
#include <QString>
#include <fmt/ranges.h>
#include <spdlog/spdlog.h>

class QCommandLineParser;

namespace qcla
{

class CommandLineParser;

class ArgumentGroup
{
  // use CommandLineParser::make_argument_group()
  ArgumentGroup() = default;
  void check(const QCommandLineParser& parser) const;
  friend class CommandLineParser;

public:
  std::vector<QString> argument_names;

  template<typename Enum>
    requires std::is_enum_v<Enum>
  [[nodiscard]] Enum value(const QCommandLineParser& parser) const
  {
    if (const auto it =
            std::ranges::find_if(argument_names, [&parser](const QString& name) { return parser.isSet(name); });
        it != argument_names.end())
    {
      const auto i = std::distance(argument_names.begin(), it);
      return static_cast<Enum>(static_cast<std::underlying_type_t<Enum>>(i));
    }
    spdlog::critical("None of [{}] is set.", fmt::join(argument_names, ", "));
    std::exit(EXIT_FAILURE);
  }
};

}  // namespace qcla
