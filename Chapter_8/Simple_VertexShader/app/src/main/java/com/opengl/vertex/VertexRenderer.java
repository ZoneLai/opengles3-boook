// The MIT License (MIT)
//
// Copyright (c) 2013 Dan Ginsburg, Budirijanto Purnomo
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

//
// Book:      OpenGL(R) ES 3.0 Programming Guide, 2nd Edition
// Authors:   Dan Ginsburg, Budirijanto Purnomo, Dave Shreiner, Aaftab Munshi
// ISBN-10:   0-321-93388-5
// ISBN-13:   978-0-321-93388-1
// Publisher: Addison-Wesley Professional
// URLs:      http://www.opengles-book.com
//            http://my.safaribooksonline.com/book/animation-and-3d/9780133440133
//

// Simple_VertexShader
//
//    This is a simple example that draws a rotating cube in perspective
//    using a vertex shader to transform the object
//

package com.opengl.vertex;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.SystemClock;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class VertexRenderer implements GLSurfaceView.Renderer {

    static {
        System.loadLibrary("opengl-lib");
    }

    private float mAngle;
    private long mLastTime = 0;

    public VertexRenderer(Context context) {
        nativeOnCreate();
    }

    @Override
    public void onSurfaceCreated(GL10 glUnused, EGLConfig config) {
        nativeInitGL();
    }

    @Override
    public void onSurfaceChanged(GL10 glUnused, int width, int height) {
        nativeOnSurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 glUnused) {
        update();
        nativeDrawFrame();
    }

    private void update() {
        if (mLastTime == 0) {
            mLastTime = SystemClock.uptimeMillis();
        }
        long curTime = SystemClock.uptimeMillis();
        long elapsedTime = curTime - mLastTime;
        float deltaTime = elapsedTime / 1000.0f;
        mLastTime = curTime;
        mAngle += (deltaTime * 40.0f);
        if (mAngle >= 360.0f) {
            mAngle -= 360.0f;
        }
        nativeRotateAngle(mAngle, 1.0f, 0.0f, 1.0f);
    }

    public void onResume() {
        nativeOnResume();
    }

    public void onPause() {
        nativeOnPause();
    }

    public void onStop() {
        nativeOnStop();
    }

    public void onDestroy() {
        nativeOnDestroy();
    }

    private static native void nativeOnCreate();

    private static native void nativeInitGL();

    private static native void nativeOnResume();

    private static native void nativeOnPause();

    private static native void nativeOnStop();

    private static native void nativeOnDestroy();

    private static native void nativeDrawFrame();

    private static native void nativeOnSurfaceChanged(int width, int height);

    private static native int nativeGetTextureId();

    private static native void nativeRotateAngle(float angle, float xMove, float yMove, float zMove);
}
