#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D screenTexture; // The texture

void main()
{
    float pixelSize = 0.01; // Size of the 'pixels' on the LCD screen
    float spacing = 0.002; // Spacing between pixels to simulate the LCD grid

    // Calculate the current "pixel" based on the texture coordinate
    vec2 pos = floor(TexCoord / pixelSize);

    // Determine the sub-pixel position for the RGB effect
    float subPixel = mod(pos.x + pos.y, 3.0);

    // Sample the texture
    vec4 color = texture(screenTexture, TexCoord);

    // Apply a simple RGB effect based on the sub-pixel position
    if(subPixel == 0.0) color *= vec4(1.0, 0.0, 0.0, 1.0); // Red
    else if(subPixel == 1.0) color *= vec4(0.0, 1.0, 0.0, 1.0); // Green
    else color *= vec4(0.0, 0.0, 1.0, 1.0); // Blue

    // Implement spacing effect
    if(mod(TexCoord.x, pixelSize + spacing) < spacing || mod(TexCoord.y, pixelSize + spacing) < spacing)
        color = vec4(0.0, 0.0, 0.0, 1.0); // Black lines for spacing

    FragColor = color;
}
