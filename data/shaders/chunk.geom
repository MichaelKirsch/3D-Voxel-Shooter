#version 430 core
layout (points) in;
layout (triangle_strip, max_vertices = 24) out;

uniform mat4 view;
uniform mat4 projection;
uniform float chunkSize;
uniform vec3 chunkPosition;


const float size = 1;
const vec3 lightDirection = normalize(vec3(0.4,-1.0,0.8));

out vec3 colorToSet;

in vec2 o_data[];

void createVertex(vec3 calc_color,vec4 origin, vec3 offset, vec3 faceNormal)
{
    vec4 actualoffset = vec4(offset * size,0.0);
    vec4 worldposition = origin + actualoffset;
    vec4 pos = (projection*view) * worldposition;
    gl_Position = pos;
    float brightness = max(dot(-lightDirection,faceNormal),0.3);
    colorToSet = calc_color * brightness;
    EmitVertex();
}


void main() {
    uint pos_and_sides_raw = floatBitsToUint(o_data[0].x);
    uint id_raw = floatBitsToUint(o_data[0].y);
    ivec3 position;

    uint x = bitfieldExtract(pos_and_sides_raw,24,8);
    uint y = bitfieldExtract(pos_and_sides_raw,16,8);
    uint z = bitfieldExtract(pos_and_sides_raw,8,8);
    uint sides = bitfieldExtract(pos_and_sides_raw,0,8);

    vec3 col_buffer = vec3((1.0/chunkSize)*sides,0.2,0.2);


    vec4 origin = (vec4(float(x)*2,float(y)*2,float(z)*2, 1.0) + vec4(chunkPosition.x*chunkSize*2,chunkPosition.y*chunkSize*2,chunkPosition.z*chunkSize*2,1.0));


    if(bitfieldExtract(sides,1,1))
    {
        //back
        vec3 faceNormal = vec3(0.0, 0.0, 1.0);
        createVertex(col_buffer,origin,vec3(-1.0, 1.0, 1.0), faceNormal);
        createVertex(col_buffer,origin,vec3(-1.0, -1.0, 1.0), faceNormal);
        createVertex(col_buffer,origin,vec3(1.0, 1.0, 1.0), faceNormal);
        createVertex(col_buffer,origin,vec3(1.0, -1.0, 1.0), faceNormal);
        EndPrimitive();
    }

    if(bitfieldExtract(sides,2,1))
    {

        //right
        vec3 faceNormal = vec3(1.0, 0.0, 0.0);
        createVertex(col_buffer, origin, vec3(1.0, 1.0, 1.0), faceNormal);
        createVertex(col_buffer, origin, vec3(1.0, -1.0, 1.0), faceNormal);
        createVertex(col_buffer, origin, vec3(1.0, 1.0, -1.0), faceNormal);
        createVertex(col_buffer, origin, vec3(1.0, -1.0, -1.0), faceNormal);

        EndPrimitive();
    }

    if(bitfieldExtract(sides,4,1))
    {
        //front
        vec3 faceNormal = vec3(0.0, 0.0, -1.0);
        createVertex(col_buffer, origin, vec3(1.0, 1.0, -1.0), faceNormal);
        createVertex(col_buffer, origin, vec3(1.0, -1.0, -1.0), faceNormal);
        createVertex(col_buffer, origin, vec3(-1.0, 1.0, -1.0), faceNormal);
        createVertex(col_buffer, origin, vec3(-1.0, -1.0, -1.0), faceNormal);

        EndPrimitive();
    }


    if((bitfieldExtract(sides,3,1)))
    {
        //left
        vec3 faceNormal = vec3(-1.0, 0.0, 0.0);
        createVertex(col_buffer, origin, vec3(-1.0, 1.0, -1.0), faceNormal);
        createVertex(col_buffer, origin, vec3(-1.0, -1.0, -1.0), faceNormal);
        createVertex(col_buffer, origin, vec3(-1.0, 1.0, 1.0), faceNormal);
        createVertex(col_buffer, origin, vec3(-1.0, -1.0, 1.0), faceNormal);

        EndPrimitive();
    }

if((bitfieldExtract(sides,0,1)))
{
    //up
    vec3 faceNormal = vec3(0.0, 1.0, 0.0);
    createVertex(col_buffer, origin, vec3(1.0, 1.0, 1.0), faceNormal);
    createVertex(col_buffer, origin, vec3(1.0, 1.0, -1.0), faceNormal);
    createVertex(col_buffer, origin, vec3(-1.0, 1.0, 1.0), faceNormal);
    createVertex(col_buffer, origin, vec3(-1.0, 1.0, -1.0), faceNormal);

    EndPrimitive();
}
}