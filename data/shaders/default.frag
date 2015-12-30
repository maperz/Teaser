#version 330

uniform sampler2D tex;

in vec3 o_col;
in vec2 o_uvs;

out vec4 fragColor;

void main(void)
{
	fragColor = texture(tex,o_uvs);
}