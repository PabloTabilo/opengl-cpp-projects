// basic.frag
#version 330 core
out vec4 FragColor;

//uniform vec3 uColor;
in vec2 TexCoord;

uniform sampler2D texture1;

void main()
{
    //FragColor = vec4(uColor, 1.0);
    FragColor = texture(texture1, TexCoord);
}
