#include "getresource.hpp"

#include <userver/server/handlers/exceptions.hpp>
#include <userver/engine/exception.hpp>
#include <userver/engine/task/task.hpp>
#include <userver/engine/task/cancel.hpp>
#include <userver/engine/task/task_processor_fwd.hpp>
#include <userver/fs/read.hpp>


namespace std_fs = std::filesystem;

class FileNotFoundException final : public userver::server::handlers::CustomHandlerException
{
    inline const std::string PAGE404(std::string& msg) {
        return "<html><head><title>404 Not Found</title></head><body><h1>" +
                msg +
                "</h1></body></html>";
    }
public:
    using HandlerErrorCode = userver::server::handlers::HandlerErrorCode;
    using ServiceErrorCode = userver::server::handlers::ServiceErrorCode;
    using InternalMessage  = userver::server::handlers::InternalMessage;
    using ExternalBody     = userver::server::handlers::ExternalBody;
    using ExtraHeaders     = userver::server::handlers::ExtraHeaders;

    FileNotFoundException(std::string& msg) : userver::server::handlers::CustomHandlerException(
                ServiceErrorCode {"404"}, 
                ExternalBody{PAGE404(msg)},
                InternalMessage{msg}, 
                HandlerErrorCode::kResourceNotFound) {}
    
    FileNotFoundException(std::string&& msg) : userver::server::handlers::CustomHandlerException(
                ServiceErrorCode {"404"}, 
                ExternalBody{PAGE404(msg)},
                InternalMessage{msg}, 
                HandlerErrorCode::kResourceNotFound) {}
};

std::string file_to_string(std_fs::path& filepath)
{
    std::error_code ec;
    std_fs::path canonical_filepath = std_fs::canonical(filepath, ec);
    
    if (ec) {
        throw FileNotFoundException(ec.message());
    }

    return userver::fs::ReadFileContents(
            userver::engine::current_task::GetTaskProcessor(), 
            canonical_filepath
    );
}

std::string file_to_string(std_fs::path&& filepath)
{
    std::error_code ec;
    std_fs::path canonical_filepath = std_fs::canonical(filepath, ec);
    
    if (ec) {
        throw FileNotFoundException(ec.message());
    }

    return userver::fs::ReadFileContents(
            userver::engine::current_task::GetTaskProcessor(), 
            std::move(canonical_filepath)
    );
}