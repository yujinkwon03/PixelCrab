#version 330 core

in vec4 gl_FragCoord;
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;


uniform sampler2D crabTexture;
//uniform vec4 ourColor;
//uniform int crabType;
//uniform bool walkingPhase;
void main()
{
	FragColor = texture(crabTexture, TexCoord);
	if(FragColor.a < 0.9f) discard;
//	FragColor = vec4(0.1f, 0.0f, 0.0f, 1.0f);
} 