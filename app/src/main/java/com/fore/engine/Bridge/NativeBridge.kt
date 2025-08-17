package com.fore.engine.Bridge

import android.content.res.AssetManager

object NativeBridge {
    init {
        System.loadLibrary("fore")
    }

    external fun initAssetManager(assetManager: AssetManager)
    external fun onSurfaceCreated()
    external fun onSurfaceChanged(width: Int, height: Int)
    external fun onDrawFrame()
    external fun onCalculateFPS(): Int
}