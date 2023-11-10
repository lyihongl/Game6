#version 430 core

layout(location = 0) in vec2 offset;
layout(location = 1) in vec2 size;
layout(location = 2) in vec2 pos;
layout(location = 3) in vec4 sprite;
layout(location = 4) in vec2 sheetSize;
uniform mat4 MVP;
uniform int h, w;

//out vec3 _color;
out vec2 texCoord;

void main() {
	gl_Position = vec4((pos.x + offset.x*size.x)/w-1, 1-(pos.y + offset.y*size.y)/h, 0.0, 1.0);
	// texCoord = vec2((sprite.x+float(sprite.z)/2 + offset.x*sprite.z/2)/sheetSize.x, (sprite.y+sprite.w/2 + offset.y*sprite.w/2)/sheetSize.y);
	texCoord = vec2((sprite.x+float(sprite.z)/2 + offset.x*sprite.z/2)/sheetSize.x, 
						(sprite.y+sprite.w)/sheetSize.y*(offset.y > 0 ? offset.y : 0.0f));
	// gl_Position = vec4(offset, 0.0, 1.0);
}
