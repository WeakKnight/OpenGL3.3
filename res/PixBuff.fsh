//
//#version 120
//
//uniform sampler2D textureUnit1;
//varying vec2 vVaryingTexCoord;
//
//void main(void)
//{
//    gl_FragColor = texture2D(textureUnit1, vVaryingTexCoord);
//    //gl_FragColor = vec4(0, 1, 0, 1);
//}

#version 120

uniform sampler2D textureUnit1;
varying vec2 vVaryingTexCoord;

void main()
{
    gl_FragColor = texture2D(textureUnit1, vVaryingTexCoord);
}