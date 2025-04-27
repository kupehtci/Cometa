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
};

in vec3 FragPos;
in vec3 Normal;
in vec2 texCoord;

uniform vec3 uViewPos;
uniform Material material;
uniform Light light;

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
    FragColor = vec4(result, 1.0);

}