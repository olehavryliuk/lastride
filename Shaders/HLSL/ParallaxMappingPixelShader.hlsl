float4 fvAmbient;
float4 fvDiffuse;
float4 fvSpecular;
float fSpecularPower;

sampler2D diffuseMap;
sampler2D normalMap;

struct PS_INPUT
{
   float2 Texcoord :        TEXCOORD0;
   float3 ViewDirection :   TEXCOORD1;
   float  LightDistanse:    TEXCOORD2;
};

static const float parallaxScale = 0.05f;

float2 parallaxMapping(in float3 V, in float2 T, out float parallaxHeight)
{
   // determine required number of layers
   const float minLayers = 5.0;
   const float maxLayers = 10.0;
   float numLayers = lerp(maxLayers, minLayers, abs(dot(float3(0.0f, 0.0f, 1.0f), V)));

   // height of each layer
   float layerHeight = 1.0f / numLayers;
   // depth of current layer
   float currentLayerHeight = 0.0f;
   // shift of texture coordinates for each iteration
   V.y = -V.y;
   float2 dtex = parallaxScale * V.xy / V.z / numLayers;

   // current texture coordinates
   float2 currentTextureCoords = T;

   // depth from heightmap
   float heightFromTexture = 1.0f - tex2D(normalMap, currentTextureCoords).a;
/*
   // while point is above surface
   while(heightFromTexture > currentLayerHeight)
   {
      // go to the next layer
      currentLayerHeight += layerHeight;
      // shift texture coordinates along V
      currentTextureCoords -= dtex;
      // new depth from heightmap
      heightFromTexture = 1.0f - tex2D(normalMap, currentTextureCoords).a;
   }*/
	if (heightFromTexture > currentLayerHeight)
	{
		currentLayerHeight += layerHeight;
		currentTextureCoords -= dtex;
		heightFromTexture = 1.0f - tex2D(normalMap, currentTextureCoords).a;
		if (heightFromTexture > currentLayerHeight)
		{
			currentLayerHeight += layerHeight;
			currentTextureCoords -= dtex;
			heightFromTexture = 1.0f - tex2D(normalMap, currentTextureCoords).a;
			if (heightFromTexture > currentLayerHeight)
			{
				currentLayerHeight += layerHeight;
				currentTextureCoords -= dtex;
				heightFromTexture = 1.0f - tex2D(normalMap, currentTextureCoords).a;
				if (heightFromTexture > currentLayerHeight)
				{
					currentLayerHeight += layerHeight;
					currentTextureCoords -= dtex;
					heightFromTexture = 1.0f - tex2D(normalMap, currentTextureCoords).a;
					if (heightFromTexture > currentLayerHeight)
					{
						currentLayerHeight += layerHeight;
						currentTextureCoords -= dtex;
						heightFromTexture = 1.0f - tex2D(normalMap, currentTextureCoords).a;
						if (heightFromTexture > currentLayerHeight)
						{
							currentLayerHeight += layerHeight;
							currentTextureCoords -= dtex;
							heightFromTexture = 1.0f - tex2D(normalMap, currentTextureCoords).a;
							if (heightFromTexture > currentLayerHeight)
							{
								currentLayerHeight += layerHeight;
								currentTextureCoords -= dtex;
								heightFromTexture = 1.0f - tex2D(normalMap, currentTextureCoords).a;
								if (heightFromTexture > currentLayerHeight)
								{
									currentLayerHeight += layerHeight;
									currentTextureCoords -= dtex;
									heightFromTexture = 1.0f - tex2D(normalMap, currentTextureCoords).a;
									if (heightFromTexture > currentLayerHeight)
									{
										currentLayerHeight += layerHeight;
										currentTextureCoords -= dtex;
										heightFromTexture = 1.0f - tex2D(normalMap, currentTextureCoords).a;
										if (heightFromTexture > currentLayerHeight)
										{
											currentLayerHeight += layerHeight;
											currentTextureCoords -= dtex;
											heightFromTexture = 1.0f - tex2D(normalMap, currentTextureCoords).a;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

   ///////////////////////////////////////////////////////////
   // Start of Relief Parallax Mapping

   // decrease shift and height of layer by half
   float2 deltaTexCoord = dtex / 2.0f;
   float deltaHeight = layerHeight / 2.0f;

   // return to the mid point of previous layer
   currentTextureCoords += deltaTexCoord;
   currentLayerHeight -= deltaHeight;

   // binary search to increase precision of Steep Paralax Mapping
   const int numSearches = 10;
   for(int i=0; i<numSearches; i++)
   {
      // decrease shift and height of layer by half
      deltaTexCoord /= 2.0f;
      deltaHeight /= 2.0f;

      // new depth from heightmap
      heightFromTexture = 1.0f - tex2D(normalMap, currentTextureCoords).a;

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

float parallaxSoftShadowMultiplier(in float3 L, in float2 initialTexCoord, in float initialHeight)
{
   float shadowMultiplier = 1.0f;

   const float minLayers = 3.0f;
   const float maxLayers = 5.0f;

   // calculate lighting only for surface oriented to the light source
   if(dot(float3(0.0f, 0.0f, 1.0f), L) > 0.0f)
   {
      // calculate initial parameters
      float numSamplesUnderSurface = 0.0f;
      shadowMultiplier = 0.0f;
      float numLayers = lerp(maxLayers, minLayers, abs(dot(float3(0.0f, 0.0f, 1.0f), L)));
      float layerHeight = initialHeight / numLayers;
	  L.y = -L.y;
      float2 texStep = parallaxScale * L.xy / L.z / numLayers;

      // current parameters
      float currentLayerHeight = initialHeight - layerHeight;
      float2 currentTextureCoords = initialTexCoord + texStep;
      float heightFromTexture = 1.0f - tex2D(normalMap, currentTextureCoords).a;
      int stepIndex = 1;
/*
      // while point is below depth 0.0 )
      while(currentLayerHeight > 0.0f)
      {
         // if point is under the surface
         if(heightFromTexture < currentLayerHeight)
         {
            // calculate partial shadowing factor
            numSamplesUnderSurface += 1.0f;
            float newShadowMultiplier = (currentLayerHeight - heightFromTexture) * (1.0f - float(stepIndex) / numLayers);
            shadowMultiplier = max(shadowMultiplier, newShadowMultiplier);
         }

         // offset to the next layer
         stepIndex += 1;
         currentLayerHeight -= layerHeight;
         currentTextureCoords += texStep;
         heightFromTexture = 1.0f - tex2D(normalMap, currentTextureCoords).a;
      }
*/		float newShadowMultiplier;
		if(currentLayerHeight > 0.0f)
		{
			if(heightFromTexture < currentLayerHeight)
			{
				numSamplesUnderSurface += 1.0f;
				newShadowMultiplier = (currentLayerHeight - heightFromTexture) * (1.0f - float(stepIndex) / numLayers);
				shadowMultiplier = max(shadowMultiplier, newShadowMultiplier);
			}
			stepIndex += 1;
			currentLayerHeight -= layerHeight;
			currentTextureCoords += texStep;
			heightFromTexture = 1.0f - tex2D(normalMap, currentTextureCoords).a;
			if(currentLayerHeight > 0.0f)
			{
				if(heightFromTexture < currentLayerHeight)
				{
					numSamplesUnderSurface += 1.0f;
					newShadowMultiplier = (currentLayerHeight - heightFromTexture) * (1.0f - float(stepIndex) / numLayers);
					shadowMultiplier = max(shadowMultiplier, newShadowMultiplier);
				}
				stepIndex += 1;
				currentLayerHeight -= layerHeight;
				currentTextureCoords += texStep;
				heightFromTexture = 1.0f - tex2D(normalMap, currentTextureCoords).a;
				if(currentLayerHeight > 0.0f)
				{
					if(heightFromTexture < currentLayerHeight)
					{
						numSamplesUnderSurface += 1.0f;
						newShadowMultiplier = (currentLayerHeight - heightFromTexture) * (1.0f - float(stepIndex) / numLayers);
						shadowMultiplier = max(shadowMultiplier, newShadowMultiplier);
					}
					stepIndex += 1;
					currentLayerHeight -= layerHeight;
					currentTextureCoords += texStep;
					heightFromTexture = 1.0f - tex2D(normalMap, currentTextureCoords).a;
					if(currentLayerHeight > 0.0f)
					{
						if(heightFromTexture < currentLayerHeight)
						{
							numSamplesUnderSurface += 1.0f;
							newShadowMultiplier = (currentLayerHeight - heightFromTexture) * (1.0f - float(stepIndex) / numLayers);
							shadowMultiplier = max(shadowMultiplier, newShadowMultiplier);
						}
						stepIndex += 1;
						currentLayerHeight -= layerHeight;
						currentTextureCoords += texStep;
						heightFromTexture = 1.0f - tex2D(normalMap, currentTextureCoords).a;
						if(currentLayerHeight > 0.0f)
						{
							if(heightFromTexture < currentLayerHeight)
							{
								numSamplesUnderSurface += 1.0f;
								newShadowMultiplier = (currentLayerHeight - heightFromTexture) * (1.0f - float(stepIndex) / numLayers);
								shadowMultiplier = max(shadowMultiplier, newShadowMultiplier);
							}
							stepIndex += 1;
							currentLayerHeight -= layerHeight;
							currentTextureCoords += texStep;
							heightFromTexture = 1.0f - tex2D(normalMap, currentTextureCoords).a;
						}
					}
				}
			}
		}

      // Shadowing factor should be 1 if there were no points under the surface
      if(numSamplesUnderSurface < 1.0f)
      {
         shadowMultiplier = 1.0f;
      }
      else
      {
         shadowMultiplier = 1.0f - shadowMultiplier;
      }
   }
   return shadowMultiplier;
}

float4 normalMappingLighting(in float3 L, in float2 T, float shadowMultiplier, float lightDistance)
{
	L.x = -L.x;
   //L.y = -L.y;
   float3 fvNormal         = normalize(tex2D(normalMap, T).xyz * 2.0f - 1.0f);
   float4 fvBaseColor      = tex2D(diffuseMap, T);
   float fNDotL         = dot(fvNormal, L);

   float4  fvTotalAmbient   = fvAmbient * fvBaseColor;
   float4  fvTotalDiffuse   = fvDiffuse * fNDotL * fvBaseColor;
   float4  fvTotalSpecular  = fvSpecular * ( pow( fNDotL, fSpecularPower ) );

   float Attenuation = 1.0f / (0.000005f * lightDistance * lightDistance + 0.000003f * lightDistance + 1.0f);

   float4 resColor;
   resColor = Attenuation * (fvTotalDiffuse + fvTotalSpecular) * pow(shadowMultiplier, 4.0f) + fvTotalAmbient;

   return resColor;
}

float4 main(PS_INPUT Input) : COLOR0
{
   float3 fvViewDirection  = normalize(Input.ViewDirection);
   
   float fParallaxHeight;
   float2 fvT = parallaxMapping(fvViewDirection, Input.Texcoord, fParallaxHeight);
   float shadowMultiplier = parallaxSoftShadowMultiplier(fvViewDirection, Input.Texcoord, fParallaxHeight - 0.03f);
   //float shadowMultiplier = 1.0f;
   
   return normalMappingLighting(fvViewDirection, fvT, shadowMultiplier, Input.LightDistanse);
};