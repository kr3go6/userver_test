#pragma once

#include <string>
#include <string_view>

#include <userver/components/component_list.hpp>

namespace service_index {

void AppendIndex(userver::components::ComponentList &component_list);

} // namespace service_index
