#version 330 core
layout (location = 0) in vec3 aPos; // Position of the vertex
layout (location = 1) in vec2 aTexCoord; // Texture coordinate

out vec2 TexCoord; // Pass texture coordinate to fragment shader

void main()
{
    gl_Position = vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}
