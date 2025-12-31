// basic.vert
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 vColor;
out vec2 TexCoord;

uniform mat4 transform;
uniform mat4 uProjection;

void main()
{
    vec4 worldPos = transform * vec4(aPos, 1.0);
    gl_Position = uProjection * worldPos;
    
    vColor = aColor;
    TexCoord = aTexCoord;
}
