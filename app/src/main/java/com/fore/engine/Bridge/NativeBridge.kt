package com.fore.engine.Bridge

object NativeBridge {
    init {
        System.loadLibrary("fore")
    }

    external fun onSurfaceCreated()
    external fun onSurfaceChanged(width: Int, height: Int)
    external fun onDrawFrame()
    external fun onCalculateFPS(): Int
}