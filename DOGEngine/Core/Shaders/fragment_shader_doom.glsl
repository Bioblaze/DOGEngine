#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;

void main() {
    vec4 texColor = texture(texture1, TexCoord);
    // Simulate limited color palette
    float factor = 1.0 / 16.0; // Example factor, adjust for desired effect
    vec3 limitedColor = floor(texColor.rgb / factor + 0.5) * factor;
    FragColor = vec4(limitedColor, texColor.a);
}
