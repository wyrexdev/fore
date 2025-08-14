package com.fore.engine.Core

import android.content.Context
import android.opengl.GLSurfaceView
import com.fore.engine.Bridge.NativeBridge
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class GLView(context: Context) : GLSurfaceView(context) {
    init {
        setEGLContextClientVersion(3)

        setRenderer(object: Renderer {
            override fun onDrawFrame(gl: GL10?) {
                NativeBridge.onDrawFrame()
            }

            override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
                NativeBridge.onSurfaceChanged(width, height)
            }

            override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
                NativeBridge.onSurfaceCreated()
            }
        })

        renderMode = RENDERMODE_CONTINUOUSLY
    }
}