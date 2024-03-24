#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D screenTexture; // The texture of the screen

void main()
{
    vec2 uv = TexCoord;

    // VHS effect
    // Create scanlines
    float scanline = sin(uv.y * 800.0) * 0.1;
    
    // Simulate VHS color distortion
    vec2 dist = vec2(0.005, 0.0); // Shift for red and blue
    float r = texture(screenTexture, uv + dist).r;
    float g = texture(screenTexture, uv).g;
    float b = texture(screenTexture, uv - dist).b;
    
    // Combine effects
    vec3 color = vec3(r, g, b) + scanline;

    FragColor = vec4(color, 1.0);
}
