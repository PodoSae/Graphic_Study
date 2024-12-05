#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

ImageUPtr Image::Load(const std::string& filepath) {
    auto image = ImageUPtr(new Image());
    if (!image->LoadWithStb(filepath))
        return nullptr;
    return std::move(image);
}

Image::~Image() {
    if (m_data) {
        stbi_image_free(m_data);
    }
}

bool Image::LoadWithStb(const std::string& filepath) {
    m_data = stbi_load(filepath.c_str(), &m_width, &m_height, &m_channelCount, 0);
    if (!m_data) {
        SPDLOG_ERROR("failed to load image: {} {}", filepath, stbi_failure_reason()); // 왜 stbi 실패 했는지 이유 출력
        return false;
    }
    return true;
}