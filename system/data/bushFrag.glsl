#version 130

void main (void) {	
  gl_FragColor = vec4(gl_FragCoord.x,gl_FragCoord.y,gl_FragCoord.z,1.0); //make fragment red	
}
