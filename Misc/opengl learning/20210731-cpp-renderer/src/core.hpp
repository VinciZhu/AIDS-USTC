#pragma once

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <functional>

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include FT_STROKER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace znd {
	using namespace std;
	using namespace glm;

	typedef uint8 byte;
	//Classes
	class Quad;
	class Rect;
	class Square;
	class Shader;
	class Program;
	class Texture;
	class Canvas;
	class Node;
	class Action;
	class Bitmap;
	class Color;
	class FontStyle;
	class Font;
	class Character;
	class Sprite;
	class Mesh;
	class Model;
	class Camera; 
	class Light;
	class DirLight;
	class PointLight;
	class SpotLight;
	class DisplayBox;
	class TextLabel;
	class CommandButton;
	class Application;
	class Graphics;
	class EventResponder;

	class Quad {
	public:
		vec3 coords[4];
		Quad();
		Quad(const vec3& _xyz0, const vec3& _xyz1, const vec3& _xyz2, const vec3& _xyz3);
		Quad(const vec2& _xy0, const vec2& _xy1, const vec2& _xy2, const vec2& _xy3, float _z = 0.0f);
		Quad(
			float _x0, float _y0, float _z0, float _x1, float _y1, float _z1,
			float _x2, float _y2, float _z2, float _x3, float _y3, float _z3
		);
		Quad(
			float _x0, float _y0, float _x1, float _y1,
			float _x2, float _y2, float _x3, float _y3,
			float _z = 0.0f
		);
		~Quad();
		bool operator==(const Quad& _quad);
		bool operator!=(const Quad& _quad);
	};

	class Rect : public Quad {
	public:
		float w;
		float h;
		Rect();
		Rect(const vec3& _xyz0, float _w, float _h);
		Rect(const vec2& _xy0, float _w, float _h, float _z = 0.0f);
		Rect(float _x0, float _y0, float _w, float _h, float _z = 0.0f);
		~Rect();
	};

	class Square : public Rect {
	public:
		float l;
		Square();
		Square(const vec3& _xyz0, float _l);
		Square(const vec2& _xy0, float _l, float _z = 0.0f);
		Square(float _x0, float _y0, float _l, float _z = 0.0f);
		~Square();
	};

	class Action {
	public:
		Action* prev;
		vector<Action*> next;
		void* target;
		union Value {
			float f;
			uint u;
			void* p;
		} value;
		double duration;
		double delta_time;
		int repeat;
		bool pause_flag;
		Action();
		Action(uint _type, float _value, double _duration, Action* _prev = nullptr);
		Action(uint _type, float _value, double _duration, int _repeat, Action* _prev = nullptr);
		Action(void* _target, float _value, double _duration, Action* _prev = nullptr);
		Action(void* _target, float _value, double _duration, int _repeat, Action* _prev = nullptr);
		Action(void* _target, uint _value, double _duration, Action* _prev = nullptr);
		Action(void* _target, uint _value, double _duration, int _repeat, Action* _prev = nullptr);
		Action(void* _target, void* _value, double _duration, Action* _prev = nullptr);
		Action(void* _target, void* _value, double _duration, int _repeat, Action* _prev = nullptr);
		void set_prev(Action* _prev);
		void set_pause_flag(bool _flag);
		~Action();
	};

	class Node {
	public:
		struct LessZ
		{
			bool operator()(const Node* a, const Node* b);
		};
		struct GreaterZ
		{
			bool operator()(const Node* a, const Node* b);
		};
		Node* super;
		vector<Node*> subs;
		vec3 translation;
		vec3 rotation;
		vec3 scaling;
		mat4 trans_mat;
		vector<Action*> actions;
		vector<Action*> destroyed_actions;
		double prev_time;
		Node();
		Node(const vec3& _translation, const vec3& _rotation = vec3(0.0f), const vec3& _scaling = vec3(1.0f));
		~Node();
		void set_super(Node* _super);
		void update_trans_mat();
		Action* wait(double _duration, Action* _prev = nullptr);
		Action* translate_to(const vec3& _translation, double _duration);
		Action* translate_by(const vec3& _translation, double _duration, Action* _prev = nullptr);
		Action* rotate_to(const vec3& _rotation, double _duration);
		Action* rotate_by(const vec3& _rotation, double _duration, Action* _prev = nullptr);
		Action* scale_to(const vec3& _scaling, double _duration);
		Action* scale_by(const vec3& _scaling, double _duration, Action* _prev = nullptr);
		virtual bool update_action(Action* _action);
		void update_actions();
		virtual void update();
		void play(Action* _action);
		void stop(Action* _action);
	};

	class Camera {
	public:
		vec3 position;
		vec3 center;
		float fov;
		float near;
		float far;
		mat4 trans_mat;
		Camera();
		Camera(
			const vec3& _position, const vec3& _center,
			float _fov = radians(45.0f), float _near = 0.1f, float _far = 100.0f
		);
		~Camera();
		void set_position(const vec3& _position);
		void set_center(const vec3& _center);
		void update_trans_mat();
	};

	class Shader {
	public:
		static const string default_directory;
		enum types {
			vertex = GL_VERTEX_SHADER,
			fragment = GL_FRAGMENT_SHADER
		};
		uint name;
		uint type;
		Shader();
		Shader(uint _type, const string& _src);
		Shader(const string& _filename, uint _type);
		~Shader();
	};

	class Program {
	public:
		uint name;
		Program();
		Program(uint _size, Shader* const _shaders[]);
		Program(uint _size, const string _filenames[], const uint _types[]);
		~Program();
		void use();
		void uniform_vec2(const string& _dest, const vec2& _src);
		void uniform_vec3(const string& _dest, const vec3& _src);
		void uniform_vec4(const string& _dest, const vec4& _src);
		void uniform_mat3(const string& _dest, const mat3& _src);
		void uniform_mat4(const string& _dest, const mat4& _src);
		void uniform_bool(const string& _dest, bool _src);
		void uniform_int(const string& _dest, int _src);
		void uniform_uint(const string& _dest, uint _src);
		void uniform_float(const string& _dest, float _src);
	};

	class Bitmap {
	public:
		uint width;
		uint height;
		uint channel_num;
		uint pixel_num;
		vector<byte> data;
		Bitmap();
		~Bitmap();
		Bitmap(uint _width, uint _height, uint _channel_num = 4, const vector<byte>& _src = vector<byte>()); 
		Bitmap(uint _width, uint _height, uint _channel_num, const byte* _src);
		Bitmap(const string& _filename);
	};

	class Texture {
	public:
		enum types {
			common,
			ambient,
			diffuse,
			specular,
			normal,
			tangent,
			bitangent,
			height,
			type_num
		};
		static const string str[type_num];
		static map<string, Texture> cache;
		uint name;
		uint type;
		Texture();
		Texture(const string& _filename, uint _type = common);
		Texture(const Bitmap& _bitmap, uint _type = common);
		~Texture();
		void bind(uint _binding = 0);
		static Texture& get(const string& _filename, uint _type);
	};

	class Canvas : public Texture {
	public:
		uint width;
		uint height;
		vec4 clear_color;
		uint fbo;
		mat4 trans_mat;
		Canvas();
		Canvas(uint _width, uint _height, const vec4& _clear_color = vec4(0.0f, 0.0f, 0.0f, 0.0f));
		~Canvas();
		void set_size(uint _width, uint _height);
	};

	class RenderCanvas : public Canvas {
	public:
		uint rbo;
		bool stencil_flag;
		RenderCanvas();
		RenderCanvas(uint _width, uint _height,
			const vec4& _clear_color = vec4(0.0f, 0.0f, 0.0f, 0.0f), bool _stencil_flag = false);
		~RenderCanvas();
		void set_size(uint _width, uint _height);
	};

	class Color : public vec4 {
	public:
		static const uint default_rgbas[16];
		Color();
		Color(uint _rgba);
		~Color();
		static Color get(uint _rgba);
		static Color get_default(uint _index);
	};

	class Font {
	public:
		static FT_Library lib;
		static map<string, Font> cache;
		static const string default_directory;
		static const string default_filenames[4];
		FT_Face face;
		map<wchar_t, Character*> char_cache;
		Font();
		Font(const string& _filename);
		~Font();
		static void init();
		static void done();
		static Font& get(const string& _filename);
		static Font& get_default(uint _index);
	};

	class FontStyle {
	public:
		uint size;
		uint bolden;
		uint italic;
		bool is_vertical;
	};

	class Character : public Texture {
	public:
		uint size;
		uint bolden;
		uint italic;
		bool is_vertical;
		int left, top;
		int width, rows;
		long advance_x, advance_y;
		Character();
		Character(wchar_t _ch, const Font& _font, uint _size,
			uint _bolden = 0, uint _italic = 0, bool _is_vertical = false);
		~Character();
		static Character& get(wchar_t _ch, const string& _filename, uint _size,
			uint _bolden = 0, uint _italic = 0, bool _is_vertical = false);
		static Character& get(wchar_t _ch, const Font& _font, uint _size,
			uint _bolden = 0, uint _italic = 0, bool _is_vertical = false);
	};

	class Sprite : public Node {
	public:
		struct Frame {
			vec3 translation;
			vec3 rotation;
			vec3 scaling;
			vec4 color;
			vec4 mix_color;
			Texture* texture;
			Rect rect;
			Frame(
				const vec3& _translation = vec3(0.0f), const vec3& _rotation = vec3(0.0f), const vec2& _scaling = vec2(1.0f),
				const vec4& _color = vec4(0.0f), const vec4& _mix_color = vec4(1.0f),
				const Texture* _texture = nullptr, const Rect& = Rect(-1.0f, -1.0f, 2.0f, 2.0f)
			);
			Frame(const Sprite& _sprite);
		};
		class Animation {
		public:
			uint fps;
			map<uint, Frame> keyframes;
			bool relative_flag;
			bool texture_flag;
			bool rect_flag;
			Animation();
			Animation(uint _fps, bool _relative_flag = false, bool _texture_flag = false, bool _rect_flag = false);
			Animation(
				uint _fps, uint _size, const uint _times[], const Frame _frames[],
				bool _relative_flag = false, bool _texture_flag = false, bool _rect_flag = false
			);
			~Animation();
			void convert_to_keyframe(uint _time);
		};
		class Animate {
		public:
			bool pause_flag;
			map<uint, Rect*> rects;
			vector<Action*> root_actions;
			void set_pause_flag(bool _flag);
			void generate_actions(Sprite& _sprite, const Animation& _animation, int _loop = 1);
			Animate();
			Animate(const Animation& _animation);
			~Animate();
			static Animate& get(const Sprite& _sprite, const Animation* _animation);
		};
		uint vao;
		uint vbo;
		uint ebo;
		vec4 color;
		vec4 mix_color;
		Texture* texture;
		Rect rect;
		vector<Animate*> animates;
		map<Animation*, Animate*> animate_cache;
		EventResponder* rsp_ptr;
		Sprite();
		Sprite(const Node& _node, const Texture* _texture, const Rect& _rect);
		Sprite(const vec3& _translation, const Texture* _texture, const Rect& _rect);
		Sprite(const Node& _node, const string& _filename, const Rect& _rect);
		Sprite(const vec3& _translation, const string& _filename, const Rect& _rect);
		~Sprite();
		static uint create_vao(uint _vbo, uint _ebo);
		static uint create_vbo();
		static uint create_ebo();
		void set_rect(const Rect& _rect);
		void render();
		Action* change_color_to(const vec4& _color, double _duration);
		Action* change_mix_color_to(const vec4& _mix_color, double _duration);
		bool update_action(Action* _action);
		void update_animates();
		void update();
		using Node::play;
		using Node::stop;
		void play(Animate* _animate);
		void pause(Animate* _animate);
		void resume(Animate* _animate);
		void stop(Animate* _animate);
		void play(const Animation& _animation, int _loop = 1);
		void pause(const Animation& _animation);
		void resume(const Animation& _animation);
		void stop(const Animation& _animation);
	};

	class Light {
	public:
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
		Light();
		Light(vec3 _ambient, vec3 _diffuse, vec3 _specular);
		Light(float _ambi, float _diff, float _spec, vec3 _color = vec3(1.0f, 1.0f, 1.0f));
		~Light();
	};

	class DirLight : public Light {
	public:
		vec3 direction;
		DirLight();
		DirLight(vec3 _direction, Light _light);
		DirLight(vec3 _direction, vec3 _ambient, vec3 _diffuse, vec3 _specular);
		DirLight(vec3 _direction, float _ambi, float _diff, float _spec, vec3 _color = vec3(1.0f, 1.0f, 1.0f));
		~DirLight();
	};

	class PointLight : public Light {
	public:
		vec3 position;
		float constant;
		float linear;
		float quadratic;
		PointLight();
		PointLight(vec3 _position, Light _light, float _quadratic, float _linear, float _constant = 1.0f);
		PointLight(vec3 _position, vec3 _ambient, vec3 _diffuse, vec3 _specular,
			float _quadratic, float _linear, float _constant = 1.0f);
		PointLight(vec3 _position, float _ambi, float _diff, float _spec, vec3 _color,
			float _quadratic, float _linear, float _constant = 1.0f);
		~PointLight();
	};

	class SpotLight : public Light {
	};

	class Mesh {
	public:
		static map<string, vector<Mesh*>> cache;
		static struct FileLoader{
			uint counter;
			vector<Mesh*>* meshes;
			string directory;
			const aiScene* scene;
			void process_node(const aiNode* _node);
		}loader;
		struct Vert {
			vec3 position;
			vec3 normal;
			vec2 tex_coord;
			vec3 tangent;
			vec3 bitangent;
		};
		vector<Vert> vertices;
		vector<uint> indices;
		vector<Texture*> textures;
		uint vao;
		uint vbo;
		uint ebo;
		float shininess;
		Mesh();
		~Mesh();
		Mesh(const vector<Vert>& _vertices, const vector<uint>& _indices, const vector<Texture*>& _textures);
		static vector<Mesh*>& get(const string& _filename);
		static uint create_vao(uint _vbo, uint _ebo);
		uint create_vbo();
		uint create_ebo();
	};

	class Model : public Node {
	public:
		static const uint normal_loc;
		static const uint tangent_loc;
		static const uint bitangent_loc;
		static const string shader_files[2];
		static const string oit_shader_files[2];
		static Program program;
		vector<Mesh*>* meshes;
		Model();
		~Model();
		Model(const string& _filename, const vec3& _translation);
		Model(const vector<Mesh*>& _meshes, const vec3& _translation);
		static void init();
		void render(const Camera& _camera, const DirLight& _dir_light, const PointLight& _point_light);
		void update();
	};

	namespace Appearance {
		enum styles {
			texture,
			color,
			gradient_h,
			gradient_v
		};
	}

	namespace Direction {
		enum styles {
			horizontal,
			vertical
		};
	}

	namespace Align {
		enum styles {
			left,
			right,
			top,
			bottom,
			center
		};
	}

	class DisplayBox : public Sprite {
	public:
		Canvas canvas;
		uint appearance;
		bool visible_flag;
		DisplayBox();
		~DisplayBox();
		DisplayBox(const vec3& _translation, uint _appearance, const vec4& _color, const Rect& _rect);
		DisplayBox(const vec3& _translation, uint _appearance, const Texture* _texture, const Rect& _rect);
		void render();
		void set_appearance(uint _appearance, const vec4& _color);
		void set_appearance(uint _appearance, const Texture* _texture);
	};

	class TextLabel : public DisplayBox {
	public:
		static const uint font_default_file;
		static const uint font_default_color;
		static const uint font_default_outline_color;
		static const uint font_default_linewidth;
		static const uint font_default_size;
		static const uint font_default_bolden;
		static const uint font_default_italic;
		static const uint font_default_outline;
		wstring text;
		uint direction;
		uint x_align;
		uint y_align;
		Canvas text_canvas;
		Sprite text_sprite;
		TextLabel();
		~TextLabel();
		TextLabel(const vec3& _translation, uint _appearance, const vec4& _color, const Rect& _rect,
			wstring _text = L"", uint _direction = Direction::horizontal,
			uint _x_align = Align::left, uint _y_align = Align::top);
		TextLabel(const vec3& _translation, uint _appearance, const Texture* _texture, const Rect& _rect,
			wstring _text = L"", uint _direction = Direction::horizontal,
			uint _x_align = Align::left, uint _y_align = Align::top);
		void update();
		void render();
		void refresh_text();
		void set_text(wstring _text);
		void set_direction(uint _direction);
		void set_x_align(uint _x_align);
		void set_y_align(uint _y_align);
	};

	class EventResponder {
	public:
		bool down_flag;
		bool in_flag;
		void(*down_callback)();
		void(*up_callback)();
		void(*in_callback)();
		void(*out_callback)();
		EventResponder();
		EventResponder(
			void(*_down_callback)(), void(*_up_callback)() = nullptr,
			void(*_in_callback)() = nullptr, void(*_out_callback)() = nullptr
		);
		~EventResponder();
		virtual void down();
		virtual void up();
		virtual void in();
		virtual void out();
	};

	class CommandButton : public TextLabel {
	public:
		EventResponder responder;
		CommandButton();
		~CommandButton();
		CommandButton(const vec3& _translation, uint _appearance, const vec4& _color, const Rect& _rect,
			wstring _text = L"", uint _direction = Direction::horizontal,
			uint _x_align = Align::left, uint _y_align = Align::top);
		CommandButton(const vec3& _translation, uint _appearance, const Texture* _texture, const Rect& _rect,
			wstring _text = L"", uint _direction = Direction::horizontal,
			uint _x_align = Align::left, uint _y_align = Align::top);
		void update();
	};

	class Renderer {
	public:
		Renderer();
		~Renderer();
		virtual void update();
		virtual void begin();
		virtual void end();
		virtual void render_sprite(const Sprite& _sprite);
		virtual void render_model(const Model& _model);
	};

	class TwoD_Renderer : public Renderer {
	public:
		static const string sprite_shader_files[2];
		static Program sprite_program;
		static void init();
		priority_queue<Sprite*, vector<Sprite*>, Node::GreaterZ> sprites;
		TwoD_Renderer();
		~TwoD_Renderer();
		void update();
		void begin();
		void end();
		void render_sprite(const Sprite& _sprite);
		void render_model(const Model& _model);
	};

	class ThreeD_Renderer : public Renderer {
	public:
		Camera* camera;
		ThreeD_Renderer();
		ThreeD_Renderer(const Camera& _camera);
		~ThreeD_Renderer();
		void update();
		void begin();
		void end();
		void render_sprite(const Sprite& _sprite);
		void render_model(const Model& _model);
	};

	class OIT_Renderer : public Renderer {
	public:
		static const string shader_files[2];
		static const string sprite_shader_files[2];
		static Program program;
		static Program sprite_program;
		static void init();
		OIT_Renderer();
		OIT_Renderer(const Camera& _camera);
		~OIT_Renderer();
		Camera* camera;
		uint frag_buf;
		uint frag_tex;
		uint counter_buf;
		uint head_ptr_tex;
		uint head_ptr_pbo;
		void update();
		void begin();
		void end();
		void render_sprite(const Sprite& _sprite);
		void render_model(const Model& _model);
	};

	namespace Draw
	{
		enum modes {
			normal,
			reverse,
			pixel
		};
	};

	class Graphics : public RenderCanvas {
	public:
		static const string default_directory;
		static const string color_shader_files[2];
		static const string texture_shader_files[2];
		static const string single_channel_shader_files[2];
		static const vec2 tex_coords[4];
		static const mat4 normal_mat;
		static const mat4 reverse_mat;
		uint pixel_num;
		float aspect_ratio;
		Program color_program;
		Program texture_program;
		Program single_channel_program;
		mat4 *draw_mat;
		uint draw_mode;
		Program *draw_program, *prev_draw_program;
		Canvas *canvas, *prev_canvas;
		Renderer *renderer, *prev_renderer;
		Renderer default_renderer;
		TwoD_Renderer render_2d;
		ThreeD_Renderer render_3d;
		OIT_Renderer oit;
		Sprite frame_sprite;
		uint quad_vao;
		uint quad_vbo;
		uint quad_ebo;
		uint rsp_ptr_tex;
		bool rsp_flag;
		void refresh();
		void clear(bool _depth_flag = true, bool _stencil_flag = true);
		void set_size(uint _width, uint _height);
		void set_draw_mode(uint _mode);
		void set_draw_program(const Program& _program);
		void reset_draw_program();
		void set_canvas(const Canvas& _canvas);
		void reset_canvas();
		void set_renderer(const Renderer& _renderer);
		void reset_renderer();
		uint create_quad_vao(uint _vbo, uint _ebo);
		uint create_quad_vbo();
		uint create_quad_ebo();
		void draw(const Quad& _quad);
		void draw(const Quad& _quad, const Program& _program);
		void draw(const Quad& _quad, const vec4& _c);
		void draw(const Quad& _quad, const vec4& _c0, const vec4& _c1, const vec4& _c2, const vec4& _c3);
		void draw(const Quad& _quad, const Bitmap& _bitmap, const vec4& _c = vec4(1.0f));
		void draw(const Quad& _quad, const Texture& _tex, const vec4& _c = vec4(1.0f), bool _is_single_channel = false);
		void draw(const Quad& _quad, const Texture& _tex, 
			const vec4& _c0, const vec4& _c1, const vec4& _c2, const vec4& _c3, bool _is_single_channel = false);
	}graphics;

	class Application {
	public:
		typedef GLFWwindow* Handle;
		typedef GLFWkeyfun KeyFun;
		typedef GLFWwindowsizefun WindowsizeFun;
		typedef GLFWcursorposfun CursorposFun;
		typedef GLFWmousebuttonfun MousebuttonFun;
		typedef GLFWscrollfun ScrollFun;
		static void error_callback(int error, const char* description);
		static void default_key_callback(Handle _handle, int _key, int _scancode, int _action, int _mode);
		static void default_windowsize_callback(Handle _handle, int _width, int _height);
		static void default_cursorpos_callback(Handle _handle, double _xpos, double _ypos);
		static void default_mousebutton_callback(Handle _handle, int _button, int _action, int _mods);
		static void default_scroll_callback(Handle _handle, double _xoffset, double _yoffset);
		Handle handle;
		string title;
		double cur_time, prev_time;
		uint frame_cnt;
		uint fps;
		double cursor_x, cursor_y;
		EventResponder *cur_responder, *prev_responder;
		void init(const string& _title, uint _width, uint _height);
		void done();
		void update();
		void process_events();
		void set_key_callback(KeyFun _callback);
		void set_windowsize_callback(WindowsizeFun _callback);
		void set_cursorpos_callback(CursorposFun _callback);
		void set_mousebutton_callback(MousebuttonFun _callback);
		void set_scroll_callback(ScrollFun _callback);
		bool exit_flag;
	}app;

}