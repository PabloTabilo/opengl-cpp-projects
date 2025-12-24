#version 330 core

in vec2 vTexCoord;
out vec4 FragColor;

uniform sampler2D uGridTex;

void main()
{
    vec2 uv = vec2(vTexCoord.x, 1.0 - vTexCoord.y);
    FragColor = texture(uGridTex, uv);
}