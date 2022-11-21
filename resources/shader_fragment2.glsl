#version 330 core
out vec4 color;
in vec3 vertex_normal;
in vec3 vertex_pos;
in vec2 vertex_tex;
uniform vec3 campos;

uniform sampler2D tex;
void main()
{
    vec2 tempTex = vertex_tex;
    tempTex /= 8;
    vec4 tempCol = texture(tex, tempTex+0.48);
    color = tempCol;
    color.a = (1 - length(tempCol)) * -0.5;
}
