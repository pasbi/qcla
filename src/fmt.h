#pragma once

#include <QString>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>

template<> struct fmt::formatter<QString> : fmt::formatter<std::string>
{
  auto format(const QString& s, fmt::format_context& ctx) const
  {
    return fmt::formatter<std::string>::format(s.toStdString(), ctx);
  }
};

template<> struct fmt::formatter<QStringView> : fmt::formatter<QString>
{
  auto format(const QStringView& sv, format_context& ctx) const
  {
    // Not really elegant, but I think there is no (simple) other way.
    // Also, performance should not really matter as no large strings are expected to be printed.
    return fmt::formatter<QString>::format(sv.toString(), ctx);
  }
};

class Hex
{
public:
  explicit Hex(const QByteArray& byte_array) : m_byte_array(byte_array)
  {
  }

  [[nodiscard]] QString to_string() const
  {
    return QString::fromUtf8(m_byte_array.toHex());
  }

private:
  const QByteArray& m_byte_array;
};

template<> struct fmt::formatter<Hex> : fmt::formatter<QString>
{
  auto format(const Hex& hex, fmt::format_context& ctx) const
  {
    return fmt::formatter<QString>::format(hex.to_string(), ctx);
  }
};

#if FMT_VERSION < 100000
template<typename T> struct fmt::formatter<std::optional<T>> : fmt::formatter<T>
{
  static auto format(const std::optional<T>& opt, format_context& ctx)
  {
    if (opt.has_value()) {
      return fmt::format_to(ctx.out(), "optional({})", *opt);
    } else {
      return fmt::format_to(ctx.out(), "None", *opt);
    }
  }
};
#endif
