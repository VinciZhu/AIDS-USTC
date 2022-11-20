#pragma once
#include "core.hpp"
namespace znd {

	Bitmap::Bitmap() {
	}

	Bitmap::Bitmap(uint _width, uint _height, uint _channel_num, const vector<byte>& _src) {
		width = _width;
		height = _height;
		channel_num = _channel_num;
		pixel_num = _width * _height;
		data = _src;
	}

	Bitmap::Bitmap(uint _width, uint _height, uint _channel_num, const byte* _src) {
		width = _width;
		height = _height;
		channel_num = _channel_num;
		pixel_num = _width * _height;
		data.assign(_src, _src + pixel_num * _channel_num);
	}

	Bitmap::Bitmap(const string& _filename) {
		int _width, _height, _channel_num;
		byte* _src = stbi_load((Graphics::default_directory + _filename).c_str(), &_width, &_height, &_channel_num, 0);
		width = _width;
		height = _height;
		channel_num = _channel_num;
		pixel_num = _width * _height;
		data.assign(_src, _src + pixel_num * _channel_num);
		stbi_image_free(_src);
	}

	Bitmap::~Bitmap() {
	}

}