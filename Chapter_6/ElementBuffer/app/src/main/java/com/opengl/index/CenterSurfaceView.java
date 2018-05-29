package com.opengl.index;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;


public class CenterSurfaceView extends GLSurfaceView {

    private CenterRenderer mCenterRenderer;

    public CenterSurfaceView(Context context) {
        super(context);
    }

    public CenterSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        setEGLContextClientVersion(3);
        mCenterRenderer = new CenterRenderer(context);
        setRenderer(mCenterRenderer);
    }

    @Override
    public void onResume() {
        super.onResume();
        setRenderMode(RENDERMODE_WHEN_DIRTY);
        mCenterRenderer.onResume();
    }

    @Override
    public void onPause() {
        super.onPause();
        mCenterRenderer.onPause();
    }
}
