#version 430 core

layout(location = 0) in vec2 offset;
layout(location = 1) in vec2 size;
layout(location = 2) in vec3 pos;
layout(location = 3) in vec4 sprite;
layout(location = 4) in vec2 sheetSize;
uniform mat4 MVP;
uniform float h, w;
uniform vec2 cameraOffset;

//out vec3 _color;
out vec2 texCoord;

void main() {
    // gl_Position = vec4((x*cos(rad) - y*sin(rad) + 2*x_center)/w-1, 1 - (x*sin(rad) + y*cos(rad) + 2*y_center)/h, 0.0, 1.0);
	float rad = pos.z;
	//float xoffset = (w/2 - cameraOffset.x)/w;
	//float yoffset = (cameraOffset.y - h/2)/h;
	gl_Position = vec4(
		2*(pos.x-cameraOffset.x + offset.x*size.x*cos(rad)-offset.y*size.y*sin(rad))/w-1,
		1-2*(pos.y-cameraOffset.y + offset.y*size.y*cos(rad)+sin(rad)*offset.x*size.x)/h, 
		0.0, 1.0
	);
	// texCoord = vec2((sprite.x+float(sprite.z)/2 + offset.x*sprite.z/2)/sheetSize.x, (sprite.y+sprite.w/2 + offset.y*sprite.w/2)/sheetSize.y);
	texCoord = vec2((sprite.x+float(sprite.z)/2 + offset.x*sprite.z/2)/sheetSize.x, 
						sprite.y/sheetSize.y+sprite.w/sheetSize.y*(offset.y > 0 ? offset.y : 0.0f));
	// gl_Position = vec4(offset, 0.0, 1.0);
}
