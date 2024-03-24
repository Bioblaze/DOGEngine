#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    vec3 posJitter = aPos + vec3(0.005 * sin(gl_InstanceID), 0.005 * cos(gl_InstanceID), 0);
    gl_Position = projection * view * model * vec4(posJitter, 1.0);
    TexCoord = aTexCoord;
}
