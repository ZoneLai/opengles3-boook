package com.opengl.particlesystem;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

public class ParticleSystemView extends GLSurfaceView {

    private ParticleSystemRenderer mTexture2DRenderer;

    public ParticleSystemView(Context context) {
        super(context);
    }

    public ParticleSystemView(Context context, AttributeSet attrs) {
        super(context, attrs);
        setEGLContextClientVersion(3);
        mTexture2DRenderer = new ParticleSystemRenderer(context);
        setRenderer(mTexture2DRenderer);
    }

    @Override
    public void onResume() {
        super.onResume();
        setRenderMode(RENDERMODE_CONTINUOUSLY);
        mTexture2DRenderer.onResume();
    }

    @Override
    public void onPause() {
        super.onPause();
        mTexture2DRenderer.onPause();
    }
}
