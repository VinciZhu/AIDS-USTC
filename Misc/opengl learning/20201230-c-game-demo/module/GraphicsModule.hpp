/////////////////////////
//封装OpenGL图形接口的模块
/////////////////////////

#pragma once

//着色器子模块
#include "ShaderModule.hpp"

//纹理子模块
#include "TextureModule.hpp"

//2D形状子模块(依赖于着色器子模块、纹理子模块)
#include "Shape2D_Module.hpp"

//2D精灵子模块(依赖于2D形状子模块)
#include "SpriteModule.hpp"

//渲染子模块(依赖于着色器子模块)
#include "RenderModule.hpp"