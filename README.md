# 🦀 Pixel Crab Shader Project
This project explores animated pixel art using OpenGL (C++) and GLSL shaders. I created and animated two versions of a pixel crab:

    Vertex Crab (PixelCrab): Constructed by manually placing vertices for each pixel, using a hand-written integer map.

    Texture Crab (RectCrab): A more efficient version using only four vertices and a pixel-art texture.

Both versions were animated with the same walk cycle. During this process, I learned that the textured version allowing for a higher number of crabs on screen due to its simplicity and performance benefits. 

I also implemented fragment shaders (see pixelCrabShader.frag) that dynamically alter the crab's colors based on parameters like time and position—though these are not active in the latest build.

The current executable includes interactive flocking behavior, where crabs are attracted to the mouse position. I also implemented preliminary code for crab-to-crab repulsion, but found it challenging to make the resulting movement feel visually pleasing within the constraints of pixel-style animation—so that feature is currently commented out.

To properly build the solution in Visual Studio Code, you can follow the set-up instructions for creating a OPENGL environment. This involves linking a few dependencies so please be careful as you read :) https://learnopengl.com/Getting-started/Creating-a-window 
