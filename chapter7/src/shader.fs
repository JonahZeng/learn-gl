#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;
uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
	// FragColor = vec4(ourColor, 1.0f);
	// FragColor = texture(texture1, TexCoord);
	FragColor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.2f);
};