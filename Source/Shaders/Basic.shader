#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main() {
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
}


#shader fragment
#version 330 core

out vec4 Color;
in vec4 ourColor;

void main() {
    Color = ourColor;
};