package com.example.myapplication

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

import android.Manifest
import android.app.Activity
import android.content.pm.PackageManager
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.graphics.ImageFormat
import android.graphics.SurfaceTexture
import android.hardware.camera2.CameraAccessException
import android.hardware.camera2.CameraCaptureSession
import android.hardware.camera2.CameraDevice
import android.hardware.camera2.CameraManager
import android.hardware.camera2.CaptureRequest
import android.media.Image
import android.media.ImageReader
import android.os.Bundle
import android.os.Handler
import android.os.HandlerThread
import android.util.Log
import android.util.SparseIntArray
import android.view.Surface
import android.view.TextureView
import android.view.TextureView.SurfaceTextureListener
import android.view.View
import android.widget.Button
import android.widget.ImageView
import android.widget.Toast
import androidx.core.app.ActivityCompat
import java.util.concurrent.Semaphore
import java.util.concurrent.TimeUnit


class MainActivity : Activity() {
    // 在关闭摄像机之前阻止应用程序退出的{链接信号量。
    private val mCameraOpenCloseLock = Semaphore(1)

    // 预览textureView
    private var textureView: TextureView? = null // 用来显示摄像头数据预览
    private var buttonTakePicture: Button? = null // 按钮，抓拍
    private var imageView: ImageView? = null // 用来显示抓拍诈照片

    /*
     * 摄像头管理器CameraManager：位于android.hardware.camera2.CameraManager下，也是Android
     * 21(5.0)添加的，
     * 和其他系统服务一样通过 Context.getSystemService(CameraManager.class )
     * 或者Context.getSystemService(Context.CAMERA_SERVICE) 来完成初始化，主要用于管理系统摄像头
     * https://developer.android.google.cn/reference/android/hardware/camera2/
     * CameraManager
     */
    private var mCameraManager: CameraManager? = null

    // 摄像头id 通常0代表后置摄像头，1代表前置摄像头
    private var mCameraID: String? = null

    /*
     * 处理静态图像捕获
     * https://developer.android.google.cn/reference/android/media/ImageReader
     * The ImageReader class allows direct application access to image data rendered
     * into a Surface
     */
    private var mImageReader: ImageReader? = null

    /*
     * 系统向摄像头发送 Capture 请求，而摄像头会返回 CameraMetadata，
     * 这一切都是在由对应的CameraDevice创建的CameraCaptureSession 会话完成，
     * 当程序需要预览、拍照、再次预览时，都需要先通过会话
     */
    private var mCameraCaptureSession: CameraCaptureSession? = null

    /*
     * CameraDevice是Camera2中抽象出来的一个对象，直接与系统硬件摄像头相联系
     * https://developer.android.google.cn/reference/android/hardware/camera2/
     * CameraDevice
     */
    private var mCameraDevice: CameraDevice? = null

    /*
     * CameraRequest代表了一次捕获请求，
     * 而CameraRequest.Builder用于描述捕获图片的各种参数设置，
     * 包含捕获硬件（传感器，镜头，闪存），对焦模式、曝光模式，
     * 处理流水线，控制算法和输出缓冲区的配置
     */
    private var previewBuilder: CaptureRequest.Builder? = null
    private var pictureBuilder: CaptureRequest.Builder? = null
    private var mHandlerThread: HandlerThread? = null
    private var childHandler: Handler? = null

    /*
     * CXH20181007
     * 对象创建完成之后，会执行到该类的onCreate方法，
     * 此onCreate方法是重写父类Activity的onCreate方法而实现的。
     * onCreate方法用来初始化Activity实例对象。
     * 一般情况下我们将自己的初始化代码放置在这个函数内
     */
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // 以下开始自己的代码...
        imageView = findViewById<View>(R.id.image_view_picture_show) as ImageView
        textureView = findViewById<View>(R.id.texture_view_camera) as TextureView
        textureView!!.surfaceTextureListener = surfaceTextureListener

        /*
         * CXH20181007
         * 在Android程序中，为控件（按钮）添加监听方式及其处理代码有三种不同的方式
         * 可参考 https://blog.csdn.net/woniu_manpa/article/details/79417498 学习
         * 本示例程序中使用的是内部类的方式 button.setOnClickListener()
         */
        buttonTakePicture = findViewById<View>(R.id.button_take_picture) as Button
        buttonTakePicture!!.setOnClickListener {
            if (buttonTakePicture!!.text == "拍照") {
                takePicture()
                buttonTakePicture!!.text = "返回"
            } else {
                buttonTakePicture!!.text = "拍照"
                imageView!!.visibility = View.GONE // 设置控件是否可视
                textureView!!.visibility = View.VISIBLE // 设置控件是否可视
            }
        }
    }

    // TextureView 监听事件
    private var surfaceTextureListener: SurfaceTextureListener = object : SurfaceTextureListener {
        override fun onSurfaceTextureAvailable(surface: SurfaceTexture, width: Int, height: Int) {
            openCamera()
        }

        override fun onSurfaceTextureSizeChanged(
            surface: SurfaceTexture, width: Int, height: Int
        ) {
        }

        override fun onSurfaceTextureDestroyed(surface: SurfaceTexture): Boolean {
            return false
        }

        override fun onSurfaceTextureUpdated(surface: SurfaceTexture) {}
    }

    /*** 打开摄像头  */
    private fun openCamera() {
        if (mHandlerThread == null) {
            mHandlerThread = HandlerThread("Camera2")
            mHandlerThread!!.start()
            childHandler = Handler(mHandlerThread!!.looper)
        }
        if (mImageReader == null) {/*
             * CXH20181007：调试例子的过程中发现 TextureView
             * 的尺寸如果和Android中支持的不一致时，无法生成预览，故在示例中手工强制设置为1280*720
             */
            mImageReader = ImageReader.newInstance(1280, 720, ImageFormat.JPEG, 3)
            mImageReader!!.setOnImageAvailableListener({ reader ->
                // 可以在这里处理拍照得到的临时照片 例如，写入本地
                // 拿到拍照照片数据
                var image: Image? = null
                try {
                    image = reader.acquireLatestImage()
                    val bitmap = imageToBitmap(image)
                    if (bitmap != null) {
                        runOnUiThread {
                            textureView!!.visibility = View.GONE
                            imageView!!.visibility = View.VISIBLE
                            imageView!!.setImageBitmap(bitmap)
                        }
                    }
                } catch (e: Exception) {
                    e.printStackTrace()
                } finally {
                    image?.close()
                }
            }, childHandler)
        }
        if (mCameraManager == null) mCameraManager =
            getSystemService(CAMERA_SERVICE) as CameraManager
        var cameraIds = arrayOf<String?>()
        try {
            // 获取所有摄像头ID
            cameraIds = mCameraManager!!.cameraIdList
        } catch (e: CameraAccessException) {
            Log.e(TAG, "Cam access exception getting IDs", e)
        }
        if (cameraIds.isEmpty()) {
            Log.e(TAG, "No cameras found")
            return
        }
        // 通常0代表后置摄像头，1代表前置摄像头
        mCameraID = cameraIds[0]
        try {
            if (!mCameraOpenCloseLock.tryAcquire(2500, TimeUnit.MILLISECONDS)) {
                throw RuntimeException("Time out waiting to lock camera opening.")
            }
            if (ActivityCompat.checkSelfPermission(this, Manifest.permission.CAMERA) !=
                PackageManager.PERMISSION_GRANTED
            ) {
                Log.e(TAG, "没有照相机权限")
                return
            } else {
                Log.e(TAG, "有照相机权限")
            }
            // 开启摄像头
            mCameraManager!!.openCamera(mCameraID!!, stateCallback, null)
            Toast.makeText(this@MainActivity, ">>>Open Camera", Toast.LENGTH_SHORT).show()
        } catch (e: CameraAccessException) {
            e.printStackTrace()
        } catch (e: InterruptedException) {
            throw RuntimeException("Interrupted while trying to lock camera opening.", e)
        }
    }

    // 摄像头监听事件
    private val stateCallback: CameraDevice.StateCallback = object : CameraDevice.StateCallback() {
        override fun onOpened(camera: CameraDevice) {
            mCameraOpenCloseLock.release()
            // 打开摄像头
            mCameraDevice = camera
            takePreview()
        }

        override fun onDisconnected(camera: CameraDevice) {
            mCameraOpenCloseLock.release()
            // 关闭摄像头
            if (null != mCameraDevice) {
                mCameraDevice!!.close()
                mImageReader!!.close()
                mImageReader = null
            }
            mCameraDevice = null
        }

        override fun onError(camera: CameraDevice, error: Int) {
            mCameraOpenCloseLock.release()
            mCameraDevice = null
            // 有错误
            Log.e(TAG, "摄像头开启失败")
            Toast.makeText(this@MainActivity, ">>>摄像头开启失败", Toast.LENGTH_SHORT).show()
        }
    }

    /*** 预览  */
    private fun takePreview() {
        val texture = textureView!!.surfaceTexture/*
         * CXH20181007：调试例子的过程中发现 TextureView
         * 的尺寸如果和Android中支持的不一致时，无法生成预览，故在示例中手工强制设置为1280*720
         */
        texture!!.setDefaultBufferSize(1280, 720)
        // texture.setDefaultBufferSize(textureView.getWidth(),
        // textureView.getHeight());
        val surface = Surface(texture)
        try {
            if (previewBuilder == null) {
                previewBuilder = mCameraDevice!!.createCaptureRequest(CameraDevice.TEMPLATE_PREVIEW)
                previewBuilder!!.addTarget(surface)
                // 自动对焦
                previewBuilder!!.set(
                    CaptureRequest.CONTROL_AF_MODE,
                    CaptureRequest.CONTROL_AF_MODE_CONTINUOUS_PICTURE
                )
                // 打开闪光灯
                previewBuilder!!.set(
                    CaptureRequest.CONTROL_AE_MODE, CaptureRequest.CONTROL_AE_MODE_ON_AUTO_FLASH
                )
            }
            mCameraDevice!!.createCaptureSession(
                listOf<Surface>(surface, mImageReader!!.surface),
                object : CameraCaptureSession.StateCallback() {
                    override fun onConfigured(session: CameraCaptureSession) {
                        if (mCameraDevice == null) return
                        mCameraCaptureSession = session
                        try {
                            mCameraCaptureSession!!.setRepeatingRequest(
                                previewBuilder!!.build(), null, childHandler
                            )
                        } catch (e: CameraAccessException) {
                            e.printStackTrace()
                        }
                    }

                    override fun onConfigureFailed(session: CameraCaptureSession) {
                        Log.e(TAG, "配置错误")
                        Toast.makeText(this@MainActivity, ">>>配置错误", Toast.LENGTH_SHORT).show()
                    }
                },
                null
            )
        } catch (e: CameraAccessException) {
            e.printStackTrace()
        }
    }

    /*** 拍照  */
    private fun takePicture() {
        try {
            if (pictureBuilder == null) {
                pictureBuilder =
                    mCameraDevice!!.createCaptureRequest(CameraDevice.TEMPLATE_STILL_CAPTURE)
                pictureBuilder!!.addTarget(mImageReader!!.surface)
                // 自动对焦
                pictureBuilder!!.set(
                    CaptureRequest.CONTROL_AF_MODE,
                    CaptureRequest.CONTROL_AF_MODE_CONTINUOUS_PICTURE
                )
                // 打开闪光灯
                pictureBuilder!!.set(
                    CaptureRequest.CONTROL_AE_MODE, CaptureRequest.CONTROL_AE_MODE_ON_AUTO_FLASH
                )
                val rotation = windowManager.defaultDisplay.rotation
                // 根据设备方向计算设置照片的方向
                pictureBuilder!!.set(
                    CaptureRequest.JPEG_ORIENTATION, ORIENTATIONS[rotation]
                )
            }
            mCameraCaptureSession!!.capture(pictureBuilder!!.build(), null, childHandler)
        } catch (e: CameraAccessException) {
            e.printStackTrace()
        }
    }

    /*** 关闭摄像头  */
    private fun closeCamera() {
        try {
            mCameraOpenCloseLock.acquire()
            if (mCameraCaptureSession != null) {
                mCameraCaptureSession!!.close()
                mCameraCaptureSession = null
            }
            if (mCameraDevice != null) {
                mCameraDevice!!.close()
                mCameraDevice = null
            }
            if (mImageReader != null) {
                mImageReader!!.close()
                mImageReader = null
            }
            stopBackgroundThread()
        } catch (e: Exception) {
            e.printStackTrace()
        } finally {
            mCameraOpenCloseLock.release()
        }
    }

    /**
     * 停止线程
     */
    private fun stopBackgroundThread() {
        if (mHandlerThread != null) {
            mHandlerThread!!.quitSafely()
            try {
                mHandlerThread!!.join()
                mHandlerThread = null
                childHandler = null
            } catch (e: InterruptedException) {
                e.printStackTrace()
            }
        }
    }

    /**
     * image转bitmap
     *
     * @param image
     * @return
     */
    private fun imageToBitmap(image: Image?): Bitmap? {
        val buffer = image!!.planes[0].buffer
        val bytes = ByteArray(buffer.remaining())
        buffer[bytes] // 由缓冲区存入字节数组
        return BitmapFactory.decodeByteArray(bytes, 0, bytes.size)
    }

    override fun onPause() {
        super.onPause()
        closeCamera()
    } // @Override

    // public void onRequestPermissionsResult(int requestCode, @NonNull String[]
    // permissions, @NonNull int[] grantResults) {
    // if (permissions[0].equals(Manifest.permission.CAMERA) && grantResults[0] ==
    // PackageManager.PERMISSION_GRANTED) {
    // closeCamera();
    // openCamera();
    // }
    // }
    companion object {
        private const val TAG = ">>>"
        private val ORIENTATIONS = SparseIntArray()

        /// 为了使照片竖直显示
        init {
            ORIENTATIONS.append(Surface.ROTATION_0, 90)
            ORIENTATIONS.append(Surface.ROTATION_90, 0)
            ORIENTATIONS.append(Surface.ROTATION_180, 270)
            ORIENTATIONS.append(Surface.ROTATION_270, 180)
        }
    }
}

