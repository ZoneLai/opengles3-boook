package com.opengl.texture;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;


public class CenterSurfaceView extends GLSurfaceView {

    private Texture2DRenderer mTexture2DRenderer;

    public CenterSurfaceView(Context context) {
        super(context);
    }

    public CenterSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        setEGLContextClientVersion(3);
        mTexture2DRenderer = new Texture2DRenderer(context);
        setRenderer(mTexture2DRenderer);
    }

    @Override
    public void onResume() {
        super.onResume();
        setRenderMode(RENDERMODE_WHEN_DIRTY);
        mTexture2DRenderer.onResume();
    }

    @Override
    public void onPause() {
        super.onPause();
        mTexture2DRenderer.onPause();
    }
}
