#include "pch.h"

#include "hare/details/auto_tracer.h"
#include "hare/details/autolog.h"

namespace hare::details {

template <>
autolog<auto_tracer, auto_flusher>::autolog(std::string_view file_name,
                                            std::string_view function_signature,
                                            const std::string& logger_name,
                                            std::string_view obj_name) noexcept
    : flusher_(logger_name), tracer_(file_name, function_signature, logger_name, obj_name) {
}

template <>
autolog<auto_measure, auto_flusher>::autolog(std::string_view file_name,
                                             std::string_view function_signature,
                                             const std::string& logger_name,
                                             std::string_view obj_name) noexcept
    : flusher_(logger_name), tracer_(file_name, function_signature, logger_name, obj_name) {
}

template <>
autolog<auto_tracer, auto_flusher_all>::autolog(std::string_view file_name,
                                                std::string_view function_signature,
                                                const std::string& logger_name,
                                                std::string_view obj_name) noexcept
    : flusher_(), tracer_(file_name, function_signature, logger_name, obj_name) {
}

template <>
autolog<auto_measure, auto_flusher_all>::autolog(std::string_view file_name,
                                                 std::string_view function_signature,
                                                 const std::string& logger_name,
                                                 std::string_view obj_name) noexcept
    : flusher_(), tracer_(file_name, function_signature, logger_name, obj_name) {
}

template <>
autolog<auto_tracer, auto_flusher>::~autolog() = default;
template <>
autolog<auto_measure, auto_flusher>::~autolog() = default;
template <>
autolog<auto_tracer, auto_flusher_all>::~autolog() = default;
template <>
autolog<auto_measure, auto_flusher_all>::~autolog() = default;

}  // namespace hare::details