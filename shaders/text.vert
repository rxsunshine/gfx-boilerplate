#version 400 core

layout(location=0) in vec2 in_pos;
layout(location=1) in vec2 in_coord;

out vec2 pass_coord;

uniform vec2 u_tl;
uniform vec2 u_br;
uniform vec2 u_pos;
uniform vec2 u_size;
uniform vec2 u_res;

void main() {
    pass_coord = mix(u_tl, u_br, vec2(in_coord.x, 1.0 - in_coord.y));
    vec2 pos = (in_pos * 0.5 + 0.5) + vec2(0.0, -1.0);
    
    gl_Position = vec4(vec2(-1.0, 1.0) + 2.0 * (pos * u_size + u_pos * vec2(1.0, -1.0)) / u_res, 0.0, 1.0);
}