#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    vec2 halvedTexCoord = vec2(TexCoord.x/2, TexCoord.y/2);
    FragColor = mix(texture(texture1, halvedTexCoord), texture(texture2, TexCoord), 0.2);
}
