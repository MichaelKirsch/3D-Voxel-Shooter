#version 330

layout (location = 0) in vec3 data;

//left=0,right,up,down,front,back,underwater,_spare_bit

void main() {
    uint position_x_y = floatBitsToUint(data.y);
    uint position_z_which_spare = floatBitsToUint(data.z);
    uint colors = floatBitsToUint(data.x);


}
