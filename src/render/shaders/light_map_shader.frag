#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuseMap;
    sampler2D specularMap;
    sampler2D emissionMap;

    bool hasDiffuseMap;
    bool hasSpecularMap;
    bool hasEmissionMap;

    vec3 diffuse;
    vec3 specular;

    vec3 color;
    vec3 ambient;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    bool isDirectional;

    float constant;
    float linear;
    float quadratic;
};

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Position of the fragment
in vec3 FragPos;
// defines the normal of the fragment
in vec3 Normal;
// Texture coordinate
in vec2 texCoord;

uniform vec3 uViewPos;
uniform Material material;
uniform Light light;

uniform DirectionalLight directionalLight;

vec3 CalculateDirectionalLight(DirectionalLight dirLight, vec3 fragNormal, vec3 viewDirection)
{
    vec3 lightDirection = normalize(-dirLight.direction);
    float diff = max(dot(fragNormal, lightDirection), 0.0);

    vec3 reflectedDirection = reflect(-lightDirection, fragNormal);
    float spec = pow(max(dot(viewDirection, reflectedDirection), 0.0), material.shininess);

    vec3 ambient = dirLight.ambient * vec3(texture(material.diffuseMap, texCoord));
    vec3 diffuse = dirLight.diffuse * diff * vec3(texture(material.diffuseMap, texCoord));
    vec3 specular = dirLight.specular * spec * vec3(texture(material.specularMap, texCoord));

    vec3 result = ambient + diffuse + specular;
    return result;
}

void main()
{
    // ambient
    vec3 ambient = vec3(0.0, 0.0, 0.0);

    if(material.hasDiffuseMap){
        ambient = light.ambient * vec3(texture(material.diffuseMap, texCoord));
    }
    else {
        ambient = light.ambient * material.ambient;
    }

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse = vec3(0.0, 0.0, 0.0);

    if(material.hasDiffuseMap){
        diffuse = light.diffuse * (diff * vec3(texture(material.diffuseMap, texCoord)));
    }
    else {
        diffuse = light.diffuse * (diff * material.diffuse);
    }

    // specular
    vec3 viewDir = normalize(uViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 specular = vec3(0.0, 0.0, 0.0);

    if(material.hasSpecularMap){
        specular = light.specular * (spec * vec3(texture(material.specularMap, texCoord)));
    }
    else {
        specular = light.specular * (spec * material.specular);
    }


    // emission
    vec3 emission = vec3(0.0, 0.0, 0.0);

    if(material.hasEmissionMap){
        emission = texture(material.emissionMap, texCoord).rgb;
    }



    // results
    vec3 result = (ambient + diffuse + specular + emission) * material.color;

    result += CalculateDirectionalLight(directionalLight, norm, viewDir);

    FragColor = vec4(result, 1.0);

}