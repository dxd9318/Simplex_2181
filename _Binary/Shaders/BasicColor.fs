#version 330

in vec3 Color;

uniform vec3 SolidColor = vec3(-1,-1,-1);
uniform bool complement = false;

out vec4 Fragment;

void main()
{
	Fragment = vec4(Color,1);
	vec3 Output; 
	
	if(SolidColor.r != -1.0 && SolidColor.g != -1.0 && SolidColor.b != -1.0)
		Fragment = vec4(SolidColor, 1);
		Output = Fragment.xyz;
	if(complement){
		Output = vec3(1,1,1) - Output;
	}
	Fragment = vec4(Output, 1);

	return;
}