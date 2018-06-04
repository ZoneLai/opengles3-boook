package com.opengl.mipmap2d;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;


public class CenterSurfaceView extends GLSurfaceView {

    private MipMap2DRenderer mMipMap2DRenderer;

    public CenterSurfaceView(Context context) {
        super(context);
    }

    public CenterSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        setEGLContextClientVersion(3);
        mMipMap2DRenderer = new MipMap2DRenderer(context);
        setRenderer(mMipMap2DRenderer);
    }

    @Override
    public void onResume() {
        super.onResume();
        setRenderMode(RENDERMODE_WHEN_DIRTY);
        mMipMap2DRenderer.onResume();
    }

    @Override
    public void onPause() {
        super.onPause();
        mMipMap2DRenderer.onPause();
    }
}
