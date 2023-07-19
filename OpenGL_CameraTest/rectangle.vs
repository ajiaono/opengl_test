#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
 
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 faceMatrix;

void main()
{
    vec3 lpos =  aPos;
 
    lpos = lpos.x * faceMatrix[0] + lpos.y * faceMatrix[1] + lpos.z * faceMatrix[2];
    
    gl_Position = projection * view * model * vec4(lpos, 1.0f);
      
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}


 