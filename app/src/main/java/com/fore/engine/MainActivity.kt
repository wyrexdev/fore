package com.fore.engine

import android.content.pm.ActivityInfo
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.view.Window
import android.view.WindowInsetsController
import android.view.WindowManager
import android.widget.FrameLayout
import android.widget.TextView
import com.fore.engine.Bridge.NativeBridge

import com.fore.engine.Core.GLView;

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        NativeBridge.initAssetManager(assets)

        var fps: TextView = findViewById(R.id.fps)

        requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE

        window.insetsController?.let {
            it.hide(android.view.WindowInsets.Type.statusBars())
            it.hide(android.view.WindowInsets.Type.navigationBars())
            it.systemBarsBehavior =
                WindowInsetsController.BEHAVIOR_SHOW_TRANSIENT_BARS_BY_SWIPE
        }

        supportActionBar?.hide()

        val playground = findViewById<FrameLayout>(R.id.playground)
        val surface = GLView(this)

        playground.addView(surface)

        val handler = Handler(Looper.getMainLooper())

        handler.post(object : Runnable {
            override fun run() {
                fps.text = "FPS: " + NativeBridge.onCalculateFPS().toString()
                handler.postDelayed(this, 16)
            }
        })
    }
}