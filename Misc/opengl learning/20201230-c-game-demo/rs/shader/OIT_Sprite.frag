#version 460 core
layout (early_fragment_tests) in;

layout (binding = 0, offset = 0) uniform atomic_uint CounterBuf;
layout (binding = 2, rgba32ui) uniform uimageBuffer FragBuf;
layout (binding = 1, r32ui) uniform uimage2D HeadPtrTex;

layout (binding = 0) uniform sampler2D TexSrc;
in vec4 fvColor;
in vec2 fvTexCoord;
uniform vec4 FlashColor;
uniform bool SingleChannel;

void main() {
	vec4 TempColor = texture(TexSrc, fvTexCoord);
	if(SingleChannel) {
		TempColor = vec4(1.0f,1.0f,1.0f,TempColor.r);
	}
	TempColor = fvColor * TempColor;
	TempColor = vec4(mix(TempColor.rgb, FlashColor.rgb, FlashColor.a), TempColor.a);
	uint index = atomicCounterIncrement(CounterBuf);
	uint head = imageAtomicExchange(HeadPtrTex, ivec2(gl_FragCoord.xy), index);
	uvec4 item = uvec4(
		head,
		packUnorm4x8(TempColor), 
		floatBitsToUint(gl_FragCoord.z),
		0
	);
	imageStore(FragBuf, int(index), item);
}