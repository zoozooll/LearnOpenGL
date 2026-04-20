package com.example.learnopengl

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MyGLRenderer : GLSurfaceView.Renderer {

    companion object {
        init {
            System.loadLibrary("textures_combined")
        }
    }

    private external fun onInit()
    private external fun onSizeChanged(width: Int, height: Int)
    private external fun onDraw()
    private external fun onDestroy()

    fun cleanUp() {
        onDestroy()
    }

    override fun onSurfaceCreated(unused: GL10, config: EGLConfig) {
        onInit()
    }

    override fun onDrawFrame(unused: GL10) {
        onDraw()
    }

    override fun onSurfaceChanged(unused: GL10, width: Int, height: Int) {
        onSizeChanged(width, height)
    }
}
