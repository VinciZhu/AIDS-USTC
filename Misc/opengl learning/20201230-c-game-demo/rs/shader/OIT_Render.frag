#version 460 core

layout (binding = 2, rgba32ui) uniform uimageBuffer FragBuf;
layout (binding = 1, r32ui) uniform uimage2D HeadPtrTex;

out vec4 fColor;

void main(){
	uint cur_index = imageLoad(HeadPtrTex, ivec2(gl_FragCoord).xy).r;
	uint frag_cnt = 0;
	uvec4 frag_array[32];
	uvec4 frag;
	while (cur_index != 0 && frag_cnt < 32) {
		frag = imageLoad(FragBuf, int(cur_index));
		frag_array[frag_cnt] = frag;
		cur_index = frag.x;
		++frag_cnt;
	}
	uint i, j;
	if (frag_cnt > 1) {
		for (i = 0; i < frag_cnt - 1; ++i) {
			for (j = i + 1; j < frag_cnt; ++j) {
				uvec4 frag1 = frag_array[i];
				uvec4 frag2 = frag_array[j];
				float z1 = uintBitsToFloat(frag1.z);
				float z2 = uintBitsToFloat(frag2.z);
				if (z1 < z2) {
					frag_array[i] = frag2;
					frag_array[j] = frag1;
				}
			}
		}
	}
	vec4 out_color = vec4(0.0f), temp_color;
	for (i = 0; i < frag_cnt; ++i) {
		temp_color = unpackUnorm4x8(frag_array[i].y);
		out_color = mix(out_color, temp_color, temp_color.a);
	}
	fColor = out_color;
}
