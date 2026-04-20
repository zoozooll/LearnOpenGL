param(
    [string]$templateDir = "1.getting_started\1.1.hello_window"
)

$MODULES = @{
    "1.getting_started" = @(
        "1.1.hello_window",
        "1.2.hello_window_clear",
        "2.1.hello_triangle",
        "2.2.hello_triangle_indexed",
        "2.3.hello_triangle_exercise1",
        "2.4.hello_triangle_exercise2",
        "2.5.hello_triangle_exercise3",
        "3.1.shaders_uniform",
        "3.2.shaders_interpolation",
        "3.3.shaders_class",
        "4.1.textures",
        "4.2.textures_combined",
        "4.4.textures_exercise2",
        "4.5.textures_exercise3",
        "4.6.textures_exercise4",
        "5.1.transformations",
        "5.2.transformations_exercise2",
        "6.1.coordinate_systems",
        "6.2.coordinate_systems_depth",
        "6.3.coordinate_systems_multiple",
        "7.1.camera_circle",
        "7.2.camera_keyboard_dt",
        "7.3.camera_mouse_zoom",
        "7.4.camera_class"
    )
    "2.lighting" = @(
        "1.colors",
        "2.1.basic_lighting_diffuse",
        "2.2.basic_lighting_specular",
        "3.1.materials",
        "3.2.materials_exercise1",
        "4.1.lighting_maps_diffuse_map",
        "4.2.lighting_maps_specular_map",
        "4.4.lighting_maps_exercise4",
        "5.1.light_casters_directional",
        "5.2.light_casters_point",
        "5.3.light_casters_spot",
        "5.4.light_casters_spot_soft",
        "6.multiple_lights"
    )
    "3.model_loading" = @(
        "1.model_loading"
    )
    "4.advanced_opengl" = @(
        "1.1.depth_testing",
        "1.2.depth_testing_view",
        "2.stencil_testing",
        "3.1.blending_discard",
        "3.2.blending_sort",
        "5.1.framebuffers",
        "5.2.framebuffers_exercise1",
        "6.1.cubemaps_skybox",
        "6.2.cubemaps_environment_mapping",
        "8.advanced_glsl_ubo",
        "9.1.geometry_shader_houses",
        "9.2.geometry_shader_exploding",
        "9.3.geometry_shader_normals",
        "10.1.instancing_quads",
        "10.2.asteroids",
        "10.3.asteroids_instanced",
        "11.1.anti_aliasing_msaa",
        "11.2.anti_aliasing_offscreen"
    )
    "5.advanced_lighting" = @(
        "1.advanced_lighting",
        "2.gamma_correction",
        "3.1.1.shadow_mapping_depth",
        "3.1.2.shadow_mapping_base",
        "3.1.3.shadow_mapping",
        "3.2.1.point_shadows",
        "3.2.2.point_shadows_soft",
        "4.normal_mapping",
        "5.1.parallax_mapping",
        "5.2.steep_parallax_mapping",
        "5.3.parallax_occlusion_mapping",
        "6.hdr",
        "7.bloom",
        "8.1.deferred_shading",
        "8.2.deferred_shading_volumes",
        "9.ssao"
    )
    "6.pbr" = @(
        "1.1.lighting",
        "1.2.lighting_textured",
        "2.1.1.ibl_irradiance_conversion",
        "2.1.2.ibl_irradiance",
        "2.2.1.ibl_specular",
        "2.2.2.ibl_specular_textured"
    )
    "7.in_practice" = @(
        "1.debugging",
        "2.text_rendering"
    )
}

$GUEST_ARTICLES = @(
    @("8.guest", "2020", "oit"),
    @("8.guest", "2020", "skeletal_animation"),
    @("8.guest", "2021", "1.scene", "1.scene_graph"),
    @("8.guest", "2021", "1.scene", "2.frustum_culling"),
    @("8.guest", "2021", "2.csm"),
    @("8.guest", "2021", "3.tessellation", "terrain_gpu_dist"),
    @("8.guest", "2021", "3.tessellation", "terrain_cpu_src"),
    @("8.guest", "2021", "4.dsa"),
    @("8.guest", "2022", "5.computeshader_helloworld"),
    @("8.guest", "2022", "6.physically_based_bloom"),
    @("8.guest", "2022", "7.area_lights", "1.area_light"),
    @("8.guest", "2022", "7.area_lights", "2.multiple_area_lights")
)

function Get-JavaPackage {
    param(
        [string]$title,
        [string]$tutorial
    )
    $pkgTitle = $title.Replace(".", "_").Replace("-", "_")
    $pkgTutorial = $tutorial.Replace(".", "_").Replace("-", "_")
    return "com.example.learnopengl.$pkgTitle.$pkgTutorial"
}

function Get-JniPackage {
    param(
        [string]$title,
        [string]$tutorial
    )
    $pkgTitle = $title.Replace(".", "_1").Replace("-", "_1")
    $pkgTutorial = $tutorial.Replace(".", "_1").Replace("-", "_1")
    return "Java_com_example_learnopengl_${pkgTitle}_${pkgTutorial}_MyGLRenderer"
}

function Get-LibName {
    param([string]$tutorial)
    return $tutorial.Replace(".", "_").Replace("-", "_")
}

function New-BuildGradle {
    param(
        [string]$title,
        [string]$tutorial
    )
    $pkg = Get-JavaPackage $title $tutorial
    return @"
plugins {
    alias(libs.plugins.android.application)
    alias(libs.plugins.kotlin.compose)
}

android {
    namespace = "$pkg"
    compileSdk = 36

    defaultConfig {
        applicationId = "$pkg"
        minSdk = 24
        targetSdk = 35
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
        externalNativeBuild {
            cmake {
                cppFlags("")
            }
        }
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_11
        targetCompatibility = JavaVersion.VERSION_11
    }

    buildFeatures {
        compose = true
    }
    externalNativeBuild {
        cmake {
            path = file("src/main/cpp/CMakeLists.txt")
            version = "3.22.1"
        }
    }
}

dependencies {
    implementation(libs.androidx.core.ktx)
    implementation(libs.androidx.lifecycle.runtime.ktx)
    implementation(libs.androidx.activity.compose)
    implementation(platform(libs.androidx.compose.bom))
    implementation(libs.androidx.compose.ui)
    implementation(libs.androidx.compose.ui.graphics)
    implementation(libs.androidx.compose.ui.tooling.preview)
    implementation(libs.androidx.compose.material3)
    testImplementation(libs.junit)
    androidTestImplementation(libs.androidx.junit)
    androidTestImplementation(libs.androidx.espresso.core)
    androidTestImplementation(platform(libs.androidx.compose.bom))
    androidTestImplementation(libs.androidx.compose.ui.test.junit4)
    debugImplementation(libs.androidx.compose.ui.tooling)
    debugImplementation(libs.androidx.compose.ui.test.manifest)
}
"@
}

function New-CMakeLists {
    param(
        [string]$title,
        [string]$tutorial
    )
    $libName = Get-LibName $tutorial
    return @"
cmake_minimum_required(VERSION 3.22.1)

project("$libName")

find_library(log-lib log)
find_library(glesv3-lib GLESv3)

set(LEARN_OPENGL_ROOT_FOLDER "../../../../../..")
set(LEARN_OPENGL_TITLE "$title")
set(LEARN_OPENGL_TUTORIAL "$tutorial")
set(LEARN_OPENGL_PROJECT_FOLDER `${LEARN_OPENGL_ROOT_FOLDER}/src/`${LEARN_OPENGL_TITLE}/`${LEARN_OPENGL_TUTORIAL})

include_directories(
    `${LEARN_OPENGL_ROOT_FOLDER}/includes
)

# Fix for "unknown type name '__NDK_FPABI__'" caused by old khrplatform.h
add_definitions(-D__NDK_FPABI__=)

include_directories(
        `${LEARN_OPENGL_PROJECT_FOLDER}
)

add_library($libName SHARED native-lib.cpp
    `${LEARN_OPENGL_PROJECT_FOLDER}/GLRenderer.cpp
    `${LEARN_OPENGL_PROJECT_FOLDER}/GLRenderer.h
)

target_link_libraries($libName `${log-lib} `${glesv3-lib})
"@
}

function New-NativeLib {
    param(
        [string]$title,
        [string]$tutorial
    )
    $jniPrefix = Get-JniPackage $title $tutorial
    return @"
#include <jni.h>
#include <GLRenderer.h>

static GLRenderer* renderer = nullptr;

extern "C"
JNIEXPORT void JNICALL
${jniPrefix}_onInit(JNIEnv *env, jobject thiz) {
    renderer = new GLRenderer();
}

extern "C"
JNIEXPORT void JNICALL
${jniPrefix}_onSizeChanged(JNIEnv *env, jobject thiz, jint width, jint height) {
    renderer->OnSizeChanged(width, height);
}

extern "C"
JNIEXPORT void JNICALL
${jniPrefix}_onDraw(JNIEnv *env, jobject thiz) {
    renderer->OnDraw();
}

extern "C"
JNIEXPORT void JNICALL
${jniPrefix}_onDestroy(JNIEnv *env, jobject thiz) {
    renderer->OnDestroy();
    delete renderer;
}
"@
}

function New-MainActivity {
    param(
        [string]$title,
        [string]$tutorial
    )
    $pkg = Get-JavaPackage $title $tutorial
    return @"
package $pkg

import android.opengl.GLSurfaceView
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.ui.Modifier
import androidx.compose.ui.viewinterop.AndroidView
import androidx.core.view.WindowCompat
import androidx.core.view.WindowInsetsCompat
import androidx.core.view.WindowInsetsControllerCompat

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        val windowInsetsController = WindowCompat.getInsetsController(window, window.decorView)
        windowInsetsController.hide(WindowInsetsCompat.Type.systemBars())
        windowInsetsController.systemBarsBehavior = WindowInsetsControllerCompat.BEHAVIOR_SHOW_TRANSIENT_BARS_BY_SWIPE

        setContent {
            var renderer: MyGLRenderer? = null
            AndroidView(
                modifier = Modifier.fillMaxSize(),
                factory = { context ->
                    GLSurfaceView(context).apply {
                        setEGLContextClientVersion(3)
                        val myRenderer = MyGLRenderer()
                        renderer = myRenderer
                        setRenderer(myRenderer)
                    }
                },
                onRelease = { glSurfaceView ->
                    glSurfaceView.queueEvent {
                        renderer?.cleanUp()
                    }
                }
            )
        }
    }
}
"@
}

function New-MyGLRenderer {
    param(
        [string]$title,
        [string]$tutorial
    )
    $pkg = Get-JavaPackage $title $tutorial
    $libName = Get-LibName $tutorial
    return @"
package $pkg

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MyGLRenderer : GLSurfaceView.Renderer {

    companion object {
        init {
            System.loadLibrary("$libName")
        }
    }

    private external fun onInit()
    private external fun onSizeChanged(width: Int, height: Int)
    private external fun onDraw()
    private external fun onDestroy()

    fun cleanUp() {
        onDestroy()
    }

    override fun onSurfaceCreated(unused: GL10, config: EGLConfig) {
        onInit()
    }

    override fun onDrawFrame(unused: GL10) {
        onDraw()
    }

    override fun onSurfaceChanged(unused: GL10, width: Int, height: Int) {
        onSizeChanged(width, height)
    }
}
"@
}

function New-AndroidManifest {
    return @"
<?xml version="1.0" encoding="utf-8"?>
<manifest xmlns:android="http://schemas.android.com/apk/res/android">

    <application
        android:allowBackup="true"
        android:icon="@mipmap/ic_launcher"
        android:label="@string/app_name"
        android:roundIcon="@mipmap/ic_launcher_round"
        android:supportsRtl="true"
        android:theme="@style/Theme.LearnOpenGLAndroid">
        <activity
            android:name=".MainActivity"
            android:exported="true">
            <intent-filter>
                <action android:name="android.intent.action.MAIN" />
                <category android:name="android.intent.category.LAUNCHER" />
            </intent-filter>
        </activity>
    </application>

</manifest>
"@
}

function New-StringsXml {
    param([string]$tutorial)
    return @"
<resources>
    <string name="app_name">$tutorial</string>
</resources>
"@
}

function Copy-ResFiles {
    param(
        [string]$srcDir,
        [string]$destDir
    )
    $resSrc = Join-Path $srcDir "src/main/res"
    $resDest = Join-Path $destDir "src/main/res"
    
    if (Test-Path $resSrc) {
        Copy-Item -Path $resSrc -Destination $resDest -Recurse -Force
    }
}

function New-Module {
    param(
        [string]$title,
        [string]$tutorial
    )
    $moduleDir = Join-Path $title $tutorial
    
    if (Test-Path $moduleDir) {
        Write-Host "Module $moduleDir already exists, skipping"
        return
    }
    
    Write-Host "Creating module: $moduleDir"
    
    $cppDir = Join-Path $moduleDir "src/main/cpp"
    $javaBase = Join-Path $moduleDir "src/main/java/com/example/learnopengl"
    
    New-Item -ItemType Directory -Path $cppDir -Force | Out-Null
    New-Item -ItemType Directory -Path $javaBase -Force | Out-Null
    
    # Generate build.gradle.kts
    $buildGradle = New-BuildGradle $title $tutorial
    $buildGradlePath = Join-Path $moduleDir "build.gradle.kts"
    $buildGradle | Out-File $buildGradlePath -Encoding utf8
    
    # Generate CMakeLists.txt
    $cmake = New-CMakeLists $title $tutorial
    $cmakePath = Join-Path $cppDir "CMakeLists.txt"
    $cmake | Out-File $cmakePath -Encoding utf8
    
    # Generate native-lib.cpp
    $nativeLib = New-NativeLib $title $tutorial
    $nativeLibPath = Join-Path $cppDir "native-lib.cpp"
    $nativeLib | Out-File $nativeLibPath -Encoding utf8
    
    # Generate Java package directory
    $pkgTitle = $title.Replace(".", "_").Replace("-", "_")
    $pkgTutorial = $tutorial.Replace(".", "_").Replace("-", "_")
    $pkgDir = Join-Path $javaBase $pkgTitle $pkgTutorial
    New-Item -ItemType Directory -Path $pkgDir -Force | Out-Null
    
    # Generate MainActivity.kt
    $mainActivity = New-MainActivity $title $tutorial
    $mainActivityPath = Join-Path $pkgDir "MainActivity.kt"
    $mainActivity | Out-File $mainActivityPath -Encoding utf8
    
    # Generate MyGLRenderer.kt
    $myGLRenderer = New-MyGLRenderer $title $tutorial
    $myGLRendererPath = Join-Path $pkgDir "MyGLRenderer.kt"
    $myGLRenderer | Out-File $myGLRendererPath -Encoding utf8
    
    # Generate AndroidManifest.xml
    $manifestDir = Join-Path $moduleDir "src/main"
    New-Item -ItemType Directory -Path $manifestDir -Force | Out-Null
    $manifest = New-AndroidManifest
    $manifestPath = Join-Path $manifestDir "AndroidManifest.xml"
    $manifest | Out-File $manifestPath -Encoding utf8
    
    # Generate strings.xml
    $valuesDir = Join-Path $moduleDir "src/main/res/values"
    New-Item -ItemType Directory -Path $valuesDir -Force | Out-Null
    $stringsXml = New-StringsXml $tutorial
    $stringsXmlPath = Join-Path $valuesDir "strings.xml"
    $stringsXml | Out-File $stringsXmlPath -Encoding utf8
    
    # Copy other res files from template
    Copy-ResFiles $templateDir $moduleDir
    
    # Create empty proguard-rules.pro
    $proguardPath = Join-Path $moduleDir "proguard-rules.pro"
    "" | Out-File $proguardPath -Encoding utf8
}

function New-GuestModule {
    param(
        [string[]]$pathParts
    )
    $moduleDir = $pathParts -Join "\"
    $title = ($pathParts[0..($pathParts.Length-2)]) -Join "/"
    $tutorial = $pathParts[-1]
    
    if (Test-Path $moduleDir) {
        Write-Host "Module $moduleDir already exists, skipping"
        return
    }
    
    Write-Host "Creating module: $moduleDir"
    
    $cppDir = Join-Path $moduleDir "src/main/cpp"
    $javaBase = Join-Path $moduleDir "src/main/java/com/example/learnopengl"
    
    New-Item -ItemType Directory -Path $cppDir -Force | Out-Null
    New-Item -ItemType Directory -Path $javaBase -Force | Out-Null
    
    # Generate build.gradle.kts
    $pkgParts = $pathParts | ForEach-Object { $_.Replace(".", "_").Replace("-", "_") }
    $pkg = "com.example.learnopengl.$($pkgParts -Join ".")"
    $buildGradle = @"
plugins {
    alias(libs.plugins.android.application)
    alias(libs.plugins.kotlin.compose)
}

android {
    namespace = "$pkg"
    compileSdk = 36

    defaultConfig {
        applicationId = "$pkg"
        minSdk = 24
        targetSdk = 35
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
        externalNativeBuild {
            cmake {
                cppFlags("")
            }
        }
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_11
        targetCompatibility = JavaVersion.VERSION_11
    }

    buildFeatures {
        compose = true
    }
    externalNativeBuild {
        cmake {
            path = file("src/main/cpp/CMakeLists.txt")
            version = "3.22.1"
        }
    }
}

dependencies {
    implementation(libs.androidx.core.ktx)
    implementation(libs.androidx.lifecycle.runtime.ktx)
    implementation(libs.androidx.activity.compose)
    implementation(platform(libs.androidx.compose.bom))
    implementation(libs.androidx.compose.ui)
    implementation(libs.androidx.compose.ui.graphics)
    implementation(libs.androidx.compose.ui.tooling.preview)
    implementation(libs.androidx.compose.material3)
    testImplementation(libs.junit)
    androidTestImplementation(libs.androidx.junit)
    androidTestImplementation(libs.androidx.espresso.core)
    androidTestImplementation(platform(libs.androidx.compose.bom))
    androidTestImplementation(libs.androidx.compose.ui.test.junit4)
    debugImplementation(libs.androidx.compose.ui.tooling)
    debugImplementation(libs.androidx.compose.ui.test.manifest)
}
"@
    $buildGradlePath = Join-Path $moduleDir "build.gradle.kts"
    $buildGradle | Out-File $buildGradlePath -Encoding utf8
    
    # Generate CMakeLists.txt
    $libName = $pkgParts -Join "_"
    $cmake = @"
cmake_minimum_required(VERSION 3.22.1)

project("$libName")

find_library(log-lib log)
find_library(glesv3-lib GLESv3)

set(LEARN_OPENGL_ROOT_FOLDER "../../../../../..")
set(LEARN_OPENGL_TITLE "$title")
set(LEARN_OPENGL_TUTORIAL "$tutorial")
set(LEARN_OPENGL_PROJECT_FOLDER `${LEARN_OPENGL_ROOT_FOLDER}/src/`${LEARN_OPENGL_TITLE}/`${LEARN_OPENGL_TUTORIAL})

include_directories(
    `${LEARN_OPENGL_ROOT_FOLDER}/includes
)

# Fix for "unknown type name '__NDK_FPABI__'" caused by old khrplatform.h
add_definitions(-D__NDK_FPABI__=)

include_directories(
        `${LEARN_OPENGL_PROJECT_FOLDER}
)

add_library($libName SHARED native-lib.cpp
    `${LEARN_OPENGL_PROJECT_FOLDER}/GLRenderer.cpp
    `${LEARN_OPENGL_PROJECT_FOLDER}/GLRenderer.h
)

target_link_libraries($libName `${log-lib} `${glesv3-lib})
"@
    $cmakePath = Join-Path $cppDir "CMakeLists.txt"
    $cmake | Out-File $cmakePath -Encoding utf8
    
    # Generate native-lib.cpp
    $jniParts = $pathParts | ForEach-Object { $_.Replace(".", "_1").Replace("-", "_1") }
    $jniPrefix = "Java_com_example_learnopengl_$($jniParts -Join "_")_MyGLRenderer"
    $nativeLib = @"
#include <jni.h>
#include <GLRenderer.h>

static GLRenderer* renderer = nullptr;

extern "C"
JNIEXPORT void JNICALL
${jniPrefix}_onInit(JNIEnv *env, jobject thiz) {
    renderer = new GLRenderer();
}

extern "C"
JNIEXPORT void JNICALL
${jniPrefix}_onSizeChanged(JNIEnv *env, jobject thiz, jint width, jint height) {
    renderer->OnSizeChanged(width, height);
}

extern "C"
JNIEXPORT void JNICALL
${jniPrefix}_onDraw(JNIEnv *env, jobject thiz) {
    renderer->OnDraw();
}

extern "C"
JNIEXPORT void JNICALL
${jniPrefix}_onDestroy(JNIEnv *env, jobject thiz) {
    renderer->OnDestroy();
    delete renderer;
}
"@
    $nativeLibPath = Join-Path $cppDir "native-lib.cpp"
    $nativeLib | Out-File $nativeLibPath -Encoding utf8
    
    # Generate Java package directory
    $javaPkgDir = Join-Path $javaBase ($pkgParts -Join "\")
    New-Item -ItemType Directory -Path $javaPkgDir -Force | Out-Null
    
    # Generate MainActivity.kt
    $mainActivity = @"
package $pkg

import android.opengl.GLSurfaceView
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.ui.Modifier
import androidx.compose.ui.viewinterop.AndroidView
import androidx.core.view.WindowCompat
import androidx.core.view.WindowInsetsCompat
import androidx.core.view.WindowInsetsControllerCompat

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        val windowInsetsController = WindowCompat.getInsetsController(window, window.decorView)
        windowInsetsController.hide(WindowInsetsCompat.Type.systemBars())
        windowInsetsController.systemBarsBehavior = WindowInsetsControllerCompat.BEHAVIOR_SHOW_TRANSIENT_BARS_BY_SWIPE

        setContent {
            var renderer: MyGLRenderer? = null
            AndroidView(
                modifier = Modifier.fillMaxSize(),
                factory = { context ->
                    GLSurfaceView(context).apply {
                        setEGLContextClientVersion(3)
                        val myRenderer = MyGLRenderer()
                        renderer = myRenderer
                        setRenderer(myRenderer)
                    }
                },
                onRelease = { glSurfaceView ->
                    glSurfaceView.queueEvent {
                        renderer?.cleanUp()
                    }
                }
            )
        }
    }
}
"@
    $mainActivityPath = Join-Path $javaPkgDir "MainActivity.kt"
    $mainActivity | Out-File $mainActivityPath -Encoding utf8
    
    # Generate MyGLRenderer.kt
    $myGLRenderer = @"
package $pkg

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MyGLRenderer : GLSurfaceView.Renderer {

    companion object {
        init {
            System.loadLibrary("$libName")
        }
    }

    private external fun onInit()
    private external fun onSizeChanged(width: Int, height: Int)
    private external fun onDraw()
    private external fun onDestroy()

    fun cleanUp() {
        onDestroy()
    }

    override fun onSurfaceCreated(unused: GL10, config: EGLConfig) {
        onInit()
    }

    override fun onDrawFrame(unused: GL10) {
        onDraw()
    }

    override fun onSurfaceChanged(unused: GL10, width: Int, height: Int) {
        onSizeChanged(width, height)
    }
}
"@
    $myGLRendererPath = Join-Path $javaPkgDir "MyGLRenderer.kt"
    $myGLRenderer | Out-File $myGLRendererPath -Encoding utf8
    
    # Generate AndroidManifest.xml
    $manifestDir = Join-Path $moduleDir "src/main"
    New-Item -ItemType Directory -Path $manifestDir -Force | Out-Null
    $manifest = New-AndroidManifest
    $manifestPath = Join-Path $manifestDir "AndroidManifest.xml"
    $manifest | Out-File $manifestPath -Encoding utf8
    
    # Generate strings.xml
    $valuesDir = Join-Path $moduleDir "src/main/res/values"
    New-Item -ItemType Directory -Path $valuesDir -Force | Out-Null
    $stringsXml = New-StringsXml $tutorial
    $stringsXmlPath = Join-Path $valuesDir "strings.xml"
    $stringsXml | Out-File $stringsXmlPath -Encoding utf8
    
    # Copy other res files from template
    Copy-ResFiles $templateDir $moduleDir
    
    # Create empty proguard-rules.pro
    $proguardPath = Join-Path $moduleDir "proguard-rules.pro"
    "" | Out-File $proguardPath -Encoding utf8
}

function Update-SettingsGradle {
    $settingsPath = "settings.gradle.kts"
    
    $lines = Get-Content $settingsPath -Raw
    $lines = $lines -split "`n"
    $newLines = $lines[0..22]
    
    $newLines += ""
    $newLines += "// 1. getting_started"
    $MODULES["1.getting_started"] | ForEach-Object {
        $newLines += "include(`":1.getting_started:$_`")"
    }
    
    $newLines += ""
    $newLines += "// 2. lighting"
    $MODULES["2.lighting"] | ForEach-Object {
        $newLines += "include(`":2.lighting:$_`")"
    }
    
    $newLines += ""
    $newLines += "// 3. model_loading"
    $MODULES["3.model_loading"] | ForEach-Object {
        $newLines += "include(`":3.model_loading:$_`")"
    }
    
    $newLines += ""
    $newLines += "// 4. advanced_opengl"
    $MODULES["4.advanced_opengl"] | ForEach-Object {
        $newLines += "include(`":4.advanced_opengl:$_`")"
    }
    
    $newLines += ""
    $newLines += "// 5. advanced_lighting"
    $MODULES["5.advanced_lighting"] | ForEach-Object {
        $newLines += "include(`":5.advanced_lighting:$_`")"
    }
    
    $newLines += ""
    $newLines += "// 6. pbr"
    $MODULES["6.pbr"] | ForEach-Object {
        $newLines += "include(`":6.pbr:$_`")"
    }
    
    $newLines += ""
    $newLines += "// 7. in_practice"
    $MODULES["7.in_practice"] | ForEach-Object {
        $newLines += "include(`":7.in_practice:$_`")"
    }
    
    $newLines += ""
    $newLines += "// GUEST_ARTICLES"
    $GUEST_ARTICLES | ForEach-Object {
        $path = ":" + ($_ -Join ":")
        $newLines += "include(`"$path`")"
    }
    
    $newLines -Join "`n" | Out-File $settingsPath -Encoding utf8 -NoNewline
}

# Main execution
foreach ($title in $MODULES.Keys) {
    foreach ($tutorial in $MODULES[$title]) {
        New-Module $title $tutorial
    }
}

foreach ($pathParts in $GUEST_ARTICLES) {
    New-GuestModule $pathParts
}

Update-SettingsGradle

Write-Host ""
Write-Host "All modules created successfully!"
