/////////////////////
//封装着色器程序的模块
/////////////////////

#pragma once

//着色器相关
#include "Shader.hpp"

//着色器文件相关（依赖于着色器）
#include "FileShader.hpp"

//着色器程序相关（依赖于着色器）
#include "ShaderProgram.hpp"

//从文件创建的着色器程序（依赖于着色器、着色器文件）
#include "FileProgram.hpp"