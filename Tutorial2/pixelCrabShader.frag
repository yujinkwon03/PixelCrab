#version 330 core

in vec4 gl_FragCoord;
flat in int bodyPart;
in vec4 vertexColor;
out vec4 FragColor;

uniform vec4 ourColor;
uniform int crabType;
uniform bool walkingPhase;
void main()
{
//	FragColor = vec4(gl_FragCoord.xy / vec2(800.0f, 800.0f), 0.0f, 1.0f);
	if(bodyPart == 1) // crab body
	{
		if(crabType == 0) 
		{
			FragColor = vec4(gl_FragCoord.xy / vec2(1200.0f, 1200.0f), 0.0f, 1.0f);
		} else if(crabType == 1) {
			FragColor = vec4(vertexColor);
		} else if(crabType == 2) {
			FragColor = vec4(vertexColor);
		} else if(crabType == 3) {
			FragColor = vec4( ourColor.x, ourColor.y, vertexColor.zw);
		} else if(crabType == 4) {
			FragColor = vec4(ourColor.y + 0.4, 0.0f, ourColor.y + 0.8, vertexColor.w);
		} else if(crabType == 5) {
			FragColor = vec4( ourColor.y, ourColor.y, ourColor.y, vertexColor.w);
		} else {
			FragColor = vec4(vertexColor.x, ourColor.y, vertexColor.zw);
		}

	} else if(bodyPart == 2) // crab eyes 
	{
		FragColor = vec4(0.1f, 0.0f, 0.0f, 1.0f);
	}
} 