#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;
//flat out int bodyPart;

//uniform bool isMoving; 
uniform int crabFrame;
//uniform float crabPixelSize; 
//uniform vec2 centerPos; // Coordinates of the Center of the Crab 
uniform mat4 transform;

//float epsilon = 0.0000001;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = vec2(aTexCoord.x / 2 + float(crabFrame) / 2, aTexCoord.y);
}
