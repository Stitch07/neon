#include <iostream>
#include "fmt/format.h"
#include "fmt/color.h"
#include "imagegen.h"
#include "httplib.h"
#include "httputil.h"
#include "ImageMagick-7/Magick++.h"
#include "kmeans/kmeans.h"

#define VERSION "0.1.0"

int main(int argc, char** argv) {
    fmt::print(fmt::fg(fmt::color::aqua) | fmt::emphasis::bold, "Neon {}\n", VERSION);
    // initialize imagemagick
    Magick::InitializeMagick(*argv);

    using namespace httplib;
    Server srv;
    srv.Get("/", [](const Request& req, Response& res) {
	res.set_content(fmt::format("Neon - {}", VERSION), "text/plain");
    });

    srv.Get("/grayscale", [](const Request& req, Response& res) {
        auto avatar_url = req.get_param_value("avatar");
        if (avatar_url.empty()) {
            httputil::bad_request(res, "Provide an avatar query parameter.");
            return;
        }
        try {
            auto grayscaled_img = imagegen::grayscale(avatar_url);
            imagegen::utils::encode(res, grayscaled_img);
        } catch(std::exception& e) {
            httputil::bad_request(res, "invalid url");
        }
    });

    srv.Get("/sepia", [](const Request& req, Response& res) {
        auto avatar_url = req.get_param_value("avatar");
        if (avatar_url.empty()) {
            httputil::bad_request(res, "Provide an avatar query parameter.");
            return;
        }
        try {
            auto grayscaled_img = imagegen::sepia(avatar_url);
            imagegen::utils::encode(res, grayscaled_img);
        } catch(std::exception& e) {
            httputil::bad_request(res, "invalid url");
        }
    });

    srv.Get(R"(/color/(\w+))", [&](const Request& req, Response& res) {
        std::string color = req.matches[1];
        auto valid = imagegen::utils::is_valid_hex(color);
        if (!valid) {
            httputil::bad_request(res, "Invalid color parameter");
            return;
        }
        imagegen::utils::encode(res, imagegen::draw_color(color));
    });

    srv.listen("localhost", 3000);
}
