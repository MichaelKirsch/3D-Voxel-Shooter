#version 330
layout (points) in;
layout (triangle_strip, max_vertices = 5) out;
void main() {
    vec4 position = gl_in[0].gl_Position;
    gl_Position = position + vec4(-0.5, -0.5, 0.0, 0.0);    // 1:bottom-left
    EmitVertex();
    gl_Position = position + vec4( 0.5, -0.5, 0.0, 0.0);    // 2:bottom-right
    EmitVertex();
    gl_Position = position + vec4(-0.5,  0.5, 0.0, 0.0);    // 3:top-left
    EmitVertex();
    gl_Position = position + vec4( 0.5,  0.5, 0.0, 0.0);    // 4:top-right
    EmitVertex();
    gl_Position = position + vec4( 0.0,  1.0, 0.0, 0.0);    // 5:top
    EmitVertex();
    EndPrimitive();

}
    //first side
    /*
    gl_Position = gl_in[0].gl_Position + vec4(-0.5f, -0.5f, -0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(0.5f, -0.5f, -0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(0.5f,  0.5f, -0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(0.5f,  0.5f, -0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-0.5f,  0.5f, -0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-0.5f, -0.5f, -0.5f,1.0);
    EmitVertex();
    EndPrimitive();

    //second
    gl_Position = gl_in[0].gl_Position + vec4(-0.5f, -0.5f,  0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(0.5f, -0.5f,  0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(0.5f,  0.5f,  0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(0.5f,  0.5f,  0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-0.5f,  0.5f,  0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-0.5f, -0.5f,  0.5f,1.0);
    EmitVertex();
    EndPrimitive();
    //third
    gl_Position = gl_in[0].gl_Position + vec4(-0.5f,  0.5f,  0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-0.5f,  0.5f, -0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-0.5f, -0.5f, -0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-0.5f, -0.5f, -0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-0.5f, -0.5f,  0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-0.5f,  0.5f,  0.5f,1.0);
    EmitVertex();
    EndPrimitive();
    //fourth
    gl_Position = gl_in[0].gl_Position + vec4(0.5f,  0.5f,  0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(0.5f,  0.5f, -0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(0.5f, -0.5f, -0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(0.5f, -0.5f, -0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(0.5f, -0.5f,  0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(0.5f,  0.5f,  0.5f,1.0);
    EmitVertex();
    EndPrimitive();
    //fifth
    gl_Position = gl_in[0].gl_Position + vec4(-0.5f, -0.5f, -0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(0.5f, -0.5f, -0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(0.5f, -0.5f,  0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(0.5f, -0.5f,  0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-0.5f, -0.5f,  0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-0.5f, -0.5f, -0.5f,1.0);
    EmitVertex();
    EndPrimitive();
    //sixth
    gl_Position = gl_in[0].gl_Position + vec4(-0.5f,  0.5f, -0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(0.5f,  0.5f, -0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(0.5f,  0.5f,  0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(0.5f,  0.5f,  0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-0.5f,  0.5f,  0.5f,1.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-0.5f,  0.5f, -0.5f,1.0);
    EmitVertex();

    EndPrimitive();
}
*/
