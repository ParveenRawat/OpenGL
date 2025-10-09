#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 Normal;
in vec3 crntPos;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

uniform vec3 lightPos;
uniform vec4 lightColor;
uniform vec3 camPos;

vec4 spotLight() {
    float outerCone = 0.90f;
    float innerCone = 0.95f;

    float ambient = 0.4f;

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(vec3(lightPos - crntPos));
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);

    float specularLight = 0.5f;
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0), 16);
    float specular = specAmount * specularLight;

    float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
    float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

    return (texture(diffuse0, texCoord) * (diffuse * intensity + ambient) + texture(specular0, texCoord).r * specular * intensity) * lightColor;
}

vec4 directionalLight() {
    vec3 normal = normalize(Normal);

    float specularLight = 0.5f;
    float ambient = 0.4f;

    vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));

    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);

    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0), 16);

    float specular = specAmount * specularLight;

    float diffuse = max(dot(normal, lightDirection), 0.0f);
    return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}

vec4 pointLight() {
    vec3 lightVec = lightPos - crntPos;
    float dis = length(lightVec);

    float ambient = 0.4;

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightVec);
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularLight = 0.5f;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), ambient), 16);
    float specular = specAmount * specularLight;

    float a = 0.05f;
    float b = 0.01;
    float intensity = 1.0f / (a * dis * dis + b * dis + 1.0f);

    return (texture(diffuse0, texCoord) * (diffuse * intensity + ambient) + texture(specular0, texCoord).r * specular * intensity) * lightColor;
}

void main() {
    FragColor = spotLight();
}
