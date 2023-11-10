#version 430 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D tex;

void main(){
	vec4 intermediate = texture(tex, texCoord);
	//if(intermediate.a < 0.1){
	//	discard;
	//}
	FragColor = 0.2*vec4(texCoord, 0.0, 1.0) + intermediate;
	//FragColor = vec4(texCoord, 0.0, 1.0);
}