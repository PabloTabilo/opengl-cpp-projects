#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixVal;

void main() {
    // Set a solid brown color
    // FragColor = vec4(0.6f, 0.4f, 0.2f, 1.0f); // RGB for brown
    FragColor = texture(texture1, TexCoord);
}
