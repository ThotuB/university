package cg.bouncysquare;

import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.opengles.GL11;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

public class Square {
    private FloatBuffer mFVertexBuffer;
    private ByteBuffer mColorBuffer;
    private ByteBuffer mIndexBuffer;

    public Square() {
        float vertices[]= {
                -2.0f, -1.0f,
                1.0f, -1.0f,
                -1.0f, 1.0f,
                1.0f, 1.0f
        };

        byte maxColor = (byte)255;
        byte colors[] = {
                0, maxColor, 0, maxColor,
                0, maxColor, 0, maxColor,
                0, maxColor, 0, maxColor,
                0, maxColor, 0, maxColor,
        };

        byte indices[] = {
                0, 3, 1,
                0, 2, 3
        };

        ByteBuffer vbb = ByteBuffer.allocateDirect(vertices.length * 4);
        vbb.order(ByteOrder.nativeOrder());

        mFVertexBuffer = vbb.asFloatBuffer();
        mFVertexBuffer.put(vertices);
        mFVertexBuffer.position(0);

        mColorBuffer = ByteBuffer.allocateDirect(colors.length);
        mColorBuffer.put(colors);
        mColorBuffer.position(0);

        mIndexBuffer = ByteBuffer.allocateDirect(indices.length);
        mIndexBuffer.put(indices);
        mIndexBuffer.position(0);
    }

    public void draw(GL10 gl)
    {
        gl.glFrontFace(GL11.GL_CW);
        gl.glVertexPointer(2, GL11.GL_FLOAT, 0, mFVertexBuffer);
        gl.glColorPointer(4, GL11.GL_UNSIGNED_BYTE, 0, mColorBuffer);
        int[] geometry = {
                GL11.GL_TRIANGLES,
                GL11.GL_POINTS,
                GL11.GL_LINE_STRIP,
                GL11.GL_LINE_LOOP,
                GL11.GL_LINES,
                GL11.GL_TRIANGLE_STRIP,
                GL11.GL_TRIANGLE_FAN
        };
        gl.glDrawElements(geometry[6], 6, GL11.GL_UNSIGNED_BYTE, mIndexBuffer);
    }
}