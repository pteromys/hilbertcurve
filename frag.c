uniform int uResolution;
uniform mediump float uThreshold;
uniform mediump float uCoeffLinear, uCoeffLocal, uCoeffConstant;
varying mediump vec2 vCoord;
const int DEPTH = 12;
uniform mediump float uLocality;

mediump float hilbert(mediump vec2 pos) {
	mediump float ix, iy;
	mediump float ans = 0.0, scale = 1.0;
	for (int i = 0; i < DEPTH; i++) {
		// the 0.9 moves [0,1] into [0,1).
		ix = 1.0 + floor(0.9 * pos.x); iy = 1.0 + floor(0.9 * pos.y);
		scale *= 0.25;
		ans += scale * (iy + 3.0 * ix - 2.0 * ix * iy);
		pos = vec2(
			2.0 * (iy * pos.x + (1.0 - iy) * (1.0 - 2.0 * ix) * pos.y) + 1.0 - 2.0 * ix,
			2.0 * (iy * pos.y + (1.0 - iy) * (1.0 - 2.0 * ix) * pos.x) + 1.0 - 2.0 * iy
		);
	}
	return ans + 0.5 * scale;
}

mediump float reparametrize(mediump float t) {
	return uCoeffConstant + t * uCoeffLinear +
		sign(t - uThreshold) * uCoeffLocal * pow(abs(t - uThreshold), 1.0 - uLocality);
}

void main(void) {
	mediump float progress = hilbert(vCoord);
	gl_FragColor = vec4(vec3(reparametrize(progress)), 1.0);
}
