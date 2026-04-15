#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <learnopengl/camera.h>
#include <vector>

class Shader;

struct bloomMip
{
	glm::vec2 size;
	glm::ivec2 intSize;
	unsigned int texture;
};

class bloomFBO
{
public:
	bloomFBO();
	~bloomFBO();
	bool Init(unsigned int windowWidth, unsigned int windowHeight, unsigned int mipChainLength);
	void Destroy();
	void BindForWriting();
	const std::vector<bloomMip>& MipChain() const;

private:
	bool mInit;
	unsigned int mFBO;
	std::vector<bloomMip> mMipChain;
};

class BloomRenderer
{
public:
	BloomRenderer();
	~BloomRenderer();
	bool Init(unsigned int windowWidth, unsigned int windowHeight);
	void Destroy();
	void RenderBloomTexture(unsigned int srcTexture, float filterRadius);
	unsigned int BloomTexture();
	unsigned int BloomMip_i(int index);

private:
	void RenderDownsamples(unsigned int srcTexture);
	void RenderUpsamples(float filterRadius);

	bool mInit;
	bloomFBO mFBO;
	glm::ivec2 mSrcViewportSize;
	glm::vec2 mSrcViewportSizeFloat;
	Shader* mDownsampleShader;
	Shader* mUpsampleShader;

	bool mKarisAverageOnDownsample = true;
};

class GLRenderer
{
public:
    GLRenderer();
    virtual ~GLRenderer() = default;

    virtual void OnInit();
    virtual void OnSizeChanged(int width, int height);
    virtual void OnDraw();
    virtual void OnDestroy();

    // Camera
    Camera camera;
    float lastX;
    float lastY;
    bool firstMouse;

    // Timing
    float deltaTime;
    float lastFrame;

    bool bloom;
    float exposure;
    int programChoice;
    float bloomFilterRadius;

private:
    Shader* shader;
    Shader* shaderLight;
    Shader* shaderBlur;
    Shader* shaderBloomFinal;

    unsigned int woodTexture, containerTexture;
    unsigned int hdrFBO;
    unsigned int colorBuffers[2];
    unsigned int rboDepth;
    unsigned int pingpongFBO[2];
    unsigned int pingpongColorbuffers[2];

    std::vector<glm::vec3> lightPositions;
    std::vector<glm::vec3> lightColors;

    BloomRenderer bloomRenderer;

    int m_width;
    int m_height;

    unsigned int loadTexture(const char *path, bool gammaCorrection);
    void renderCube();
};

#endif //GLRENDERER_H
