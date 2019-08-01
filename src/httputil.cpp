#include <string>

#include <httplib.h>
#include "httputil.h"

void httputil::bad_request(httplib::Response &res, const std::string& s) {
    res.status = 400;
    res.set_content(s, "text/plain");
}
