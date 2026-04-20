import os
import shutil
import re

source_path = r"g:\Workspaces\cpp\LearnOpenGL\android\1.getting_started\1.1.hello_window"
log_path = r"g:\Workspaces\cpp\LearnOpenGL\android\copy_log.txt"

modules = [
    # 1.getting_started
    ":1.getting_started:1.2.hello_window_clear",
    ":1.getting_started:2.1.hello_triangle",
    ":1.getting_started:2.2.hello_triangle_indexed",
    ":1.getting_started:2.3.hello_triangle_exercise1",
    ":1.getting_started:2.4.hello_triangle_exercise2",
    ":1.getting_started:2.5.hello_triangle_exercise3",
    ":1.getting_started:3.1.shaders_uniform",
    ":1.getting_started:3.2.shaders_interpolation",
    ":1.getting_started:3.3.shaders_class",
    ":1.getting_started:4.1.textures",
    ":1.getting_started:4.2.textures_combined",
    ":1.getting_started:4.4.textures_exercise2",
    ":1.getting_started:4.5.textures_exercise3",
    ":1.getting_started:4.6.textures_exercise4",
    ":1.getting_started:5.1.transformations",
    ":1.getting_started:5.2.transformations_exercise2",
    ":1.getting_started:6.1.coordinate_systems",
    ":1.getting_started:6.2.coordinate_systems_depth",
    ":1.getting_started:6.3.coordinate_systems_multiple",
    ":1.getting_started:7.1.camera_circle",
    ":1.getting_started:7.2.camera_keyboard_dt",
    ":1.getting_started:7.3.camera_mouse_zoom",
    ":1.getting_started:7.4.camera_class",
    
    # 2.lighting
    ":2.lighting:1.colors",
    ":2.lighting:2.1.basic_lighting_diffuse",
    ":2.lighting:2.2.basic_lighting_specular",
    ":2.lighting:3.1.materials",
    ":2.lighting:3.2.materials_exercise1",
    ":2.lighting:4.1.lighting_maps_diffuse_map",
    ":2.lighting:4.2.lighting_maps_specular_map",
    ":2.lighting:4.4.lighting_maps_exercise4",
    ":2.lighting:5.1.light_casters_directional",
    ":2.lighting:5.2.light_casters_point",
    ":2.lighting:5.3.light_casters_spot",
    ":2.lighting:5.4.light_casters_spot_soft",
    ":2.lighting:6.multiple_lights",
    
    # 3.model_loading
    ":3.model_loading:1.model_loading",
    
    # 4.advanced_opengl
    ":4.advanced_opengl:1.1.depth_testing",
    ":4.advanced_opengl:1.2.depth_testing_view",
    ":4.advanced_opengl:2.stencil_testing",
    ":4.advanced_opengl:3.1.blending_discard",
    ":4.advanced_opengl:3.2.blending_sort",
    ":4.advanced_opengl:5.1.framebuffers",
    ":4.advanced_opengl:5.2.framebuffers_exercise1",
    ":4.advanced_opengl:6.1.cubemaps_skybox",
    ":4.advanced_opengl:6.2.cubemaps_environment_mapping",
    ":4.advanced_opengl:8.advanced_glsl_ubo",
    ":4.advanced_opengl:9.1.geometry_shader_houses",
    ":4.advanced_opengl:9.2.geometry_shader_exploding",
    ":4.advanced_opengl:9.3.geometry_shader_normals",
    ":4.advanced_opengl:10.1.instancing_quads",
    ":4.advanced_opengl:10.2.asteroids",
    ":4.advanced_opengl:10.3.asteroids_instanced",
    ":4.advanced_opengl:11.1.anti_aliasing_msaa",
    ":4.advanced_opengl:11.2.anti_aliasing_offscreen",
    
    # 5.advanced_lighting
    ":5.advanced_lighting:1.advanced_lighting",
    ":5.advanced_lighting:2.gamma_correction",
    ":5.advanced_lighting:3.1.1.shadow_mapping_depth",
    ":5.advanced_lighting:3.1.2.shadow_mapping_base",
    ":5.advanced_lighting:3.1.3.shadow_mapping",
    ":5.advanced_lighting:3.2.1.point_shadows",
    ":5.advanced_lighting:3.2.2.point_shadows_soft",
    ":5.advanced_lighting:4.normal_mapping",
    ":5.advanced_lighting:5.1.parallax_mapping",
    ":5.advanced_lighting:5.2.steep_parallax_mapping",
    ":5.advanced_lighting:5.3.parallax_occlusion_mapping",
    ":5.advanced_lighting:6.hdr",
    ":5.advanced_lighting:7.bloom",
    ":5.advanced_lighting:8.1.deferred_shading",
    ":5.advanced_lighting:8.2.deferred_shading_volumes",
    ":5.advanced_lighting:9.ssao",
    
    # 6.pbr
    ":6.pbr:1.1.lighting",
    ":6.pbr:1.2.lighting_textured",
    ":6.pbr:2.1.1.ibl_irradiance_conversion",
    ":6.pbr:2.1.2.ibl_irradiance",
    ":6.pbr:2.2.1.ibl_specular",
    ":6.pbr:2.2.2.ibl_specular_textured",
    
    # 7.in_practice
    ":7.in_practice:1.debugging",
    ":7.in_practice:2.text_rendering",
    
    # 8.guest
    ":8.guest:2020:oit",
    ":8.guest:2020:skeletal_animation",
    ":8.guest:2021:1.scene:1.scene_graph",
    ":8.guest:2021:1.scene:2.frustum_culling",
    ":8.guest:2021:2.csm",
    ":8.guest:2021:3.tessellation:terrain_gpu_dist",
    ":8.guest:2021:3.tessellation:terrain_cpu_src",
    ":8.guest:2021:4.dsa",
    ":8.guest:2022:5.computeshader_helloworld",
    ":8.guest:2022:6.physically_based_bloom",
    ":8.guest:2022:7.area_lights:1.area_light",
    ":8.guest:2022:7.area_lights:2.multiple_area_lights"
]

def clean_name(s):
    result = re.sub(r'\d+\.', '', s)
    result = result.lstrip('.')
    result = result.rstrip('.')
    return result

def clean_package_name(s):
    result = clean_name(s)
    result = result.replace(':', '_')
    return result

def clean_path_name(s):
    result = s.replace(':', '_')
    return result

def log(message):
    print(message)
    with open(log_path, 'a', encoding='utf-8') as f:
        f.write(message + '\n')

# Clear log file
if os.path.exists(log_path):
    os.remove(log_path)

log("Starting script...")
log(f"Source path: {source_path}")
log(f"Source path exists: {os.path.exists(source_path)}")
log(f"Modules count: {len(modules)}")

# Get items to copy (excluding build directories)
items_to_copy = []
if os.path.exists(source_path):
    for item in os.listdir(source_path):
        if item not in ['.cxx', 'build', '.gradle']:
            items_to_copy.append(item)
    log(f"Items to copy: {items_to_copy}")

for idx, module in enumerate(modules, 1):
    log(f"\nProcessing module {idx}/{len(modules)}: {module}")
    
    try:
        module_trimmed = module.lstrip(':')
        last_colon_index = module_trimmed.rfind(':')
        title_name = module_trimmed[:last_colon_index]
        tutorial_name = module_trimmed[last_colon_index+1:]
        
        title_name_clean = clean_package_name(title_name)
        tutorial_name_clean = clean_name(tutorial_name)
        
        # Clean title name for path (replace colons)
        title_name_path = clean_path_name(title_name)
        
        target_path = os.path.join(r"g:\Workspaces\cpp\LearnOpenGL\android", title_name_path, tutorial_name)
        
        log(f"  Target: {target_path}")
        log(f"  ApplicationId: com.example.learnopengl.{title_name_clean}.{tutorial_name_clean}")
        
        # Create directory if it doesn't exist
        if not os.path.exists(target_path):
            os.makedirs(target_path, exist_ok=True)
            log("  Created directory")
        
        # Copy files
        log("  Starting copy...")
        for item in items_to_copy:
            s = os.path.join(source_path, item)
            d = os.path.join(target_path, item)
            log(f"    Copying: {item}")
            if os.path.isdir(s):
                if os.path.exists(d):
                    shutil.rmtree(d)
                shutil.copytree(s, d)
                log(f"    Copied dir: {item}")
            else:
                if os.path.exists(d):
                    os.remove(d)
                shutil.copy2(s, d)
                log(f"    Copied file: {item}")
        log("  Copied files successfully")
        
        # Update build.gradle.kts
        build_gradle_path = os.path.join(target_path, "build.gradle.kts")
        with open(build_gradle_path, 'r', encoding='utf-8') as f:
            content = f.read()
        content = re.sub(r'applicationId = "com\.example\.learnopengl\.[^"]+"', 
                        f'applicationId = "com.example.learnopengl.{title_name_clean}.{tutorial_name_clean}"', 
                        content)
        with open(build_gradle_path, 'w', encoding='utf-8') as f:
            f.write(content)
        log("  Updated build.gradle.kts")
        
        # Update CMakeLists.txt
        cmake_lists_path = os.path.join(target_path, "src/main/cpp/CMakeLists.txt")
        with open(cmake_lists_path, 'r', encoding='utf-8') as f:
            content = f.read()
        content = content.replace('project("hello_window")', f'project("{tutorial_name_clean}")')
        content = re.sub(r'set\(LEARN_OPENGL_TITLE "[^"]+"\)', f'set(LEARN_OPENGL_TITLE "{title_name}")', content)
        content = re.sub(r'set\(LEARN_OPENGL_TUTORIAL "[^"]+"\)', f'set(LEARN_OPENGL_TUTORIAL "{tutorial_name}")', content)
        content = content.replace('add_library(hello_window', f'add_library({tutorial_name_clean}')
        content = content.replace('target_link_libraries(hello_window', f'target_link_libraries({tutorial_name_clean}')
        with open(cmake_lists_path, 'w', encoding='utf-8') as f:
            f.write(content)
        log("  Updated CMakeLists.txt")
        
        # Update MyGLRenderer.kt
        renderer_path = os.path.join(target_path, "src/main/java/com/example/learnopengl/MyGLRenderer.kt")
        with open(renderer_path, 'r', encoding='utf-8') as f:
            content = f.read()
        content = content.replace('System.loadLibrary("hello_window")', f'System.loadLibrary("{tutorial_name_clean}")')
        with open(renderer_path, 'w', encoding='utf-8') as f:
            f.write(content)
        log("  Updated MyGLRenderer.kt")
        
        # Update strings.xml
        strings_path = os.path.join(target_path, "src/main/res/values/strings.xml")
        with open(strings_path, 'r', encoding='utf-8') as f:
            content = f.read()
        content = re.sub(r'<string name="app_name">[^<]+</string>', f'<string name="app_name">{tutorial_name}</string>', content)
        with open(strings_path, 'w', encoding='utf-8') as f:
            f.write(content)
        log("  Updated strings.xml")
        
        log("  Done!")
    except Exception as e:
        import traceback
        log(f"  ERROR: {str(e)}")
        log(f"  Traceback: {traceback.format_exc()}")
        log("  Continuing with next module...")

log("\nAll modules processed successfully!")