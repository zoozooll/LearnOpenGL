pluginManagement {
    repositories {
        google {
            content {
                includeGroupByRegex("com\\.android.*")
                includeGroupByRegex("com\\.google.*")
                includeGroupByRegex("androidx.*")
            }
        }
        mavenCentral()
        gradlePluginPortal()
    }
}
dependencyResolutionManagement {
    repositoriesMode.set(RepositoriesMode.FAIL_ON_PROJECT_REPOS)
    repositories {
        google()
        mavenCentral()
    }
}

rootProject.name = "LearnOpenGLAndroid"
include(":app")

// 1. getting_started
include(":1.getting_started:1.1.hello_window")
include(":1.getting_started:1.2.hello_window_clear")
include(":1.getting_started:2.1.hello_triangle")
include(":1.getting_started:2.2.hello_triangle_indexed")
include(":1.getting_started:2.3.hello_triangle_exercise1")
include(":1.getting_started:2.4.hello_triangle_exercise2")
include(":1.getting_started:2.5.hello_triangle_exercise3")
include(":1.getting_started:3.1.shaders_uniform")
include(":1.getting_started:3.2.shaders_interpolation")
include(":1.getting_started:3.3.shaders_class")
include(":1.getting_started:4.1.textures")
include(":1.getting_started:4.2.textures_combined")
include(":1.getting_started:4.4.textures_exercise2")
include(":1.getting_started:4.5.textures_exercise3")
include(":1.getting_started:4.6.textures_exercise4")
include(":1.getting_started:5.1.transformations")
include(":1.getting_started:5.2.transformations_exercise2")
include(":1.getting_started:6.1.coordinate_systems")
include(":1.getting_started:6.2.coordinate_systems_depth")
include(":1.getting_started:6.3.coordinate_systems_multiple")
include(":1.getting_started:7.1.camera_circle")
include(":1.getting_started:7.2.camera_keyboard_dt")
include(":1.getting_started:7.3.camera_mouse_zoom")
include(":1.getting_started:7.4.camera_class")

// 2. lighting
include(":2.lighting:1.colors")
include(":2.lighting:2.1.basic_lighting_diffuse")
include(":2.lighting:2.2.basic_lighting_specular")
include(":2.lighting:3.1.materials")
include(":2.lighting:3.2.materials_exercise1")
include(":2.lighting:4.1.lighting_maps_diffuse_map")
include(":2.lighting:4.2.lighting_maps_specular_map")
include(":2.lighting:4.4.lighting_maps_exercise4")
include(":2.lighting:5.1.light_casters_directional")
include(":2.lighting:5.2.light_casters_point")
include(":2.lighting:5.3.light_casters_spot")
include(":2.lighting:5.4.light_casters_spot_soft")
include(":2.lighting:6.multiple_lights")

// 3. model_loading
include(":3.model_loading:1.model_loading")

// 4. advanced_opengl
include(":4.advanced_opengl:1.1.depth_testing")
include(":4.advanced_opengl:1.2.depth_testing_view")
include(":4.advanced_opengl:2.stencil_testing")
include(":4.advanced_opengl:3.1.blending_discard")
include(":4.advanced_opengl:3.2.blending_sort")
include(":4.advanced_opengl:5.1.framebuffers")
include(":4.advanced_opengl:5.2.framebuffers_exercise1")
include(":4.advanced_opengl:6.1.cubemaps_skybox")
include(":4.advanced_opengl:6.2.cubemaps_environment_mapping")
include(":4.advanced_opengl:8.advanced_glsl_ubo")
include(":4.advanced_opengl:9.1.geometry_shader_houses")
include(":4.advanced_opengl:9.2.geometry_shader_exploding")
include(":4.advanced_opengl:9.3.geometry_shader_normals")
include(":4.advanced_opengl:10.1.instancing_quads")
include(":4.advanced_opengl:10.2.asteroids")
include(":4.advanced_opengl:10.3.asteroids_instanced")
include(":4.advanced_opengl:11.1.anti_aliasing_msaa")
include(":4.advanced_opengl:11.2.anti_aliasing_offscreen")

// 5. advanced_lighting
include(":5.advanced_lighting:1.advanced_lighting")
include(":5.advanced_lighting:2.gamma_correction")
include(":5.advanced_lighting:3.1.1.shadow_mapping_depth")
include(":5.advanced_lighting:3.1.2.shadow_mapping_base")
include(":5.advanced_lighting:3.1.3.shadow_mapping")
include(":5.advanced_lighting:3.2.1.point_shadows")
include(":5.advanced_lighting:3.2.2.point_shadows_soft")
include(":5.advanced_lighting:4.normal_mapping")
include(":5.advanced_lighting:5.1.parallax_mapping")
include(":5.advanced_lighting:5.2.steep_parallax_mapping")
include(":5.advanced_lighting:5.3.parallax_occlusion_mapping")
include(":5.advanced_lighting:6.hdr")
include(":5.advanced_lighting:7.bloom")
include(":5.advanced_lighting:8.1.deferred_shading")
include(":5.advanced_lighting:8.2.deferred_shading_volumes")
include(":5.advanced_lighting:9.ssao")

// 6. pbr
include(":6.pbr:1.1.lighting")
include(":6.pbr:1.2.lighting_textured")
include(":6.pbr:2.1.1.ibl_irradiance_conversion")
include(":6.pbr:2.1.2.ibl_irradiance")
include(":6.pbr:2.2.1.ibl_specular")
include(":6.pbr:2.2.2.ibl_specular_textured")

// 7. in_practice
include(":7.in_practice:1.debugging")
include(":7.in_practice:2.text_rendering")

// GUEST_ARTICLES
include(":8.guest:2020:oit")
include(":8.guest:2020:skeletal_animation")
include(":8.guest:2021:1.scene:1.scene_graph")
include(":8.guest:2021:1.scene:2.frustum_culling")
include(":8.guest:2021:2.csm")
include(":8.guest:2021:3.tessellation:terrain_gpu_dist")
include(":8.guest:2021:3.tessellation:terrain_cpu_src")
include(":8.guest:2021:4.dsa")
include(":8.guest:2022:5.computeshader_helloworld")
include(":8.guest:2022:6.physically_based_bloom")
include(":8.guest:2022:7.area_lights:1.area_light")
include(":8.guest:2022:7.area_lights:2.multiple_area_lights")