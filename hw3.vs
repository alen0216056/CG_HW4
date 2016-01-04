varying vec3 normal, lightDir, eyeDir, tangent_t, tangent_b;

void main()
{	
	normal = gl_NormalMatrix * gl_Normal;
	tangent_t = gl_NormalMatrix * gl_MultiTexCoord3.xyz;
	tangent_b = cross(normal, tangent_t);

	vec3 vVertex = vec3(gl_ModelViewMatrix * gl_Vertex);

	lightDir = vec3(gl_LightSource[0].position.xyz - vVertex);
	eyeDir = -vVertex;
	
	gl_TexCoord[0].xy = gl_MultiTexCoord0.xy;
	gl_TexCoord[1].xy = gl_MultiTexCoord1.xy;
	gl_TexCoord[2].xy = gl_MultiTexCoord2.xy;
	gl_Position = ftransform();		
	//gl_Position = gl_ProjectionMatrix*gl_ModelViewMatrix * gl_Vertex;
}