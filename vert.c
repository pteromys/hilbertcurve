attribute vec4 pos;
varying mediump vec2 vCoord;

void main(void) {
	gl_Position = pos;
	vCoord = pos.xy;
}
