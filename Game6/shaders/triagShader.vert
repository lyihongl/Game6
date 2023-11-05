#version 430 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in float x_center;
layout(location = 2) in float y_center;
layout(location = 3) in float rad;
uniform mat4 MVP;
uniform int h, w;

// flat out vec3 color_;
out vec3 color_;
void main() {
    // int h = 720;
    // int w = 1280;
    // color_ = vec3(2*(aPos.x - mod(aPos.x, 20.f))/w - 1, 2*(aPos.y - mod(aPos.y, 20.f))/h - 1, 0);
    // color_ = vec3(2*(int(aPos.x/2)*2)/w-1, 2*(int(aPos.y/2)*2)/h - 1, 0);
    float x = 2*(aPos.x - x_center); 
    float y = 2*(aPos.y - y_center);
    gl_Position = vec4((x*cos(rad) - y*sin(rad) + 2*x_center)/w-1, 1 - (x*sin(rad) + y*cos(rad) + 2*y_center)/h, 0.0, 1.0);
    // gl_Position = vec4(x*cos(rad) - y*sin(rad) + 2*x_center/w, y*sin(rad) + y*cos(rad) + 2*y_center/h, 0.0, 1.0);
    // gl_Position = vec4(x*cos(rad) - y*sin(rad), y, 0.0, 1.0);
    color_ = vec3(0.5, 0, 0);
    // color_ = vec3(sqrt(pow(gl_Position.x - mod(gl_Position.x, 0.05), 2)), gl_Position.y - mod(gl_Position.y, 0.05), (gl_Position.x + gl_Position.y)/2 - mod((gl_Position.x + gl_Position.y)/2, 0.05));
    // gl_PointSize = 30.0;
}