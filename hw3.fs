varying vec3 normal, lightDir, eyeDir, tangent_t, tangent_b;
uniform sampler2D colorTexture1, colorTexture2, colorTexture3;

void main (void)
{
	vec3 N = normalize(normal);
	vec3 L = normalize(lightDir);
	vec3 T = normalize(tangent_t);
	vec3 B = normalize(tangent_b);
	
	vec3 new_N = (2*(texture2D(colorTexture1, gl_TexCoord[0].xy).r-0.5))*T + (2*(texture2D(colorTexture1, gl_TexCoord[0].xy).g-0.5))*B + (2*(texture2D(colorTexture1, gl_TexCoord[0].xy).b-0.5))*N;
	new_N =  normalize(new_N);
	
	vec4 final_color = (gl_FrontLightModelProduct.sceneColor * gl_FrontMaterial.ambient) + (gl_LightSource[0].ambient * gl_FrontMaterial.ambient);
					
	float lambertTerm = dot(new_N,L);
	
	if(lambertTerm > 0.0){
		final_color += gl_LightSource[0].diffuse * texture2D(colorTexture2, gl_TexCoord[1].xy).rgba * lambertTerm;
		vec3 E = normalize(eyeDir);
		vec3 R = reflect(-L, new_N);
		float specular = pow( max(dot(R, E), 0.0), gl_FrontMaterial.shininess );
		final_color += gl_LightSource[0].specular * texture2D(colorTexture3, gl_TexCoord[1].xy).rgba * specular;	
	}
	gl_FragColor = final_color;
}
