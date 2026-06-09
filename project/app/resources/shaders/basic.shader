#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 u_Transform;

out vec3 ourColor;

void main() {
    gl_Position = u_Transform * vec4(aPos, 1.0);
    ourColor = aColor;
}


#shader fragment
#version 330 core

out vec4 Color;
in vec3 ourColor;

void main() {
    Color = vec4(ourColor, 1.0);
};
