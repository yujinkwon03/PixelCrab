#version 330 core
layout(location = 0) in vec3 aPos;
out vec4 vertexColor;
flat out int bodyPart;

uniform bool isMoving; 
uniform bool walkingPhase;
uniform float crabPixelSize; 
uniform vec2 centerPos; // Coordinates of the Center of the Crab 
uniform mat4 transform;

float epsilon = 0.0000001;

void main()
{
	vertexColor = vec4(1.0f, 0.5f, 0.3f, 1.0f);
	vec2 currPos = aPos.xy;

	if(isMoving && walkingPhase) 
	{
		// Calculate the Leg Positions of Stationary Crab 
		vec2 leg1Pos = centerPos + (crabPixelSize * vec2(-8.0, -5.0));
		vec2 leg2Pos = centerPos + (crabPixelSize * vec2(-6.0, -5.0));
		vec2 leg3Pos = centerPos + (crabPixelSize * vec2(5.0,-5.0));;
		vec2 leg4Pos = centerPos + (crabPixelSize * vec2(7.0, -5.0));


		// If the vertex is part of a leg pixel, change its position so that the 
		if(currPos.y <= leg1Pos.y) 
		{
			if((currPos.x >= leg1Pos.x - epsilon && currPos.x <= leg1Pos.x + crabPixelSize + epsilon) || (currPos.x >= leg3Pos.x - epsilon && currPos.x <= leg3Pos.x + crabPixelSize + epsilon))
			{
				vec2 newLegPos = aPos.xy - vec2(crabPixelSize, 0.0);
				gl_Position = vec4(newLegPos, aPos.z, 1.0);
			} else if((currPos.x >= leg2Pos.x  - epsilon && currPos.x <= leg2Pos.x + crabPixelSize + epsilon) || (currPos.x >= leg4Pos.x - epsilon && currPos.x <= leg4Pos.x + crabPixelSize+ epsilon))
			{
				vec2 newLegPos = aPos.xy + vec2(crabPixelSize, 0.0);
				gl_Position = vec4(newLegPos, aPos.z, 1.0);
			} else {
				gl_Position = vec4(aPos.x, 0.5, aPos.z, 1.0);
			}

		} else {
			gl_Position = vec4(aPos, 1.0);
		}

		bodyPart = 1;

	} else	
	{
		// Set the Eye Color differently 
		vec2 eye1Pos = centerPos + crabPixelSize * vec2(-2.0, 3.0);
		vec2 eye2Pos = centerPos + crabPixelSize * vec2(1.0, 3.0);

		if((currPos.y <= eye1Pos.y + epsilon && currPos.y > eye1Pos.y - crabPixelSize + epsilon) && ((currPos.x >= eye1Pos.x - epsilon && currPos.x < eye1Pos.x + crabPixelSize + epsilon) || (currPos.x >= eye2Pos.x - epsilon && currPos.x < eye2Pos.x + crabPixelSize + epsilon)) ) 
		{
			bodyPart = 2;
		} else 
		{
			bodyPart = 1;
		}

		gl_Position = vec4(aPos, 1.0);
	}

	gl_Position = transform * gl_Position;

}
