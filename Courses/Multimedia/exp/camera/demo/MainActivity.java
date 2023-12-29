/*中国科学技术大学  信息科学技术学院  电子工程与信息科学系  2018.10*/
/*本科生《多媒体技术》课程实验：Android手机上的视频捕捉*/

/*原有《多媒体技术》课程的实验的各个项目都是在Microsoft Visual Studio的Visual C++ 6.0下开发，可以运行在Windows操作系统下。随着智能手机在诸多场合取代了PC机的作用，我们重新考虑原有课程实验项目设置的合理性。
2018年尝试性将Android下多媒体技术开发的内容放入课程实验。
示例代码仅用于教学，代码中对网络上已有代码引用时做了标注。
cxh@ustc.edu.cn,20181007*/
/*
* 本示例程序参考 https://blog.csdn.net/idea_however/article/details/78436470 改写
* 不过 https://www.jianshu.com/p/73fed068a795 关于Android Camera2 的使用总结写得更加详细一些，学习的时候可以查看
*/
package cn.edu.ustc.eeis.videocapture;

import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.ImageFormat;
import android.graphics.SurfaceTexture;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraCaptureSession;
import android.hardware.camera2.CameraDevice;
import android.hardware.camera2.CameraManager;
import android.hardware.camera2.CaptureRequest;
import android.media.Image;
import android.media.ImageReader;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.support.annotation.NonNull;
import android.util.Log;
import android.util.SparseIntArray;
import android.view.Surface;
import android.view.TextureView;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.Toast;

import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;

public class MainActivity extends Activity {

    private final static String TAG = ">>>";
    private static final SparseIntArray ORIENTATIONS = new SparseIntArray();
    // 在关闭摄像机之前阻止应用程序退出的{链接信号量。
    private Semaphore mCameraOpenCloseLock = new Semaphore(1);

    /// 为了使照片竖直显示
    static {
        ORIENTATIONS.append(Surface.ROTATION_0, 90);
        ORIENTATIONS.append(Surface.ROTATION_90, 0);
        ORIENTATIONS.append(Surface.ROTATION_180, 270);
        ORIENTATIONS.append(Surface.ROTATION_270, 180);
    }
    // 预览textureView
    private TextureView textureView;// 用来显示摄像头数据预览
    private Button button_take_picture;// 按钮，抓拍
    private ImageView imageView;// 用来显示抓拍诈照片

    /*
     * 摄像头管理器CameraManager：位于android.hardware.camera2.CameraManager下，也是Android
     * 21(5.0)添加的，
     * 和其他系统服务一样通过 Context.getSystemService(CameraManager.class )
     * 或者Context.getSystemService(Context.CAMERA_SERVICE) 来完成初始化，主要用于管理系统摄像头
     * https://developer.android.google.cn/reference/android/hardware/camera2/
     * CameraManager
     */
    private CameraManager mCameraManager;

    // 摄像头id 通常0代表后置摄像头，1代表前置摄像头
    private String mCameraID;

    /*
     * 处理静态图像捕获
     * https://developer.android.google.cn/reference/android/media/ImageReader
     * The ImageReader class allows direct application access to image data rendered
     * into a Surface
     */
    private ImageReader mImageReader;
    /*
     * 系统向摄像头发送 Capture 请求，而摄像头会返回 CameraMetadata，
     * 这一切都是在由对应的CameraDevice创建的CameraCaptureSession 会话完成，
     * 当程序需要预览、拍照、再次预览时，都需要先通过会话
     */
    private CameraCaptureSession mCameraCaptureSession;

    /*
     * CameraDevice是Camera2中抽象出来的一个对象，直接与系统硬件摄像头相联系
     * https://developer.android.google.cn/reference/android/hardware/camera2/
     * CameraDevice
     */
    private CameraDevice mCameraDevice;

    /*
     * CameraRequest代表了一次捕获请求，
     * 而CameraRequest.Builder用于描述捕获图片的各种参数设置，
     * 包含捕获硬件（传感器，镜头，闪存），对焦模式、曝光模式，
     * 处理流水线，控制算法和输出缓冲区的配置
     */
    private CaptureRequest.Builder previewBuilder;
    private CaptureRequest.Builder pictureBuilder;

    private HandlerThread mHandlerThread;
    private Handler childHandler;

    /*
     * CXH20181007
     * 对象创建完成之后，会执行到该类的onCreate方法，
     * 此onCreate方法是重写父类Activity的onCreate方法而实现的。
     * onCreate方法用来初始化Activity实例对象。
     * 一般情况下我们将自己的初始化代码放置在这个函数内
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // 以下开始自己的代码...
        imageView = (ImageView) findViewById(R.id.imageview_picture_show);
        textureView = (TextureView) findViewById(R.id.textureView_camera);
        textureView.setSurfaceTextureListener(surfaceTextureListener);

        /*
         * CXH20181007
         * 在Android程序中，为控件（按钮）添加监听方式及其处理代码有三种不同的方式
         * 可参考 https://blog.csdn.net/woniu_manpa/article/details/79417498 学习
         * 本示例程序中使用的是内部类的方式 button.setOnClickListener()
         */
        button_take_picture = (Button) findViewById(R.id.button_take_picture);
        button_take_picture.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (button_take_picture.getText().equals("拍照")) {
                    takePicture();
                    button_take_picture.setText("返回");
                } else {
                    button_take_picture.setText("拍照");
                    imageView.setVisibility(View.GONE);// 设置控件是否可视
                    textureView.setVisibility(View.VISIBLE);// 设置控件是否可视
                }
            }
        });

    }

    // TextureView 监听事件
    TextureView.SurfaceTextureListener surfaceTextureListener = new TextureView.SurfaceTextureListener() {
        @Override
        public void onSurfaceTextureAvailable(SurfaceTexture surface, int width, int height) {
            openCamera();
        }

        @Override
        public void onSurfaceTextureSizeChanged(SurfaceTexture surface, int width, int height) {
        }

        @Override
        public boolean onSurfaceTextureDestroyed(SurfaceTexture surface) {
            return false;
        }

        @Override
        public void onSurfaceTextureUpdated(SurfaceTexture surface) {
        }
    };

    /*** 打开摄像头 */
    private void openCamera() {
        if (mHandlerThread == null) {
            mHandlerThread = new HandlerThread("Camera2");
            mHandlerThread.start();
            childHandler = new Handler(mHandlerThread.getLooper());
        }

        if (mImageReader == null) {
            /*
             * CXH20181007：调试例子的过程中发现 TextureView
             * 的尺寸如果和Android中支持的不一致时，无法生成预览，故在示例中手工强制设置为1280*720
             */
            mImageReader = ImageReader.newInstance(1280, 720, ImageFormat.JPEG, 3);
            mImageReader.setOnImageAvailableListener(new ImageReader.OnImageAvailableListener() {
                // 可以在这里处理拍照得到的临时照片 例如，写入本地
                @Override
                public void onImageAvailable(ImageReader reader) {
                    // 拿到拍照照片数据
                    Image image = null;
                    try {
                        image = reader.acquireLatestImage();
                        final Bitmap bitmap = imageToBitmap(image);
                        if (bitmap != null) {
                            runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    textureView.setVisibility(View.GONE);
                                    imageView.setVisibility(View.VISIBLE);
                                    imageView.setImageBitmap(bitmap);
                                }
                            });
                        }
                    } catch (Exception e) {
                        e.printStackTrace();
                    } finally {
                        if (image != null) {
                            image.close();
                            image = null;
                        }
                    }

                }
            }, childHandler);
        }

        if (mCameraManager == null)
            mCameraManager = (CameraManager) getSystemService(Context.CAMERA_SERVICE);

        String cameraIds[] = {};
        try {
            // 获取所有摄像头ID
            cameraIds = mCameraManager.getCameraIdList();
        } catch (CameraAccessException e) {
            Log.e(TAG, "Cam access exception getting IDs", e);
        }
        if (cameraIds.length < 1) {
            Log.e(TAG, "No cameras found");
            return;
        }
        // 通常0代表后置摄像头，1代表前置摄像头
        mCameraID = cameraIds[0];
        try {
            if (!mCameraOpenCloseLock.tryAcquire(2500, TimeUnit.MILLISECONDS)) {
                throw new RuntimeException("Time out waiting to lock camera opening.");
            }
            // if (ActivityCompat.checkSelfPermission(this, Manifest.permission.CAMERA) !=
            // PackageManager.PERMISSION_GRANTED) {
            // Log.e(TAG,"没有照相机权限");
            // return;
            // }else{
            // Log.e(TAG,"有照相机权限");
            // }
            // 开启摄像头
            mCameraManager.openCamera(mCameraID, stateCallback, null);
            Toast.makeText(MainActivity.this, ">>>Open Camera", Toast.LENGTH_SHORT).show();

        } catch (CameraAccessException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            throw new RuntimeException("Interrupted while trying to lock camera opening.", e);
        }
    }

    // 摄像头监听事件
    private CameraDevice.StateCallback stateCallback = new CameraDevice.StateCallback() {
        @Override
        public void onOpened(@NonNull CameraDevice camera) {
            mCameraOpenCloseLock.release();
            // 打开摄像头
            mCameraDevice = camera;

            takePreview();
        }

        @Override
        public void onDisconnected(@NonNull CameraDevice camera) {
            mCameraOpenCloseLock.release();
            // 关闭摄像头
            if (null != mCameraDevice) {
                mCameraDevice.close();
                mImageReader.close();
                mImageReader = null;
            }
            mCameraDevice = null;
        }

        @Override
        public void onError(@NonNull CameraDevice camera, int error) {
            mCameraOpenCloseLock.release();
            mCameraDevice = null;
            // 有错误
            Log.e(TAG, "摄像头开启失败");
            Toast.makeText(MainActivity.this, ">>>摄像头开启失败", Toast.LENGTH_SHORT).show();

        }
    };

    /*** 预览 */
    private void takePreview() {
        SurfaceTexture texture = textureView.getSurfaceTexture();
        /*
         * CXH20181007：调试例子的过程中发现 TextureView
         * 的尺寸如果和Android中支持的不一致时，无法生成预览，故在示例中手工强制设置为1280*720
         */
        texture.setDefaultBufferSize(1280, 720);
        // texture.setDefaultBufferSize(textureView.getWidth(),
        // textureView.getHeight());
        Surface surface = new Surface(texture);
        try {
            if (previewBuilder == null) {
                previewBuilder = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_PREVIEW);
                previewBuilder.addTarget(surface);
                // 自动对焦
                previewBuilder.set(CaptureRequest.CONTROL_AF_MODE, CaptureRequest.CONTROL_AF_MODE_CONTINUOUS_PICTURE);
                // 打开闪光灯
                previewBuilder.set(CaptureRequest.CONTROL_AE_MODE, CaptureRequest.CONTROL_AE_MODE_ON_AUTO_FLASH);

            }
            mCameraDevice.createCaptureSession(Arrays.asList(surface, mImageReader.getSurface()),
                    new CameraCaptureSession.StateCallback() {
                        @Override
                        public void onConfigured(@NonNull CameraCaptureSession session) {
                            if (mCameraDevice == null)
                                return;
                            mCameraCaptureSession = session;
                            try {
                                mCameraCaptureSession.setRepeatingRequest(previewBuilder.build(), null, childHandler);
                            } catch (CameraAccessException e) {
                                e.printStackTrace();
                            }
                        }

                        @Override
                        public void onConfigureFailed(@NonNull CameraCaptureSession session) {
                            Log.e(TAG, "配置错误");
                            Toast.makeText(MainActivity.this, ">>>配置错误", Toast.LENGTH_SHORT).show();
                        }
                    }, null);

        } catch (CameraAccessException e) {
            e.printStackTrace();
        }
    }

    /*** 拍照 */
    private void takePicture() {
        try {
            if (pictureBuilder == null) {
                pictureBuilder = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_STILL_CAPTURE);
                pictureBuilder.addTarget(mImageReader.getSurface());
                // 自动对焦
                pictureBuilder.set(CaptureRequest.CONTROL_AF_MODE, CaptureRequest.CONTROL_AF_MODE_CONTINUOUS_PICTURE);
                // 打开闪光灯
                pictureBuilder.set(CaptureRequest.CONTROL_AE_MODE, CaptureRequest.CONTROL_AE_MODE_ON_AUTO_FLASH);
                int rotation = getWindowManager().getDefaultDisplay().getRotation();
                // 根据设备方向计算设置照片的方向
                pictureBuilder.set(CaptureRequest.JPEG_ORIENTATION, ORIENTATIONS.get(rotation));
            }
            mCameraCaptureSession.capture(pictureBuilder.build(), null, childHandler);
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }
    }

    /*** 关闭摄像头 */
    private void closeCamera() {
        try {
            mCameraOpenCloseLock.acquire();
            if (mCameraCaptureSession != null) {
                mCameraCaptureSession.close();
                mCameraCaptureSession = null;
            }
            if (mCameraDevice != null) {
                mCameraDevice.close();
                mCameraDevice = null;
            }
            if (mImageReader != null) {
                mImageReader.close();
                mImageReader = null;
            }
            stopBackgroundThread();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            mCameraOpenCloseLock.release();
        }
    }

    /**
     * 停止线程
     */
    private void stopBackgroundThread() {
        if (mHandlerThread != null) {
            mHandlerThread.quitSafely();
            try {
                mHandlerThread.join();
                mHandlerThread = null;
                childHandler = null;
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * image转bitmap
     *
     * @param image
     * @return
     */
    private Bitmap imageToBitmap(Image image) {
        ByteBuffer buffer = image.getPlanes()[0].getBuffer();
        byte[] bytes = new byte[buffer.remaining()];
        buffer.get(bytes);// 由缓冲区存入字节数组
        return BitmapFactory.decodeByteArray(bytes, 0, bytes.length);
    }

    @Override
    protected void onPause() {
        super.onPause();
        closeCamera();
    }

    // @Override
    // public void onRequestPermissionsResult(int requestCode, @NonNull String[]
    // permissions, @NonNull int[] grantResults) {
    // if (permissions[0].equals(Manifest.permission.CAMERA) && grantResults[0] ==
    // PackageManager.PERMISSION_GRANTED) {
    // closeCamera();
    // openCamera();
    // }
    // }

}
