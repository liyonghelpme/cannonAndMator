
"											\n\
#ifdef GL_ES								\n\
precision lowp float;						\n\
#endif										\n\
											\n\
varying vec4 v_fragmentColor;				\n\
varying vec2 v_texCoord;					\n\
uniform sampler2D CC_Texture0;				\n\
uniform float radius;                       \n\
											\n\
void main()									\n\
{											\n\
    gl_FragColor = vec4(1, 0, 0, 1) \n\
}											\n\
";

	//gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);			\n
