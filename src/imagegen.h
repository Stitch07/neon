#pragma once
#include <string>
#include <httplib.h>
#include <Magick++.h>

namespace imagegen {
    Magick::Image grayscale(const std::string&);
    Magick::Image sepia(const std::string&);

    namespace utils {
        std::string read_blob(Magick::Blob&);
        std::string read_image(Magick::Image);

        void encode(httplib::Response&, const Magick::Image&);
    }
}
