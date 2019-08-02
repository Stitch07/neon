#include <fmt/format.h>
#include "imagegen.h"
#include "ImageMagick-7/Magick++.h"
#include <charconv>
#include <cstdlib>

// workaround to stod not accepting a base
double s16tod(const std::string& s) {
    return static_cast<double>(strtol(s.c_str(), NULL, 16));
}

Magick::Image imagegen::grayscale(const std::string &avatar) {
    Magick::Image avatar_im(avatar);
    avatar_im.grayscale(MagickCore::PixelIntensityMethod::UndefinedPixelIntensityMethod); // update this?
    return avatar_im;
}

Magick::Image imagegen::sepia(const std::string& avatar) {
	Magick::Image avatar_im(avatar);
	avatar_im.sepiaTone(50000);
	return avatar_im;
}

Magick::Image imagegen::draw_color(const std::string &cl) {
    auto r = s16tod(cl.substr(0, 2));
    auto g = s16tod(cl.substr(2, 2));
    auto b = s16tod(cl.substr(4, 2));
    Magick::Image canvas(Magick::Geometry(500, 500), Magick::ColorRGB(r, g, b));
    return canvas;
}

// reads an in memory blob into a string
std::string imagegen::utils::read_blob(Magick::Blob &b) {
    const std::string str{ static_cast<const char*>(b.data()), b.length() };
    return str;
}

std::string imagegen::utils::read_image(Magick::Image im) {
    Magick::Blob buf;
    im.write(&buf, "PNG");
    return read_blob(buf);
}

void imagegen::utils::encode(httplib::Response &res, const Magick::Image &im) {
    res.set_content(read_image(im), "image/png");
}

const bool imagegen::utils::is_valid_hex(std::string &s) {
    // trim leading # and 0x
    if (s[0] == '#') s = s.substr(1);
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) s = s.substr(2);
    // check length before iterating over all chars
    if (s.length() != 6) return false;
    for (auto c: s) {
        if (c > 'f') return false;
    }
    return true;
}
