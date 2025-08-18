#ifndef FOREGINE_ASSETLOADER_H
#define FOREGINE_ASSETLOADER_H

#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <vector>

class AssetLoader {
private:
    static AAssetManager* assetManager;

public:
    static void initAssetManager(JNIEnv* env, jobject assetManagerObj);
    static std::vector<unsigned char> loadAsset(const char* filename);
    static unsigned char* loadImageAsset(const char* filename, int* width, int* height, int* channels);
};

#endif //FOREGINE_ASSETLOADER_H
