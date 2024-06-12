#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Inputs from the vertex shader
in vec3 ourColor;
in vec2 TexCoord;

// Gets the texture unit from the main function
uniform sampler2D tex0;

void main()
{
    FragColor = texture(tex0, TexCoord) * vec4(ourColor, 1.0);
}
