#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D screenTexture; // The texture

void main()
{
    vec4 color = texture(screenTexture, TexCoord);

    // Simulate scanlines
    float scanlineEffect = sin(TexCoord.y * 800.0) * 0.1;
    color -= scanlineEffect;

    // Basic phosphor glow effect (simplistic)
    float dist = distance(TexCoord, vec2(0.5, 0.5));
    color *= 1.0 - dist * 0.1;

    FragColor = color;
}
