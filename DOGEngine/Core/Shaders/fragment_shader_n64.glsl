#version 450 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;
uniform float time; // Assuming a time uniform for dynamic effects

void main() {
    // Simulate N64's bilinear filtering by manually blending nearby texels.
    vec2 texSize = vec2(textureSize(texture1, 0));
    vec2 nearestTexel = floor(TexCoords * texSize) / texSize;
    vec2 nextTexel = ceil(TexCoords * texSize) / texSize;
    vec4 texelColor1 = texture(texture1, nearestTexel);
    vec4 texelColor2 = texture(texture1, nextTexel);
    vec4 blendedColor = mix(texelColor1, texelColor2, 0.5); // Simple blend for example.

    // Limit the color palette to simulate the N64's color depth.
    vec3 limitedColor = floor(blendedColor.rgb * (256.0 / 32.0)) / (256.0 / 32.0);

    FragColor = vec4(limitedColor, blendedColor.a);

    // Simulate depth precision issues
    float zDepth = gl_FragCoord.z / gl_FragCoord.w;
    if (fract(zDepth * 1000.0) < 0.5) {
        // Adjust the color to simulate a Z-fighting artifact
        FragColor.rgb *= 0.95; // Slightly darken the color to indicate depth collision
    }
}
