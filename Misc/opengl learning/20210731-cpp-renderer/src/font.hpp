#pragma once
#include "core.hpp"
namespace znd {

	map<string, Font> Font::cache;
	FT_Library Font::lib;
	const string Font::default_directory = "rs/font/";
	const string Font::default_filenames[4] = {
		"msyh.ttc"
	};

	Font::Font() {
	}

	Font::~Font() {
		FT_Done_Face(face);
	}

	Font::Font(const string& _filename) {
		if (FT_New_Face(lib, (default_directory + _filename).c_str(), 0, &face)) {
			cerr << "[Znd] Error: failed to load font: " << _filename << endl;
		}
	}

	void Font::init() {
		if (FT_Init_FreeType(&lib)) {
			cerr << "[Znd] Error: failed to init freetype library" << endl;
		}
	}

	void Font::done() {
		cache.clear();
		FT_Done_FreeType(lib);
	}

	Font& Font::get(const string& _filename) {
		auto itr = cache.find(_filename);
		if (itr == cache.end()) {
			Font& font = cache[_filename];
			new(&font) Font(_filename);
			return font;
		}
		else {
			return itr->second;
		}
	}

	Font& Font::get_default(uint _index) {
		return get(default_filenames[_index]);
	}

}
