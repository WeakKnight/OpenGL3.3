// ADS Point lighting Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 120

vec4 vFragColor;

uniform vec4       ambientColor;
uniform vec4       diffuseColor;   
uniform vec4       specularColor;
uniform sampler2D  cloudTexture;
uniform float      dissolveFactor;

varying vec3 vVaryingNormal;
varying vec3 vVaryingLightDir;
varying vec2 vVaryingTexCoord;

void main(void)
{
    vec4 vCloudSample = texture2D(cloudTexture, vVaryingTexCoord);
    
    if(vCloudSample.r < dissolveFactor)
        discard;
    
    
    // Dot product gives us diffuse intensity
    float diff = max(0.0, dot(normalize(vVaryingNormal), normalize(vVaryingLightDir)));
    
    // Multiply intensity by diffuse color, force alpha to 1.0
    vFragColor = diff * diffuseColor;
    
    // Add in ambient light
    vFragColor += ambientColor;
    
    
    // Specular Light
    vec3 vReflection = normalize(reflect(-normalize(vVaryingLightDir), normalize(vVaryingNormal)));
    float spec = max(0.0, dot(normalize(vVaryingNormal), vReflection));
    if(diff != 0) {
        float fSpec = pow(spec, 128.0);
        vFragColor.rgb += vec3(fSpec, fSpec, fSpec);
    }
    
    gl_FragColor = vFragColor;
}
    