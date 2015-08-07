#version 120

uniform vec4 fvAmbient;
uniform vec4 fvDiffuse;
uniform vec4 fvSpecular;
uniform float fSpecularPower;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;

varying vec2  Texcoord;
varying vec3  ViewDirection;
varying float LightDistanse;

void main( void )
{
   vec3  fvViewDirection  = normalize( ViewDirection );
   vec3  fvNormal         = normalize( ( texture2D( normalMap, Texcoord ).xyz * 2.0 ) - 1.0 );
   float fNDotL           = dot( fvNormal, fvViewDirection ); 
   
   vec4  fvBaseColor      = texture2D( diffuseMap, Texcoord );
   
   vec4  fvTotalAmbient   = fvAmbient * fvBaseColor; 
   vec4  fvTotalDiffuse   = fvDiffuse * fNDotL * fvBaseColor;
   vec4  fvTotalSpecular  = fvSpecular * ( pow( fNDotL, fSpecularPower ) );
  
   float Attenuation = 1.0 / (0.000005 * LightDistanse * LightDistanse + 0.000003 * LightDistanse + 1.0);

   gl_FragColor = ( Attenuation * (fvTotalDiffuse + fvTotalSpecular) + fvTotalAmbient );
       
}