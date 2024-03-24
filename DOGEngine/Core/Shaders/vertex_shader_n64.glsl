#version 450 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time; // Pass a time value from your application

void main() {
    // Basic jittering effect
    float jitterAmount = 0.005 * sin(time * 5.0 + aPos.x * aPos.y);
    vec3 jitteredPos = aPos + vec3(jitterAmount);

    gl_Position = projection * view * model * vec4(jitteredPos, 1.0);
    TexCoords = aTexCoords;
}
