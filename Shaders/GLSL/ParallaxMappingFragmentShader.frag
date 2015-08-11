//#version 120

uniform vec4 fvAmbient;
uniform vec4 fvDiffuse;
uniform vec4 fvSpecular;
uniform float fSpecularPower;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;

varying vec2  Texcoord;
varying vec3  ViewDirection;
varying float LightDistanse;

float parallaxScale = 0.03;

vec2 parallaxMapping(in vec3 V, in vec2 T, out float parallaxHeight)
{
   // determine required number of layers
   const float minLayers = 20.0;
   const float maxLayers = 30.0;
   float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), V)));

   // height of each layer
   float layerHeight = 1.0 / numLayers;
   // depth of current layer
   float currentLayerHeight = 0.0;
   // shift of texture coordinates for each iteration
   V.y = -V.y;
   vec2 dtex = parallaxScale * V.xy / V.z / numLayers;

   // current texture coordinates
   vec2 currentTextureCoords = T;

   // depth from heightmap
   float heightFromTexture = 1.0 - texture2D(normalMap, currentTextureCoords).a;

   // while point is above surface
   while(heightFromTexture > currentLayerHeight)
   {
      // go to the next layer
      currentLayerHeight += layerHeight;
      // shift texture coordinates along V
      currentTextureCoords -= dtex;
      // new depth from heightmap
      heightFromTexture = 1.0 - texture2D(normalMap, currentTextureCoords).a;
   }

   ///////////////////////////////////////////////////////////
   // Start of Relief Parallax Mapping

   // decrease shift and height of layer by half
   vec2 deltaTexCoord = dtex / 2.0;
   float deltaHeight = layerHeight / 2.0;

   // return to the mid point of previous layer
   currentTextureCoords += deltaTexCoord;
   currentLayerHeight -= deltaHeight;

   // binary search to increase precision of Steep Paralax Mapping
   const int numSearches = 10;
   for(int i=0; i<numSearches; i++)
   {
      // decrease shift and height of layer by half
      deltaTexCoord /= 2.0;
      deltaHeight /= 2.0;

      // new depth from heightmap
      heightFromTexture = 1.0 - texture2D(normalMap, currentTextureCoords).a;

      // shift along or agains vector V
      if(heightFromTexture > currentLayerHeight) // below the surface
      {
         currentTextureCoords -= deltaTexCoord;
         currentLayerHeight += deltaHeight;
      }
      else // above the surface
      {
         currentTextureCoords += deltaTexCoord;
         currentLayerHeight -= deltaHeight;
      }
   }

   // return results
   parallaxHeight = currentLayerHeight;    
   
   return currentTextureCoords;
}   

float parallaxSoftShadowMultiplier(in vec3 L, in vec2 initialTexCoord, in float initialHeight)
{
   float shadowMultiplier = 1.0;

   const float minLayers = 15.0;
   const float maxLayers = 30.0;

   // calculate lighting only for surface oriented to the light source
   if(dot(vec3(0.0, 0.0, 1.0), L) > 0.0)
   {
      // calculate initial parameters
      float numSamplesUnderSurface = 0.0;
      shadowMultiplier = 0.0;
      float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), L)));
      float layerHeight = initialHeight / numLayers;
      vec2 texStep = parallaxScale * L.xy / L.z / numLayers;

      // current parameters
      float currentLayerHeight = initialHeight - layerHeight;
      vec2 currentTextureCoords = initialTexCoord + texStep;
      float heightFromTexture = 1.0 - texture2D(normalMap, currentTextureCoords).a;
      int stepIndex = 1;

      // while point is below depth 0.0 )
      while(currentLayerHeight > 0.0)
      {
         // if point is under the surface
         if(heightFromTexture < currentLayerHeight)
         {
            // calculate partial shadowing factor
            numSamplesUnderSurface += 1.0;
            float newShadowMultiplier = (currentLayerHeight - heightFromTexture) * (1.0 - float(stepIndex) / numLayers);
            shadowMultiplier = max(shadowMultiplier, newShadowMultiplier);
         }

         // offset to the next layer
         stepIndex += 1;
         currentLayerHeight -= layerHeight;
         currentTextureCoords += texStep;
         heightFromTexture = 1.0 - texture2D(normalMap, currentTextureCoords).a;
      }

      // Shadowing factor should be 1 if there were no points under the surface
      if(numSamplesUnderSurface < 1.0)
      {
         shadowMultiplier = 1.0;
      }
      else
      {
         shadowMultiplier = 1.0 - shadowMultiplier;
      }
   }
   return shadowMultiplier;
}

vec4 normalMappingLighting(in vec3 L, in vec2 T, float shadowMultiplier)
{
	vec3  fvNormal		   = normalize(texture2D(normalMap, T).xyz * 2.0 - 1.0);
	//fvNormal.y = 1.0 - fvNormal.y;
	vec4  fvBaseColor	   = texture2D(diffuseMap, T);
	float fNDotL		   = dot(fvNormal, L);

	vec4  fvTotalAmbient   = fvAmbient * fvBaseColor;
	vec4  fvTotalDiffuse   = fvDiffuse * fNDotL * fvBaseColor;
	vec4  fvTotalSpecular  = fvSpecular * ( pow( fNDotL, fSpecularPower ) );

	float Attenuation = 1.0 / (0.000005 * LightDistanse * LightDistanse + 0.000003 * LightDistanse + 1.0);

	vec4 resColor;
	resColor = Attenuation * (fvTotalDiffuse + fvTotalSpecular) * pow(shadowMultiplier, 4.0) + fvTotalAmbient;

	return resColor;
}

void main(void)
{
	vec3  fvViewDirection  = normalize(ViewDirection);

	float fParallaxHeight;
	vec2 fvT = parallaxMapping(fvViewDirection, Texcoord, fParallaxHeight);
	
	float shadowMultiplier = parallaxSoftShadowMultiplier(fvViewDirection, Texcoord, fParallaxHeight - 0.02);
	//float shadowMultiplier = 1.0;
	
	gl_FragColor = normalMappingLighting(fvViewDirection, fvT, shadowMultiplier);	
}