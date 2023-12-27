#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float mixWeight;

void main()
{
	// FragColor = vec4(ourColor, 1.0f);
	// FragColor = texture(texture1, TexCoord);
	FragColor = mix(texture(texture0, TexCoord), texture(texture1, vec2(1.0f-TexCoord.x, TexCoord.y)), mixWeight);
};