package com.opengl.MapBuffers;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;


public class CenterSurfaceView extends GLSurfaceView {

    private MapBuffersRenderer mMapBuffersRenderer;

    public CenterSurfaceView(Context context) {
        super(context);
    }

    public CenterSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        setEGLContextClientVersion(3);
        mMapBuffersRenderer = new MapBuffersRenderer(context);
        setRenderer(mMapBuffersRenderer);
    }

    @Override
    public void onResume() {
        super.onResume();
        setRenderMode(RENDERMODE_WHEN_DIRTY);
        mMapBuffersRenderer.onResume();
    }

    @Override
    public void onPause() {
        super.onPause();
        mMapBuffersRenderer.onPause();
    }
}
