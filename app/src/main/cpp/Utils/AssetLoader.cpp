#include "AssetLoader.h"
#include "../stb/stb_image.h"
#include <android/log.h>

AAssetManager* AssetLoader::assetManager = nullptr;

void AssetLoader::initAssetManager(JNIEnv* env, jobject assetManagerObj) {
    assetManager = AAssetManager_fromJava(env, assetManagerObj);
    if (assetManager == nullptr) {
        __android_log_print(ANDROID_LOG_ERROR, "AssetLoader", "Failed to get asset manager");
    }
}

std::vector<unsigned char> AssetLoader::loadAsset(const char* filename) {
    std::vector<unsigned char> data;
    
    if (assetManager == nullptr) {
        __android_log_print(ANDROID_LOG_ERROR, "AssetLoader", "Asset manager not initialized");
        return data;
    }

    AAsset* asset = AAssetManager_open(assetManager, filename, AASSET_MODE_BUFFER);
    if (asset == nullptr) {
        __android_log_print(ANDROID_LOG_ERROR, "AssetLoader", "Failed to open asset: %s", filename);
        return data;
    }

    long size = AAsset_getLength(asset);
    data.resize(size);
    
    AAsset_read(asset, data.data(), size);
    AAsset_close(asset);
    
    return data;
}

unsigned char* AssetLoader::loadImageAsset(const char* filename, int* width, int* height, int* channels) {
    if (assetManager == nullptr) {
        __android_log_print(ANDROID_LOG_ERROR, "AssetLoader", "Asset manager not initialized");
        return nullptr;
    }

    AAsset* asset = AAssetManager_open(assetManager, filename, AASSET_MODE_BUFFER);
    if (asset == nullptr) {
        __android_log_print(ANDROID_LOG_ERROR, "AssetLoader", "Failed to open asset: %s", filename);
        return nullptr;
    }

    long size = AAsset_getLength(asset);
    std::vector<unsigned char> buffer(size);
    AAsset_read(asset, buffer.data(), size);
    AAsset_close(asset);

    unsigned char* data = stbi_load_from_memory(buffer.data(), size, width, height, channels, 0);
    
    if (data == nullptr) {
        __android_log_print(ANDROID_LOG_ERROR, "AssetLoader", "Failed to decode image: %s", filename);
    }
    
    return data;
}
