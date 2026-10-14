//
// Copyright (C) 2002-2003 3Dlabs Inc. Ltd
//
// This source code is published by 3Dlabs Inc. Ltd., and it is provided
// under the terms of this license agreement. Any use, reproduction or
// distribution of this source code constitutes recipient's acceptance of
// this agreement.
//
// Permission to display, copy distribute, or use this source code for
// experimental, commercial or any other use is granted, provided that this
// entire 3Dlabs copyright statement and license agreement is retained.
//
// Permission to create derivative works from this source code is granted,
// provided all derivative works also retain this entire 3Dlabs copyright
// statement and license agreement.
//
// Any distribution, sublicensing or use of this code shall only be done in
// compliance with any export laws, restrictions, national security
// concerns or regulations of the United States or other applicable agency
// or authority. 
//
// Neither this source code nor its use is represented to conform to any
// particular standard, specification, proposal or other set of
// requirements or conditions.  
//
// THIS SOURCE CODE IS PROVIDED "AS IS" WITH NO WARRANTIES WHATSOEVER,
// WHETHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, AND 3DLABS EXPRESSLY
// DISCLAIMS ANY WARRANTY OF MERCHANTABILITY, NON-INFRINGEMENT, FITNESS FOR
// ANY PARTICULAR PURPOSE, TITLE, OR ANY OTHER WARRANTY, NO MATTER HOW SUCH
// WARRANTY IS ALLEGED TO HAVE ARISEN. 
//
// 3DLABS IS NOT LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL,
// CONSEQUENTIAL, EXEMPLARY OR OTHER DAMAGES (INCLUDING WITHOUT LIMITATION
// LOST PROFITS, DAMAGES BASED ON THE LOSS OF OR DAMAGE TO ANY RECORDS OR
// DATA, OR DAMAGES BASED ON A THIRD PARTY CLAIM) ARISING IN CONNECTION
// WITH THIS SOURCE CODE, HOWEVER CAUSED AND NO MATTER THE THEORY OF
// LIABILITY, EVEN IF 3DLABS HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGES. 
//

//
// Implementation dependent constants.  The example values below
// are the minimum values allowed for these maximums.
//
const int  gl_MaxLights = 8;                    // GL 1.0
const int  gl_MaxClipPlanes = 6;                // GL 1.0
const int  gl_MaxTextureUnits = 2;              // GL 1.2
const int  gl_MaxTextureCoordsARB = 2;          // ARB_fragment_program
const int  gl_MaxVertexAttributesGL2 = 16;      // GL2_vertex_shader
const int  gl_MaxVertexUniformFloatsGL2 = 512;  // GL2_vertex_shader
const int  gl_MaxVaryingFloatsGL2 = 32;         // GL2_vertex_shader
const int  gl_MaxVertexTextureUnitsGL2 = 1;     // GL2_vertex_shader
const int  gl_MaxFragmentTextureUnitsGL2 = 2;   // GL2_fragment_shader
const int  gl_MaxFragmentUniformFloatsGL2 = 64; // GL2_fragment_shader

//
// OpenGL 'uniform' state.  Page numbers are in reference to version
// 1.4 of the OpenGL specification.
//


//
// Matrix state. p. 31, 32, 37, 39, 40.
//
uniform mat4  gl_ModelViewMatrix;
uniform mat4  gl_ProjectionMatrix;
uniform mat4  gl_ModelViewProjectionMatrix;
uniform mat3  gl_NormalMatrix;    // derived
uniform mat4  gl_TextureMatrix[gl_MaxTextureCoordsARB];

//
// Normal scaling p. 39.
//
uniform float gl_NormalScale;

//
// Depth range in window coordinates, p. 33
//
struct gl_DepthRangeParameters {
    float near;        // n
    float far;         // f
    float diff;        // f - n
};
uniform gl_DepthRangeParameters gl_DepthRange;

//
// Clip planes p. 42.
//
uniform vec4  gl_ClipPlane[gl_MaxClipPlanes];

//
// Point Size, p. 66, 67.
//
struct gl_PointParameters {
    float size;
    float sizeMin;
    float sizeMax;
    float fadeThresholdSize;
    float distanceConstantAttenuation;
    float distanceLinearAttenuation;
    float distanceQuadraticAttenuation;
};
 
uniform gl_PointParameters gl_Point;

//
// Material State p. 50, 55.
//
struct gl_MaterialParameters {
    vec4  emission;    // Ecm
    vec4  ambient;     // Acm
    vec4  diffuse;     // Dcm
    vec4  specular;    // Scm
    float shininess;   // Srm
};
uniform gl_MaterialParameters  gl_FrontMaterial;
uniform gl_MaterialParameters  gl_BackMaterial;

//
// Light State p 50, 53, 55.
//

struct gl_LightSourceParameters {
    vec4  ambient;             // Acli
    vec4  diffuse;             // Dcli
    vec4  specular;            // Scli
    vec4  position;            // Ppli
    vec4  halfVector;          // Derived: Hi
    vec3  spotDirection;       // Sdli
    float spotExponent;        // Srli
    float spotCutoff;          // Crli
                               // (range: [0.0,90.0], 180.0)
    float spotCosCutoff;       // Derived: cos(Crli)
                               // (range: [1.0,0.0],-1.0)
    float constantAttenuation; // K0
    float linearAttenuation;   // K1
    float quadraticAttenuation;// K2
};

uniform gl_LightSourceParameters  gl_LightSource[gl_MaxLights];

struct gl_LightModelParameters {
    vec4  ambient;       // Acs
};

uniform gl_LightModelParameters  gl_LightModel;

//
// Derived state from products of light and material.
//

struct gl_LightModelProducts {
    vec4  sceneColor;     // Derived. Ecm + Acm * Acs
};

uniform gl_LightModelProducts gl_FrontLightModelProduct;
uniform gl_LightModelProducts gl_BackLightModelProduct; 

struct gl_LightProducts {
    vec4  ambient;        // Acm * Acli
    vec4  diffuse;        // Dcm * Dcli
    vec4  specular;       // Scm * Scli
};

uniform gl_LightProducts gl_FrontLightProduct[gl_MaxLights];
uniform gl_LightProducts gl_BackLightProduct[gl_MaxLights];

//
// Textureg Environment and Generation, p. 152, p. 40-42.
//
uniform vec4  gl_TextureEnvColor[gl_MaxFragmentTextureUnitsGL2];
uniform vec4  gl_EyePlaneS[gl_MaxTextureCoordsARB];
uniform vec4  gl_EyePlaneT[gl_MaxTextureCoordsARB];
uniform vec4  gl_EyePlaneR[gl_MaxTextureCoordsARB];
uniform vec4  gl_EyePlaneQ[gl_MaxTextureCoordsARB];
uniform vec4  gl_ObjectPlaneS[gl_MaxTextureCoordsARB];
uniform vec4  gl_ObjectPlaneT[gl_MaxTextureCoordsARB];
uniform vec4  gl_ObjectPlaneR[gl_MaxTextureCoordsARB];
uniform vec4  gl_ObjectPlaneQ[gl_MaxTextureCoordsARB];

//
// Fog p. 161
//
struct gl_FogParameters {
    vec4  color;
    float density;
    float start;
    float end;
    float scale;   //  1 / (gl_FogEnd - gl_FogStart)
};
 
uniform gl_FogParameters gl_Fog;
