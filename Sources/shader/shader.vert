#extension GL_ARB_shading_language_100
#extension GL_ARB_shader_objects
#extension GL_ARB_vertex_shader
#extension GL_ARB_fragment_shader
#version 150 core

in vec3 in_Vertex;
in vec3 in_Color;
in vec3 in_TexCoord0;

out vec4 out_Color;

void main(void)
{
	 gl_TexCoord[0] = gl_TextureMatrix[0];
	 //gl_TexCoord[0] = in_TexCoord0;
	 gl_Position = gl_Vertex*gl_ModelViewProjectionMatrix;
	 gl_Color = in_Color;
}