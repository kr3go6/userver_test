#include "hello.hpp"
#include "getresource.hpp"

#include <fmt/format.h>

#include <userver/server/handlers/http_handler_base.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

namespace service_index {

namespace {

class Index final : public userver::server::handlers::HttpHandlerBase {
public:
  static constexpr std::string_view kName = "handler-index";

  using HttpHandlerBase::HttpHandlerBase;

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest &request,
      userver::server::request::RequestContext &) const override {
    return file_to_string("app/index.html");
  }
};

} // namespace


void AppendIndex(userver::components::ComponentList &component_list) {
  component_list.Append<Index>();
}

} // namespace service_index
