#include "imagegen.h"
#include "ImageMagick-7/Magick++.h"

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
