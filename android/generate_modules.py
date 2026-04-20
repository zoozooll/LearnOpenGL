import os
import shutil

# Define all modules
MODULES = {
    "1.getting_started": [
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
        "7.4.camera_class",
    ],
    "2.lighting": [
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
        "6.multiple_lights",
    ],
    "3.model_loading": [
        "1.model_loading",
    ],
    "4.advanced_opengl": [
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
        "11.2.anti_aliasing_offscreen",
    ],
    "5.advanced_lighting": [
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
        "9.ssao",
    ],
    "6.pbr": [
        "1.1.lighting",
        "1.2.lighting_textured",
        "2.1.1.ibl_irradiance_conversion",
        "2.1.2.ibl_irradiance",
        "2.2.1.ibl_specular",
        "2.2.2.ibl_specular_textured",
    ],
    "7.in_practice": [
        "1.debugging",
        "2.text_rendering",
    ],
}

GUEST_ARTICLES = [
    ("8.guest", "2020", "oit"),
    ("8.guest", "2020", "skeletal_animation"),
    ("8.guest", "2021", "1.scene", "1.scene_graph"),
    ("8.guest", "2021", "1.scene", "2.frustum_culling"),
    ("8.guest", "2021", "2.csm"),
    ("8.guest", "2021", "3.tessellation", "terrain_gpu_dist"),
    ("8.guest", "2021", "3.tessellation", "terrain_cpu_src"),
    ("8.guest", "2021", "4.dsa"),
    ("8.guest", "2022", "5.computeshader_helloworld"),
    ("8.guest", "2022", "6.physically_based_bloom"),
    ("8.guest", "2022", "7.area_lights", "1.area_light"),
    ("8.guest", "2022", "7.area_lights", "2.multiple_area_lights"),
]

TEMPLATE_DIR = "1.getting_started/1.1.hello_window"

def get_java_package(title, tutorial):
    """Convert title and tutorial to Java package name."""
    pkg_title = title.replace(".", "_").replace("-", "_")
    pkg_tutorial = tutorial.replace(".", "_").replace("-", "_")
    return f"com.example.learnopengl.{pkg_title}.{pkg_tutorial}"

def get_jni_package(title, tutorial):
    """Convert title and tutorial to JNI function prefix."""
    pkg_title = title.replace(".", "_1").replace("-", "_1")
    pkg_tutorial = tutorial.replace(".", "_1").replace("-", "_1")
    return f"Java_com_example_learnopengl_{pkg_title}_{pkg_tutorial}_MyGLRenderer"

def generate_build_gradle(title, tutorial):
    pkg = get_java_package(title, tutorial)
    app_id = pkg
    return f'''plugins {{
    alias(libs.plugins.android.application)
    alias(libs.plugins.kotlin.compose)
}}

android {{
    namespace = "{pkg}"
    compileSdk = 36

    defaultConfig {{
        applicationId = "{app_id}"
        minSdk = 24
        targetSdk = 35
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
        externalNativeBuild {{
            cmake {{
                cppFlags("")
            }}
        }}
    }}

    buildTypes {{
        release {{
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }}
    }}
    compileOptions {{
        sourceCompatibility = JavaVersion.VERSION_11
        targetCompatibility = JavaVersion.VERSION_11
    }}

    buildFeatures {{
        compose = true
    }}
    externalNativeBuild {{
        cmake {{
            path = file("src/main/cpp/CMakeLists.txt")
            version = "3.22.1"
        }}
    }}
}}

dependencies {{
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
}}
'''

def generate_cmake(title, tutorial):
    lib_name = tutorial.replace(".", "_").replace("-", "_")
    return f'''cmake_minimum_required(VERSION 3.22.1)

project("{lib_name}")

find_library(log-lib log)
find_library(glesv3-lib GLESv3)

set(LEARN_OPENGL_ROOT_FOLDER "../../../../../..")
set(LEARN_OPENGL_TITLE "{title}")
set(LEARN_OPENGL_TUTORIAL "{tutorial}")
set(LEARN_OPENGL_PROJECT_FOLDER ${LEARN_OPENGL_ROOT_FOLDER}/src/${LEARN_OPENGL_TITLE}/${LEARN_OPENGL_TUTORIAL})

include_directories(
    ${LEARN_OPENGL_ROOT_FOLDER}/includes
)

# Fix for "unknown type name '__NDK_FPABI__'" caused by old khrplatform.h
add_definitions(-D__NDK_FPABI__=)

include_directories(
        ${LEARN_OPENGL_PROJECT_FOLDER}
)

add_library({lib_name} SHARED native-lib.cpp
    ${LEARN_OPENGL_PROJECT_FOLDER}/GLRenderer.cpp
    ${LEARN_OPENGL_PROJECT_FOLDER}/GLRenderer.h
)

target_link_libraries({lib_name} ${log-lib} ${glesv3-lib})
'''

def generate_native_lib(title, tutorial):
    jni_prefix = get_jni_package(title, tutorial)
    return f'''#include <jni.h>
#include <GLRenderer.h>

static GLRenderer* renderer = nullptr;

extern "C"
JNIEXPORT void JNICALL
{jni_prefix}_onInit(JNIEnv *env, jobject thiz) {{
    renderer = new GLRenderer();
}}

extern "C"
JNIEXPORT void JNICALL
{jni_prefix}_onSizeChanged(JNIEnv *env, jobject thiz, jint width, jint height) {{
    renderer->OnSizeChanged(width, height);
}}

extern "C"
JNIEXPORT void JNICALL
{jni_prefix}_onDraw(JNIEnv *env, jobject thiz) {{
    renderer->OnDraw();
}}

extern "C"
JNIEXPORT void JNICALL
{jni_prefix}_onDestroy(JNIEnv *env, jobject thiz) {{
    renderer->OnDestroy();
    delete renderer;
}}
'''

def generate_main_activity(title, tutorial):
    pkg = get_java_package(title, tutorial)
    return f'''package {pkg}

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

class MainActivity : ComponentActivity() {{
    override fun onCreate(savedInstanceState: Bundle?) {{
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        val windowInsetsController = WindowCompat.getInsetsController(window, window.decorView)
        windowInsetsController.hide(WindowInsetsCompat.Type.systemBars())
        windowInsetsController.systemBarsBehavior = WindowInsetsControllerCompat.BEHAVIOR_SHOW_TRANSIENT_BARS_BY_SWIPE

        setContent {{
            var renderer: MyGLRenderer? = null
            AndroidView(
                modifier = Modifier.fillMaxSize(),
                factory = {{ context ->
                    GLSurfaceView(context).apply {{
                        setEGLContextClientVersion(3)
                        val myRenderer = MyGLRenderer()
                        renderer = myRenderer
                        setRenderer(myRenderer)
                    }}
                }},
                onRelease = {{ glSurfaceView ->
                    glSurfaceView.queueEvent {{
                        renderer?.cleanUp()
                    }}
                }}
            )
        }}
    }}
}}
'''

def generate_my_gl_renderer(title, tutorial):
    pkg = get_java_package(title, tutorial)
    lib_name = tutorial.replace(".", "_").replace("-", "_")
    return f'''package {pkg}

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MyGLRenderer : GLSurfaceView.Renderer {{

    companion object {{
        init {{
            System.loadLibrary("{lib_name}")
        }}
    }}

    private external fun onInit()
    private external fun onSizeChanged(width: Int, height: Int)
    private external fun onDraw()
    private external fun onDestroy()

    fun cleanUp() {{
        onDestroy()
    }}

    override fun onSurfaceCreated(unused: GL10, config: EGLConfig) {{
        onInit()
    }}

    override fun onDrawFrame(unused: GL10) {{
        onDraw()
    }}

    override fun onSurfaceChanged(unused: GL10, width: Int, height: Int) {{
        onSizeChanged(width, height)
    }}
}}
'''

def generate_android_manifest():
    return '''<?xml version="1.0" encoding="utf-8"?>
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
'''

def generate_strings(tutorial):
    return f'''<resources>
    <string name="app_name">{tutorial}</string>
</resources>
'''

def copy_res_files(src_dir, dest_dir):
    """Copy resource files from template to new module."""
    res_src = os.path.join(src_dir, "src", "main", "res")
    res_dest = os.path.join(dest_dir, "src", "main", "res")
    
    if os.path.exists(res_src):
        shutil.copytree(res_src, res_dest, dirs_exist_ok=True)

def create_module(title, tutorial):
    """Create a single module."""
    module_dir = os.path.join(title, tutorial)
    
    if os.path.exists(module_dir):
        print(f"Module {module_dir} already exists, skipping")
        return
    
    print(f"Creating module: {module_dir}")
    
    # Create directory structure
    cpp_dir = os.path.join(module_dir, "src", "main", "cpp")
    java_dir = os.path.join(module_dir, "src", "main", "java", "com", "example", "learnopengl")
    
    os.makedirs(cpp_dir, exist_ok=True)
    os.makedirs(java_dir, exist_ok=True)
    
    # Generate build.gradle.kts
    with open(os.path.join(module_dir, "build.gradle.kts"), "w") as f:
        f.write(generate_build_gradle(title, tutorial))
    
    # Generate CMakeLists.txt
    with open(os.path.join(cpp_dir, "CMakeLists.txt"), "w") as f:
        f.write(generate_cmake(title, tutorial))
    
    # Generate native-lib.cpp
    with open(os.path.join(cpp_dir, "native-lib.cpp"), "w") as f:
        f.write(generate_native_lib(title, tutorial))
    
    # Generate Java package directory
    pkg_title = title.replace(".", "_").replace("-", "_")
    pkg_tutorial = tutorial.replace(".", "_").replace("-", "_")
    pkg_dir = os.path.join(java_dir, pkg_title, pkg_tutorial)
    os.makedirs(pkg_dir, exist_ok=True)
    
    # Generate MainActivity.kt
    with open(os.path.join(pkg_dir, "MainActivity.kt"), "w") as f:
        f.write(generate_main_activity(title, tutorial))
    
    # Generate MyGLRenderer.kt
    with open(os.path.join(pkg_dir, "MyGLRenderer.kt"), "w") as f:
        f.write(generate_my_gl_renderer(title, tutorial))
    
    # Generate AndroidManifest.xml
    manifest_dir = os.path.join(module_dir, "src", "main")
    os.makedirs(manifest_dir, exist_ok=True)
    with open(os.path.join(manifest_dir, "AndroidManifest.xml"), "w") as f:
        f.write(generate_android_manifest())
    
    # Generate strings.xml
    values_dir = os.path.join(module_dir, "src", "main", "res", "values")
    os.makedirs(values_dir, exist_ok=True)
    with open(os.path.join(values_dir, "strings.xml"), "w") as f:
        f.write(generate_strings(tutorial))
    
    # Copy other res files from template
    copy_res_files(TEMPLATE_DIR, module_dir)
    
    # Create empty proguard-rules.pro
    with open(os.path.join(module_dir, "proguard-rules.pro"), "w") as f:
        f.write("")

def create_guest_module(path_parts):
    """Create a guest article module."""
    module_dir = os.path.join(*path_parts)
    title = "/".join(path_parts[:-1])
    tutorial = path_parts[-1]
    
    if os.path.exists(module_dir):
        print(f"Module {module_dir} already exists, skipping")
        return
    
    print(f"Creating module: {module_dir}")
    
    # Create directory structure
    cpp_dir = os.path.join(module_dir, "src", "main", "cpp")
    java_base = os.path.join(module_dir, "src", "main", "java", "com", "example", "learnopengl")
    
    os.makedirs(cpp_dir, exist_ok=True)
    os.makedirs(java_base, exist_ok=True)
    
    # Generate build.gradle.kts
    pkg_parts = [p.replace(".", "_").replace("-", "_") for p in path_parts]
    pkg = "com.example.learnopengl." + ".".join(pkg_parts)
    app_id = pkg
    
    build_gradle = f'''plugins {{
    alias(libs.plugins.android.application)
    alias(libs.plugins.kotlin.compose)
}}

android {{
    namespace = "{pkg}"
    compileSdk = 36

    defaultConfig {{
        applicationId = "{app_id}"
        minSdk = 24
        targetSdk = 35
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
        externalNativeBuild {{
            cmake {{
                cppFlags("")
            }}
        }}
    }}

    buildTypes {{
        release {{
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }}
    }}
    compileOptions {{
        sourceCompatibility = JavaVersion.VERSION_11
        targetCompatibility = JavaVersion.VERSION_11
    }}

    buildFeatures {{
        compose = true
    }}
    externalNativeBuild {{
        cmake {{
            path = file("src/main/cpp/CMakeLists.txt")
            version = "3.22.1"
        }}
    }}
}}

dependencies {{
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
}}
'''
    
    with open(os.path.join(module_dir, "build.gradle.kts"), "w") as f:
        f.write(build_gradle)
    
    # Generate CMakeLists.txt
    lib_name = "_".join(pkg_parts)
    cmake = f'''cmake_minimum_required(VERSION 3.22.1)

project("{lib_name}")

find_library(log-lib log)
find_library(glesv3-lib GLESv3)

set(LEARN_OPENGL_ROOT_FOLDER "../../../../../..")
set(LEARN_OPENGL_TITLE "{title}")
set(LEARN_OPENGL_TUTORIAL "{tutorial}")
set(LEARN_OPENGL_PROJECT_FOLDER ${LEARN_OPENGL_ROOT_FOLDER}/src/${LEARN_OPENGL_TITLE}/${LEARN_OPENGL_TUTORIAL})

include_directories(
    ${LEARN_OPENGL_ROOT_FOLDER}/includes
)

# Fix for "unknown type name '__NDK_FPABI__'" caused by old khrplatform.h
add_definitions(-D__NDK_FPABI__=)

include_directories(
        ${LEARN_OPENGL_PROJECT_FOLDER}
)

add_library({lib_name} SHARED native-lib.cpp
    ${LEARN_OPENGL_PROJECT_FOLDER}/GLRenderer.cpp
    ${LEARN_OPENGL_PROJECT_FOLDER}/GLRenderer.h
)

target_link_libraries({lib_name} ${log-lib} ${glesv3-lib})
'''
    
    with open(os.path.join(cpp_dir, "CMakeLists.txt"), "w") as f:
        f.write(cmake)
    
    # Generate native-lib.cpp
    jni_parts = [p.replace(".", "_1").replace("-", "_1") for p in path_parts]
    jni_prefix = "Java_com_example_learnopengl_" + "_".join(jni_parts) + "_MyGLRenderer"
    
    native_lib = f'''#include <jni.h>
#include <GLRenderer.h>

static GLRenderer* renderer = nullptr;

extern "C"
JNIEXPORT void JNICALL
{jni_prefix}_onInit(JNIEnv *env, jobject thiz) {{
    renderer = new GLRenderer();
}}

extern "C"
JNIEXPORT void JNICALL
{jni_prefix}_onSizeChanged(JNIEnv *env, jobject thiz, jint width, jint height) {{
    renderer->OnSizeChanged(width, height);
}}

extern "C"
JNIEXPORT void JNICALL
{jni_prefix}_onDraw(JNIEnv *env, jobject thiz) {{
    renderer->OnDraw();
}}

extern "C"
JNIEXPORT void JNICALL
{jni_prefix}_onDestroy(JNIEnv *env, jobject thiz) {{
    renderer->OnDestroy();
    delete renderer;
}}
'''
    
    with open(os.path.join(cpp_dir, "native-lib.cpp"), "w") as f:
        f.write(native_lib)
    
    # Generate Java package directory
    java_pkg_dir = os.path.join(java_base, *pkg_parts)
    os.makedirs(java_pkg_dir, exist_ok=True)
    
    # Generate MainActivity.kt
    main_activity = f'''package {pkg}

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

class MainActivity : ComponentActivity() {{
    override fun onCreate(savedInstanceState: Bundle?) {{
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        val windowInsetsController = WindowCompat.getInsetsController(window, window.decorView)
        windowInsetsController.hide(WindowInsetsCompat.Type.systemBars())
        windowInsetsController.systemBarsBehavior = WindowInsetsControllerCompat.BEHAVIOR_SHOW_TRANSIENT_BARS_BY_SWIPE

        setContent {{
            var renderer: MyGLRenderer? = null
            AndroidView(
                modifier = Modifier.fillMaxSize(),
                factory = {{ context ->
                    GLSurfaceView(context).apply {{
                        setEGLContextClientVersion(3)
                        val myRenderer = MyGLRenderer()
                        renderer = myRenderer
                        setRenderer(myRenderer)
                    }}
                }},
                onRelease = {{ glSurfaceView ->
                    glSurfaceView.queueEvent {{
                        renderer?.cleanUp()
                    }}
                }}
            )
        }}
    }}
}}
'''
    
    with open(os.path.join(java_pkg_dir, "MainActivity.kt"), "w") as f:
        f.write(main_activity)
    
    # Generate MyGLRenderer.kt
    my_gl_renderer = f'''package {pkg}

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MyGLRenderer : GLSurfaceView.Renderer {{

    companion object {{
        init {{
            System.loadLibrary("{lib_name}")
        }}
    }}

    private external fun onInit()
    private external fun onSizeChanged(width: Int, height: Int)
    private external fun onDraw()
    private external fun onDestroy()

    fun cleanUp() {{
        onDestroy()
    }}

    override fun onSurfaceCreated(unused: GL10, config: EGLConfig) {{
        onInit()
    }}

    override fun onDrawFrame(unused: GL10) {{
        onDraw()
    }}

    override fun onSurfaceChanged(unused: GL10, width: Int, height: Int) {{
        onSizeChanged(width, height)
    }}
}}
'''
    
    with open(os.path.join(java_pkg_dir, "MyGLRenderer.kt"), "w") as f:
        f.write(my_gl_renderer)
    
    # Generate AndroidManifest.xml
    manifest_dir = os.path.join(module_dir, "src", "main")
    os.makedirs(manifest_dir, exist_ok=True)
    with open(os.path.join(manifest_dir, "AndroidManifest.xml"), "w") as f:
        f.write(generate_android_manifest())
    
    # Generate strings.xml
    values_dir = os.path.join(module_dir, "src", "main", "res", "values")
    os.makedirs(values_dir, exist_ok=True)
    with open(os.path.join(values_dir, "strings.xml"), "w") as f:
        f.write(generate_strings(tutorial))
    
    # Copy other res files from template
    copy_res_files(TEMPLATE_DIR, module_dir)
    
    # Create empty proguard-rules.pro
    with open(os.path.join(module_dir, "proguard-rules.pro"), "w") as f:
        f.write("")

def update_settings_gradle():
    """Update settings.gradle.kts to include all modules."""
    settings_path = "settings.gradle.kts"
    
    with open(settings_path, "r") as f:
        content = f.read()
    
    # Remove all include statements after line 23
    lines = content.split("\n")
    new_lines = lines[:23]
    
    # Add all modules
    new_lines.append("")
    new_lines.append("// 1. getting_started")
    for tutorial in MODULES["1.getting_started"]:
        new_lines.append(f'include(":1.getting_started:{tutorial}")')
    
    new_lines.append("")
    new_lines.append("// 2. lighting")
    for tutorial in MODULES["2.lighting"]:
        new_lines.append(f'include(":2.lighting:{tutorial}")')
    
    new_lines.append("")
    new_lines.append("// 3. model_loading")
    for tutorial in MODULES["3.model_loading"]:
        new_lines.append(f'include(":3.model_loading:{tutorial}")')
    
    new_lines.append("")
    new_lines.append("// 4. advanced_opengl")
    for tutorial in MODULES["4.advanced_opengl"]:
        new_lines.append(f'include(":4.advanced_opengl:{tutorial}")')
    
    new_lines.append("")
    new_lines.append("// 5. advanced_lighting")
    for tutorial in MODULES["5.advanced_lighting"]:
        new_lines.append(f'include(":5.advanced_lighting:{tutorial}")')
    
    new_lines.append("")
    new_lines.append("// 6. pbr")
    for tutorial in MODULES["6.pbr"]:
        new_lines.append(f'include(":6.pbr:{tutorial}")')
    
    new_lines.append("")
    new_lines.append("// 7. in_practice")
    for tutorial in MODULES["7.in_practice"]:
        new_lines.append(f'include(":7.in_practice:{tutorial}")')
    
    new_lines.append("")
    new_lines.append("// GUEST_ARTICLES")
    for parts in GUEST_ARTICLES:
        path = ":".join(parts)
        new_lines.append(f'include(":8.guest:{path}")')
    
    with open(settings_path, "w") as f:
        f.write("\n".join(new_lines))

def main():
    # Create regular modules
    for title, tutorials in MODULES.items():
        for tutorial in tutorials:
            create_module(title, tutorial)
    
    # Create guest articles modules
    for path_parts in GUEST_ARTICLES:
        create_guest_module(path_parts)
    
    # Update settings.gradle.kts
    update_settings_gradle()
    
    print("\nAll modules created successfully!")

if __name__ == "__main__":
    main()
