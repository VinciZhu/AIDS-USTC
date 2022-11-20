/////////////////////
//封装2D渲染精灵的模块
/////////////////////

#pragma once

//着色器相关
#include "SpriteShader.hpp"

//位图相关
#include "SpriteBitmap.hpp"

//位图文件相关(依赖于位图)
#include "FileSpriteBitmap.hpp"

//位图绘制相关(依赖于位图)
#include "SpriteBitmapDraw.hpp"

//关键帧相关
#include "AnimationKeyframe.hpp"

//动画相关(依赖于关键帧)
#include "SpriteAnimation.hpp"

//渲染精灵相关(依赖于动画、位图、着色器)
#include "Sprite.hpp"

