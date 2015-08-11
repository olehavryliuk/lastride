#version 120

varying vec2 Texcoord;
varying vec3 ViewDirection;
varying float LightDistanse;
   
void main(void)
{
   gl_Position = ftransform();
   Texcoord    = gl_MultiTexCoord0.xy;
    
   vec4 fvObjectPosition = gl_ModelViewMatrix * gl_Vertex;
   
   vec3 fvViewDirection  = -fvObjectPosition.xyz;

   LightDistanse = length(fvViewDirection);
     
   vec3 fvNormal         = gl_NormalMatrix * gl_Normal;
   vec3 fvTangent        = gl_NormalMatrix * gl_MultiTexCoord1.xyz;
   vec3 fvBinormal       = gl_NormalMatrix * gl_MultiTexCoord2.xyz;
      
   ViewDirection.x  = dot(fvTangent, fvViewDirection);
   ViewDirection.y  = dot(fvBinormal, fvViewDirection);
   ViewDirection.z  = dot(fvNormal, fvViewDirection); 
}