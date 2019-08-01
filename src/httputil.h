#pragma once

#include <httplib.h>
#include <string>

namespace httputil {
    void bad_request(httplib::Response&, const std::string&);
};
