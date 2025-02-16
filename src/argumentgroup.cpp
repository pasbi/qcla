#include "argumentgroup.h"
#include "commandlineparser.h"
#include "fmt.h"
#include <spdlog/spdlog.h>

namespace qcla
{

void ArgumentGroup::check(const QCommandLineParser& parser) const
{
  const auto count =
      std::ranges::count_if(argument_names, [&parser](const auto& arg_name) { return parser.isSet(arg_name); });
  if (count != 1) {
    if (argument_names.size() == 1) {
      spdlog::critical("{} is mandatory.", argument_names.front());
    } else {
      spdlog::critical("Exactly one of [{}] must be given.", fmt::join(argument_names, ", "));
    }
    std::exit(EXIT_FAILURE);
  }
}

}  // namespace qcla
