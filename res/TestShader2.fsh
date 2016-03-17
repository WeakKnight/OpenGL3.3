
#version 330 core

in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec3 lightPosition;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float timer;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
    sampler2D texDiffuse;
    sampler2D texSpecular;
};

uniform Material material;

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light simpleLight;

struct DirectionalLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirectionalLight directionalLight;

//
struct PointLight
{
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};

uniform PointLight pointLight;

//
struct SpotLight
{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform SpotLight spotLight;



//
void textureMaterialShader(bool useTextureMaterial, bool textureChange);
void directionLightShader();
void pointLightShader();
void spotLightShader();
void multiplelightsShader();


//==============================================================================================================
void main()
{
    const int tag = 5;
    if (tag == 1)
    {
        //贴图混合和颜色
        textureMaterialShader(true, true);
    }
    else if (tag == 2)
    {
        //方向光
        directionLightShader();
    }
    else if (tag == 3)
    {
        //点光源
        pointLightShader();
    }
    else if (tag == 4)
    {
        //聚光灯
        spotLightShader();
    }
    else if (tag == 5)
    {
        //多光源
        multiplelightsShader();
    }
}
//==============================================================================================================





//==============================================================================================================
void textureMaterialShader(bool useTextureMaterial, bool textureChange)
{
    vec4 colorOfTexture1 = texture(ourTexture1, TexCoord);
    vec4 colorOfTexture2 = texture(ourTexture2, TexCoord);
    vec4 textureColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), timer);
    
    //Ambient--------------------------------------------------------------------------------
    vec3 ambient = vec3(1.0f, 1.0f, 1.0f);
    if (useTextureMaterial)
    {
        ambient = simpleLight.ambient * vec3(texture(material.texDiffuse, TexCoord));
    }
    else
    {
        ambient = simpleLight.ambient * material.ambient;
    }
    
    // Diffuse--------------------------------------------------------------------------------
    vec3 diffuse = vec3(1.0f, 1.0f, 1.0f);
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    if (useTextureMaterial)
    {
        diffuse = simpleLight.diffuse * diff * vec3(texture(material.texDiffuse, TexCoord));
    }
    else
    {
        diffuse = simpleLight.diffuse * (diff * material.diffuse);
    }
    
    // Specular--------------------------------------------------------------------------------
    vec3 specular = vec3(1.0f, 1.0f, 1.0f);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    if (useTextureMaterial)
    {
        specular = simpleLight.specular * spec * vec3(texture(material.texSpecular, TexCoord));
    }
    else
    {
        specular = simpleLight.specular * (spec * material.specular);
    }
    
    //--------------------------------------------------------------------------------
    vec3 result = ambient + diffuse + specular;
    if (textureChange)
    {
        color = textureColor * vec4(result, 1.0f);
    }
    else
    {
        color = vec4(result, 1.0f);
    }
}


//==============================================================================================================
void directionLightShader()
{
    /*
     当一个光源很远的时候，来自光源的每条光线接近于平行。这看起来就像所有的光线来自于同一个方向，无论物体和观察者在哪儿。当一个光源被设置为无限远时，它被称为定向光(也被成为平行光)，因为所有的光线都有着同一个方向；它会独立于光源的位置。
     
     我们知道的定向光源的一个好例子是，太阳。太阳和我们不是无限远，但它也足够远了，在计算光照的时候，我们感觉它就像无限远。在下面的图片里，来自于太阳的所有的光线都被定义为平行光：
     
     
     因为所有的光线都是平行的，对于场景中的每个物体光的方向都保持一致，物体和光源的位置保持怎样的关系都无所谓。由于光的方向向量保持一致，光照计算会和场景中的其他物体相似。
     */
    
    // Ambient
    vec3 ambient = directionalLight.ambient * vec3(texture(material.texDiffuse, TexCoord));
    
    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-directionalLight.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = directionalLight.diffuse * diff * vec3(texture(material.texDiffuse, TexCoord));
    
    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = directionalLight.specular * spec * vec3(texture(material.texSpecular, TexCoord));
    
    color = vec4(ambient + diffuse + specular, 1.0f);
}


//==============================================================================================================
void pointLightShader()
{
    // Ambient
    vec3 ambient = pointLight.ambient * vec3(texture(material.texDiffuse, TexCoord));
    
    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = pointLight.diffuse * diff * vec3(texture(material.texDiffuse, TexCoord));
    
    // Specular
    vec3 viewDir = normalize(lightPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = pointLight.specular * spec * vec3(texture(material.texSpecular, TexCoord));
    
    // Attenuation
    float distance = length(lightPosition - FragPos);
    float att = (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));
    
    float attenuation = 1.0f;
    if (att > 0.0f)
    {
        attenuation = 1.0f/att;
    }
  
    //
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    
    //
    color = vec4(ambient + diffuse + specular, 1.0f);
}

//==============================================================================================================
void spotLightShader()
{
    vec3 lightDir = normalize(spotLight.position - FragPos);
    
    // Check if lighting is inside the spotlight cone
    float theta = dot(lightDir, normalize(-spotLight.direction));
    float epsilon = spotLight.cutOff - spotLight.outerCutOff;
    float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);
    
    // Ambient
    vec3 ambient = spotLight.ambient * vec3(texture(material.texDiffuse, TexCoord));
    
    // Diffuse
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = spotLight.diffuse * diff * vec3(texture(material.texDiffuse, TexCoord));
    
    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spotLight.specular * spec * vec3(texture(material.texSpecular, TexCoord));
    
    // Attenuation
    float distance = length(spotLight.position - FragPos);
    float attenuation = 1.0f / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * (distance * distance));
    
    //
    diffuse  *= attenuation;
    specular *= attenuation;
    
    //
    diffuse  *= intensity;
    specular *= intensity;
    
    color = vec4(ambient + diffuse + specular, 1.0f);
}

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // 计算漫反射强度
    float diff = max(dot(normal, lightDir), 0.0);
    // 计算镜面反射强度
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 合并各个光照分量
    vec3 ambient  = light.ambient  * vec3(texture(material.texDiffuse, TexCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.texDiffuse, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.texSpecular, TexCoord));
    return (ambient + diffuse + specular);
}

// 计算定点光在确定位置的光照颜色
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(lightPosition - fragPos);
    // 计算漫反射强度
    float diff = max(dot(normal, lightDir), 0.0);
    // 计算镜面反射
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 计算衰减
    float distance    = length(lightPosition - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance +
                                light.quadratic * (distance * distance));
    // 将各个分量合并
    vec3 ambient  = light.ambient  * vec3(texture(material.texDiffuse, TexCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.texDiffuse, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.texSpecular, TexCoord));
    
    //
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    
    //
    return (ambient + diffuse + specular);
}

// 计算定点光在确定位置的光照颜色
// Calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // Spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // Combine results
    vec3 ambient = light.ambient * vec3(texture(material.texDiffuse, TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.texDiffuse, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.texSpecular, TexCoord));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

//==============================================================================================================
void multiplelightsShader()
{
    // 一些属性
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // 第一步，计算平行光照
    vec3 result = vec3(0.1f);
    
    //方向光
    result = CalcDirLight(directionalLight, norm, viewDir);
    
    //点光
    result += CalcPointLight(pointLight, norm, FragPos, viewDir);

    //Spotlight
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
    
    //
    color = vec4(result, 1.0);
}




