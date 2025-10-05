#version 330 core
layout (triangles) in;                // input primitive type (points, lines, triangles)
layout (triangle_strip, max_vertices = 3) out;  // output primitive type and max vertices

void main() {
    // Just pass the triangle through unchanged
    for (int i = 0; i < 3; i++) {
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
}
