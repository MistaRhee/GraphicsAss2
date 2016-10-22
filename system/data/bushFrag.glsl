#version 130

void main (void) {	
  gl_FragColor = vec4(gl_FragCoord.x/2000,gl_FragCoord.y/2000,gl_FragCoord.z/2000,1.0); //make fragment red	
}
