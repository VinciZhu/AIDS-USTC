#version 460 core
layout (binding = 0, offset = 0) uniform atomic_uint CounterBuf;
layout (binding = 2, rgba32ui) uniform uimageBuffer FragBuf;
layout (binding = 1, r32ui) uniform uimage2D HeadPtrTex;
layout (binding = 0) uniform sampler2D TexSrc;
in vec2 fvTexCoord;
uniform vec4 Color;
uniform vec4 MixColor;
void main() {
	vec4 temp_color = texture(TexSrc, fvTexCoord);
	temp_color = MixColor * temp_color;
	if(temp_color.a > 0.0){
		temp_color = vec4(mix(temp_color.rgb, Color.rgb, Color.a), temp_color.a);
		uint index = atomicCounterIncrement(CounterBuf);
		uint head = imageAtomicExchange(HeadPtrTex, ivec2(gl_FragCoord.xy), index);
		uvec4 item = uvec4(
			head,
			packUnorm4x8(temp_color), 
			floatBitsToUint(gl_FragCoord.z),
			0
		);
		imageStore(FragBuf, int(index), item);
	}
	discard;
}